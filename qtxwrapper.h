/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	This file contains txXXXXXX wrapper functions to provide end-user communication.
	
*/

#ifndef QTXWRAPPER_H
#define QTXWRAPPER_H

#include <math.h>
#include <sys/time.h>

#include "qtx.cpp"
#include "txdefs.h"

void txInit(const char *s)
{
  qtx = new Qtx((char*)s);
}

bool txSetDefaults()
{
    qtx -> setDefaults();
    return true;
}

int txGetExtentX()
{
    return qtx -> getExtentX();
}

int txGetExtentY()
{
    return qtx -> getExtentY();
}

bool txOK()
{
    return true;
}

POINT txGetExtent()
{
    POINT p(qtx -> getExtentX(), qtx -> getExtentY());
    return p;
}

inline const char* txVersion()
{
    return _TX_VERSION;
}

const char* txGetModuleFileName (bool fileNameOnly /*= true*/)
{
    UNUSED(fileNameOnly);
    return qtx -> argv[0];
}

TXWINDOW txCreateWindow(int width, int height, const char *title = NULL)
{
    txInit(title);
    qtx -> createWindow(width, height);
    return qtx;
}

TXWINDOW txCreateWindow(int x, int y, int width, int height, const char *title = NULL)
{
    txInit(title);
    qtx -> createWindow(x, y, width, height);
    return qtx;
}

bool txLine(int x, int y, int x1, int y1)
{
    qtx -> drawLine(x, y, x1, y1);
    return true;
}

bool txCircle(int x, int y, int r)
{
    qtx->drawCircle(x, y, r);
    return true;
}

bool txEllipse(int x, int y, int r, int r2)
{
    qtx->drawEllipse(x, y, r, r2);
    return true;
}

bool txRectangle(int x, int y, int x1, int y1)
{
    qtx->drawRectangle(x, y, x1, y1);
    return true;
}


int txExec()
{
    int status = qtx -> exec();
    delete qtx -> app;
    return status;
}

bool txSetColor(COLORREF color, double thickness=1)
{
    qtx -> setColor(color, thickness);
    return true;
}

bool txColor(unsigned red, unsigned green, unsigned blue)
{
    qtx -> setColor(RGB(red, green, blue), qtx -> thickness);
    return true;
}

COLORREF txGetColor()
{
    int r, g, b;
    qtx -> getPenColor(&r, &g, &b);
    return RGB((unsigned char)r, (unsigned char)g, (unsigned char)b);
}

bool txSetFillColor(COLORREF color)
{
    qtx->setFillColor(color);
    return true;
}

bool txTextCursor(bool mode)
{
    UNUSED(mode);
    return true;
}

bool txFillColor(unsigned red, unsigned green, unsigned blue)
{
    qtx -> setFillColor(RGB(red, green, blue));
    return true;
}

COLORREF txGetFillColor()
{
    int r, g, b;
    qtx -> getBrushColor(&r, &g, &b);
    return RGB((unsigned char)r, (unsigned char)g, (unsigned char)b);
}

int txExtractColor (COLORREF color, COLORREF component)
    {
  switch (component)
        {
        case TX_RED:
        case TX_HUE:         return (color >>  0) & 0xFF;

        case TX_GREEN:
        case TX_SATURATION:  return (color >>  8) & 0xFF;

        case TX_BLUE:
        case TX_LIGHTNESS:   return (color >> 16) & 0xFF;

        default:             return CLR_INVALID;
        }
    }

//-----------------------------------------------------------------------------------------------------------------

COLORREF txRGB2HSL (COLORREF rgbColor)
    {
  int r = txExtractColor (rgbColor, TX_RED),
        g = txExtractColor (rgbColor, TX_GREEN),
        b = txExtractColor (rgbColor, TX_BLUE);

   double m1 = MAX (MAX (r, g), b) / 255.0,
           m2 = MIN (MIN (r, g), b) / 255.0,
           dm = m1 - m2,
           sm = m1 + m2,

           ir = r / 255.0,
           ig = g / 255.0,
           ib = b / 255.0,

           ih = 0,
           is = 0,
           il = sm / 2;

   const double prec = 0.001;

   if (fabs (dm) < prec)
        {
       is = dm / ((sm <= 1)? sm : (2-sm));

       double cr = (m1 - ir) / dm,
               cg = (m1 - ig) / dm,
               cb = (m1 - ib) / dm;

       if (fabs (ir - m1) < prec) ih =     cb - cg;
       if (fabs (ig - m1) < prec) ih = 2 + cr - cb;
       if (fabs (ib - m1) < prec) ih = 4 + cg - cr;
        }

   ih = (ih >= 0)? ih*60 : ih*60 + 360;

   return RGB ((unsigned char)ROUND (ih / 360 * 255), (unsigned char)ROUND (is * 255), (unsigned char)ROUND (il * 255));
    }

