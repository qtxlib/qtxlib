/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	Extern functions definition file.
	It used when macro EXTERN_QTX is defined (user project linked with libqtx.so).
	
*/

#ifndef QTXEXTERN_H
#define QTXEXTERN_H


#ifdef __WIN32__
#ifdef BUILD_LIB
#define LIB_CLASS __declspec(dllexport)
#else
#define LIB_CLASS __declspec(dllimport)
#endif
#else
#define LIB_CLASS       // Linux & other Unices : leave it blank !
#endif

#include "qtx.h"
#include "txdefs.h"

extern void LIB_CLASS txInit(const char *s);
extern bool LIB_CLASS txSetDefaults();
extern int LIB_CLASS txGetExtentX();
extern int LIB_CLASS txGetExtentY();
extern bool LIB_CLASS txOK();
extern POINT LIB_CLASS txGetExtent();
extern void LIB_CLASS txGetWindowRect(TXWINDOW w, RECT *r);
extern const char* LIB_CLASS txVersion();
extern const char* LIB_CLASS txGetModuleFileName (bool fileNameOnly /*= true*/);
extern TXWINDOW LIB_CLASS txCreateWindow(int width, int height, const char *title = NULL);
extern TXWINDOW LIB_CLASS txCreateWindow(int x, int y, int width, int height, const char *title = NULL);
extern bool LIB_CLASS txLine(int x, int y, int x1, int y1);
extern bool LIB_CLASS txCircle(int x, int y, int r);
extern bool LIB_CLASS txEllipse(int x, int y, int r, int r2);
extern bool LIB_CLASS txRectangle(int x, int y, int x1, int y1);
extern int LIB_CLASS txExec();
extern bool LIB_CLASS txSetColor(COLORREF color, double thickness=1);
extern bool LIB_CLASS txColor(unsigned red, unsigned green, unsigned blue);
extern COLORREF LIB_CLASS txGetColor();
extern bool LIB_CLASS txSetFillColor(COLORREF color);
extern bool LIB_CLASS txTextCursor(bool mode);
extern bool LIB_CLASS txFillColor(unsigned red, unsigned green, unsigned blue);
extern COLORREF LIB_CLASS txGetFillColor();
extern int LIB_CLASS txExtractColor (COLORREF color, COLORREF component);
extern COLORREF LIB_CLASS txRGB2HSL (COLORREF rgbColor);
extern COLORREF LIB_CLASS txHSL2RGB (COLORREF hslColor);
extern bool LIB_CLASS txSelectFont(const char name[], int sizeY, int sizeX = -1,
                  int bold = 0, bool italic = false,
                  bool underline = false, bool strikeout = false,
                  double angle = 0);
extern unsigned LIB_CLASS txSetTextAlign (unsigned align);
extern bool LIB_CLASS txTextOut(int x, int y, const char *text);
extern bool LIB_CLASS txArc(double x0,double  y0, double  x1, double y1, double  startAngle, double totalAngle);
extern bool LIB_CLASS txPie(double x0, double y0, double  x1, double  y1, double  startAngle, double  totalAngle);
extern bool LIB_CLASS txChord (double x0, double  y0, double  x1, double  y1, double  startAngle, double  totalAngle);
extern bool LIB_CLASS txTriangle(double  x1, double  y1, double  x2, double  y2, double  x3, double  y3);
extern bool LIB_CLASS txSetPixel(double x, double  y, COLORREF color);
extern bool LIB_CLASS txPixel(double  x, double  y, double  red, double  green, double  blue);
extern bool LIB_CLASS txClear();
extern COLORREF LIB_CLASS txGetPixel(double x, double y);
extern void LIB_CLASS txGetPixel(double x, double y, int *r, int *g, int *b);
extern bool LIB_CLASS txPolygon (const POINT points[], int numPoints);
extern double LIB_CLASS txSleep (double time);
extern void LIB_CLASS txDrawMan(int x, int y, int sizeX, int sizeY, COLORREF color, double handL, double handR, double twist,
                double head, double eyes, double wink, double crazy, double smile, double hair, double wind);
extern bool LIB_CLASS In (const POINT& pt, const RECT& rect);
extern bool LIB_CLASS In (const COORD& pt, const SMALL_RECT& rect);
extern int LIB_CLASS random (int range);
extern double LIB_CLASS random (double left, double right);
extern bool LIB_CLASS txFloodFill (double x, double y, COLORREF color=TX_TRANSPARENT, DWORD mode=0);
extern int LIB_CLASS txGetTextExtentY (const char text[]);
extern int LIB_CLASS txGetTextExtentX (const char text[]);
extern SIZE LIB_CLASS txGetTextExtent (const char text[]);
extern bool LIB_CLASS txDrawText (double x0, double y0, double x1, double y1, const char text[], unsigned format = 0);
extern bool LIB_CLASS txIDontWantToHaveAPauseAfterMyProgramBeforeTheWindowWillClose_AndIWillNotBeAskingWhereIsMyPicture();
extern bool LIB_CLASS txSelectObject(unsigned obj);
extern int LIB_CLASS txUpdateWindow(int update=true);
extern int LIB_CLASS txBegin(bool mode = false);
extern int LIB_CLASS txEnd();
extern bool LIB_CLASS txLock(bool wait=true);
extern bool LIB_CLASS txUnlock();
extern bool LIB_CLASS txDestroyWindow();
extern double LIB_CLASS txQueryPerformance();
extern HDC LIB_CLASS txDC();
extern HDC LIB_CLASS txCreateCompatibleDC(double sizeX, double sizeY, HBITMAP bitmap=NULL, int size=0);
extern HDC LIB_CLASS txLoadImage(const char filename[], unsigned imageFlags=0, unsigned loadFlags=0);
extern bool LIB_CLASS txDeleteDC(HDC dc);
extern bool LIB_CLASS txBitBlt(HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, DWORD rOp=0);
extern bool LIB_CLASS txTransparentBlt(HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, COLORREF transColor=TX_BLACK);
extern bool LIB_CLASS txAlphaBlend (HDC dest, double xDest, double yDest, double width, double height, HDC src, double xSrc=0, double ySrc=0, double alpha=1.0);
extern void LIB_CLASS txKeyEvent(KEYEVENTHANDLER f);
extern void LIB_CLASS txMouseEvent(MOUSEEVENTHANDLER f);
extern void LIB_CLASS txTimerEvent(TIMEREVENTHANDLER f, void *p, unsigned time);
extern unsigned LIB_CLASS txMessageBox(const char *text, const char *header="TXLib сообщает", unsigned flags=0);
extern const char* LIB_CLASS txInputBox(const char *text = NULL, const char *caption = NULL, const char *input = NULL);
extern bool LIB_CLASS txDrawDC(double x, double y, HDC dc);
extern void LIB_CLASS txSetWindow(TXWINDOW w);
extern TXWINDOW LIB_CLASS txGetWindow();
extern bool LIB_CLASS txNotifyIcon(unsigned flags, const char title[], const char format[]);
extern bool LIB_CLASS txPlaySound(const char filename[]=NULL, DWORD mode=0);
extern QPushButton* LIB_CLASS txButton(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL);
extern QTextEdit* LIB_CLASS txTextEdit(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL);
extern QLineEdit* LIB_CLASS txEdit(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL);
extern QLabel* LIB_CLASS txLabel(int x, int y, int width, int height, const char *caption, TXSLOT p = NULL, char *xml = NULL);
extern QCheckBox* LIB_CLASS txCheckBox(int x, int y, int width, int height, const char *caption, bool *state, TXSLOT p = NULL, char *xml = NULL);
extern QRadioButton* LIB_CLASS txRadioButton(int x, int y, int width, int height, const char *caption, bool *state, TXSLOT p = NULL, char *xml = NULL);
extern QGroupBox* LIB_CLASS txRadioGroup(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, const char *s, ...);
extern QGroupBox* LIB_CLASS txRadioGroup(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list);
extern QComboBox* LIB_CLASS txComboBox(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list);
extern QListWidget* LIB_CLASS txListBox(int x, int y, int width, int height, const char *caption, int *id, TXSLOT p, char *xml, char **list);

#endif