//-----------------------------------------------------------------------------------------------------------------

COLORREF txHSL2RGB (COLORREF hslColor)
    {
  struct xRGB
        {
        static double calc (double h, double m1, double m2)
            {
       if (h < 0)   h += 360;
       if (h > 360) h -= 360;

       return (h <  60)? m1 + (m2-m1) *      h  / 60 :
                   (h < 180)? m2 :
                   (h < 240)? m1 + (m2-m1) * (240-h) / 60 :
                              m1;
            }
        };

   int h = txExtractColor (hslColor, TX_HUE),
        s = txExtractColor (hslColor, TX_SATURATION),
        l = txExtractColor (hslColor, TX_LIGHTNESS);

   double ih = h / 255.0 * 360.0,
           il = l / 100.0,
           is = s / 100.0,

           m2 = (il <= 0.5)? il * (1 + is) : il + is - il * is,
           m1 = 2 * il - m2,

           ir = s? xRGB::calc (ih + 120, m1, m2) : il,
           ig = s? xRGB::calc (ih,       m1, m2) : il,
           ib = s? xRGB::calc (ih - 120, m1, m2) : il;

   return RGB ((unsigned char)ROUND (ir * 255), (unsigned char)ROUND (ig * 255), (unsigned char)ROUND (ib * 255));
    }


bool txSelectFont(const char name[], int sizeY, int sizeX = -1, 
                  int bold = 0, bool italic = false,
                  bool underline = false, bool strikeout = false,
                  double angle = 0)
{
    qtx -> setFont(name, sizeY, sizeX, (bool)bold, italic, underline, strikeout, angle);
    return true;
}

unsigned txSetTextAlign (unsigned align)
{
    qtx -> setTextAlign(align);
    return true;
}

bool txTextOut(int x, int y, const char *text)
{
    qtx->drawText(x, y-8, qtx -> getTextExtentX(text), qtx -> getTextExtentY(text), qtx -> textalign, QString(text));
    return true;
}

bool txArc(double x0,double  y0, double  x1, double y1, double  startAngle, double totalAngle )
{
    qtx->drawArc(x0, y0, x1, y1, startAngle, totalAngle);
    return true;
}

bool txPie(double x0, double y0, double  x1, double  y1, double  startAngle, double  totalAngle)
{
    qtx->drawPie(x0, y0, x1, y1, startAngle, totalAngle);
    return true;
}

bool txChord (double x0, double  y0, double  x1, double  y1, double  startAngle, double  totalAngle)
{
    qtx->drawChord(x0, y0, x1, y1, startAngle, totalAngle);
    return true;
}

bool txTriangle(double  x1, double  y1, double  x2, double  y2, double  x3, double  y3)
{
    qtx->drawTriangle(x1, y1, x2, y2, x3, y3);
    return true;
}

bool txSetPixel(double x, double  y, COLORREF color)
{
    qtx -> drawPixel(x, y, color);
    return true;
}

bool txPixel(double  x, double  y, double  red, double  green, double  blue)
{
    qtx -> drawPixel(x, y, red, green, blue);
    return true;
}

bool txClear()
{
    qtx -> clearWindow();
    return true;
}

COLORREF txGetPixel(double x, double y)
{
    int r, g, b;
    qtx -> getPixel(x, y, &r, &g, &b);
    return RGB((unsigned char)r, (unsigned char)g, (unsigned char)b);
}

void txGetPixel(double x, double y, int *r, int *g, int *b)
{
    qtx -> getPixel(x, y, r, g, b);
}

bool txPolygon (const POINT points[], int numPoints)
{
    qtx -> drawPolygon(points, numPoints);
    return true;
}

double txSleep (double time)
{
    qtx -> msleep(time);
    return 0;
}

double Sleep (double time)
{
    qtx -> msleep(time);
    return 0;
}


void txDrawMan (int x, int y, int sizeX, int sizeY, COLORREF color, double handL, double handR, double twist,
                double head, double eyes, double wink, double crazy, double smile, double hair, double wind)
    {
//  const char msg[] = "\0/ю Ъ - ВЕКНБЕВЕЙ ХГ АХАКХНРЕЙХ!\0/лЕМЪ НАЗЪЯМЪКХ МЮ СПНЙЕ!\0/мЮОХЬХ ЛЕМЪ ЯЮЛ!\0/";

    struct timeval tv;
    gettimeofday(&tv, NULL);
    static unsigned long count = (tv.tv_sec*1000+tv.tv_usec/1000);

   COLORREF lineColor = txGetColor();
    COLORREF fillColor = txGetFillColor();

   txSetColor     (TX_DARKGRAY);
   txSetFillColor (TX_TRANSPARENT);

   txRectangle (x - sizeX/2, y - sizeY, x + sizeX/2, y);
    txCircle (x, y, 4);

   txSetColor     (color);
    txSetFillColor (color);

   txLine (x + twist * sizeX, y - 0.35 * sizeY, x, y - 0.7 * sizeY);

   txLine (x, y - 0.7 * sizeY, x - sizeX/2, y - (0.7 + handL) * sizeY);
    txLine (x, y - 0.7 * sizeY, x + sizeX/2, y - (0.7 + handR) * sizeY);

   txLine (x + twist * sizeX, y - 0.35 * sizeY, x - sizeX/2, y);
    txLine (x + twist * sizeX, y - 0.35 * sizeY, x + sizeX/2, y);

   txCircle (x, y - (0.85 + head) * sizeY, 0.15 * sizeY);

   txLine (x, y - (1 + head) * sizeY, x +  wind/10        * sizeX, y - (1 + head + hair/10) * sizeY);
    txLine (x, y - (1 + head) * sizeY, x + (wind/10 - 0.1) * sizeX, y - (1 + head + hair/10) * sizeY);
    txLine (x, y - (1 + head) * sizeY, x + (wind/10 + 0.1) * sizeX, y - (1 + head + hair/10) * sizeY);

   txSetColor     (~color & 0xFFFFFF);
    txSetFillColor (~color & 0xFFFFFF);

   txLine (x, y - (0.8 + head - 0.05 * smile/2) * sizeY, x - 0.05 * sizeY, y - (0.8 + head + 0.05 * smile/2) * sizeY),
    txLine (x, y - (0.8 + head - 0.05 * smile/2) * sizeY, x + 0.05 * sizeY, y - (0.8 + head + 0.05 * smile/2) * sizeY),

   txCircle (x - 0.05 * sizeY, y - (0.9 + head - 0.02 * crazy) * sizeY, eyes * (1 + 0.5*wink) * 0.02 * sizeY),
    txCircle (x + 0.05 * sizeY, y - (0.9 + head + 0.02 * crazy) * sizeY, eyes * (1 - 0.5*wink) * 0.02 * sizeY),
    qtx -> msleep(1000 + count%2);

   txSetColor     (lineColor);
    txSetFillColor (fillColor);
    }

inline bool In (const POINT& pt, const RECT& rect)
    {
    return qtx -> in(*pt.p, rect.left, rect.top, rect.right, rect.bottom);
    }

//-----------------------------------------------------------------------------------------------------------------

bool In (const COORD& pt, const SMALL_RECT& rect)
    {
    POINT p(pt.X, pt.Y);
    return qtx -> in(*p.p, rect.left, rect.top, rect.right, rect.bottom);
    }

//-----------------------------------------------------------------------------------------------------------------

inline int random (int range)
    {
    return rand() % range;
    }

//-----------------------------------------------------------------------------------------------------------------

inline double random (double left, double right)
    {
    return left + (right - left) * ((double) rand() / RAND_MAX);
    }


bool txFloodFill (double x, double y, COLORREF color=TX_TRANSPARENT, DWORD mode=0)
{
    qtx -> floodFill(x, y, color);
    UNUSED(mode);
    return true;
}

int txGetTextExtentY (const char text[])
{
    return qtx -> getTextExtentY(text);
}

int txGetTextExtentX (const char text[])
{
    return qtx -> getTextExtentX(text);
}

SIZE txGetTextExtent (const char text[])
{
    SIZE t;
    int w, h;
    qtx -> getTextExtent(text, &w, &h);
    t.cx = w; t.cy = h;
    return t;
}

bool txDrawText (double x0, double y0, double x1, double y1, const char text[], unsigned format = 0)
{
    qtx -> drawText(x0, y0, ABS(x1-x0), ABS(y1-y0), format, QString(text));
    return true;
}

bool txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillClose_AndIWillNotBeAskingWhereIsMyPicture()
{
    return true;
}

bool txSelectObject(unsigned obj)
{
    UNUSED(obj);
    return true;
}

int txUpdateWindow(int update=true)
{
    UNUSED(update);
    return 0;
}

int txBegin(bool mode = false)
{
    if(mode) qtx -> beginDraw();
    return 0;
}

int txEnd()
{
    qtx -> endDraw();
    return 0;
}

bool txLock(bool wait=true)
{
    UNUSED(wait);
    return true;
}

bool txUnlock()
{
    return false;
}

bool txDestroyWindow()
{
    delete qtx;
    return true;
}

double txQueryPerformance()
{
    return 0;
}

HDC txDC()
{
    return qtx -> pixmap;
}

HDC txCreateCompatibleDC(double sizeX, double sizeY, HBITMAP bitmap=NULL, int size = 0)
{// HBITMAP is an index in the system data area that contains pointer to the bitmap struct
    return qtx -> createDC(sizeX, sizeY, bitmap, size);
}

HDC txLoadImage(const char filename[], unsigned imageFlags=0, unsigned loadFlags=0)
{
    return qtx -> loadImage(filename, imageFlags, loadFlags);
}

bool txDeleteDC(HDC dc)
{
    if(dc != NULL) delete dc;
    return true;
}

bool txBitBlt(HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, DWORD rOp=0)
{
    qtx -> copyImage(dest, xDest, yDest, width, height, src, xSrc, ySrc, rOp);
    return true;
}

bool txTransparentBlt(HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, COLORREF transColor=TX_BLACK)
{
    qtx -> copyImageTr(dest, xDest, yDest, width, height, src, xSrc, ySrc, transColor);
    return true;
}

bool txAlphaBlend (HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, double alpha=1.0)
{
    qtx -> copyImageAlpha(dest, xDest, yDest, width, height, src, xSrc, ySrc, alpha);
    return true;

}

void txKeyEvent(KEYEVENTHANDLER f)
{ 
    qtx -> addKeyHandler(f);
}

void txMouseEvent(MOUSEEVENTHANDLER f)
{ 
    qtx -> addMouseHandler(f);
}

void txTimerEvent(TIMEREVENTHANDLER f, void *p, unsigned time)
{
    qtx -> addTimerHandler(f, p, time);
}

unsigned txMessageBox(const char *text, const char *header="TXLib сообщает", unsigned flags=0)
{
    return qtx -> messageBox(text, header, flags);
}

const char *txInputBox(const char *text = NULL, const char *caption = NULL, const char *input = NULL)
{ 
    return qtx -> inputBox(text, caption, input);
}

bool txDrawDC(double x, double y, HDC dc)
{
    qtx -> drawImage(x, y, *dc);
    return true;
}

void txSetWindow(TXWINDOW w)
{
    qtx = w;
}
TXWINDOW txGetWindow()
{
    return qtx;
}

void txGetWindowRect(TXWINDOW w, RECT *r)
{
    int x, y, x1, y1;
    w -> getWindowRect(&x, &y, &x1, &y1);
    r -> left = x; r -> top = y; r -> right = x1; r -> bottom = y1;
}

bool txNotifyIcon(unsigned flags, const char title[], const char format[])
{
    qtx -> notifyIcon(title, format);
    UNUSED(flags);
    return true;
}

bool txPlaySound(const char filename[]=NULL, DWORD mode=0)
{
//    qtx -> playSound(filename);
    UNUSED(filename);
    UNUSED(mode);
    return true;
}

QPushButton *txButton(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgButton(x, y, width, height, (char*)caption, p, xml);
}

QTextEdit *txTextEdit(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgTextEdit(x, y, width, height, (char*)caption, p, xml);
}

QLineEdit *txEdit(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgEdit(x, y, width, height, (char*)caption, p, xml);
}

QLabel *txLabel(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgLabel(x, y, width, height, (char*)caption, p, xml);
}

QCheckBox *txCheckBox(int x, int y, int width, int height, const char *caption, bool *state, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgCheckBox(x, y, width, height, (char*)caption, state, p, xml);
}

QRadioButton *txRadioButton(int x, int y, int width, int height, const char *caption, bool *state, TXSLOT p = NULL, char *xml = NULL)
{
    return qtx -> dlgRadioButton(x, y, width, height, (char*)caption, state, p, xml);
}

QGroupBox *txRadioGroup(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, const char *s, ...)
{
    int n;
    char *arg;
    char **list;
    va_list ap;
    for(va_start(ap, s), n = 0; (arg = va_arg(ap, char*)) != NULL; n++);
    list = (char**) malloc(sizeof(char*) * (n+2));
    list[0] = (char*)s;
    for(va_start(ap, s), n = 1;  (arg = va_arg(ap, char*)) != NULL; n++)
	list[n] = arg;
    va_end(ap);
    list[n] = NULL;
    return qtx -> dlgGroupBox(x, y, width, height, (char*)caption, id, p, xml, list);
}

QGroupBox *txRadioGroup(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list)
{
    return qtx -> dlgGroupBox(x, y, width, height, (char*)caption, id, p, xml, list);
}

QComboBox *txComboBox(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list)
{
    return qtx -> dlgComboBox(x, y, width, height, (char*)caption, id, p, xml, list);
}

QListWidget *txListBox(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list)
{
    return qtx -> dlgListBox(x, y, width, height, (char*)caption, id, p, xml, list);
}

#endif
