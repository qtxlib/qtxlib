/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	Qtx class definition file.
	This class represents an environment to draw or to create an interface with dialog controls.
	
*/

#include "qtx.h"
#include "qtxpoint.cpp"
#include "qtxcnt.cpp"

//#define ABS(n) ((n < 0) ? (-n) : (n))
inline int ABS(int n) { if(n < 0) return -n; else return n; }
inline void _LESSZERO(int &n) { if(n < 0) n = 0; }

Qtx **qtxlist = NULL, *qtx = NULL; // we can use many windows in a time, and always keep an active one.
QPixmap* Qtx::getPixmap() { return pixmap; }
int Qtx::exec() { return app -> exec(); }
void Qtx::beginDraw() { begin = true; }
void Qtx::endDraw() { begin = false; container -> setPixmap(*pixmap); }
int Qtx::getExtentX() { return windowWidth; }
int Qtx::getExtentY() { return windowHeight; }
void Qtx::getWindowRect(int *x, int *y, int *x1, int *y1) { *x = container -> x(); *y = container -> y(); *x1 = container -> x() + container -> width(); *y1 =  container -> y() + container -> height(); }
void Qtx::getPenColor(int *r, int *g, int *b) { *r = painter -> pen().color().red(); *g = painter -> pen().color().green(); *b = painter -> pen().color().blue(); }
void Qtx::getBrushColor(int *r, int *g, int *b) { *r = painter -> brush().color().red(); *g = painter -> brush().color().green(); *b = painter -> brush().color().blue(); }
void Qtx::setTextAlign(unsigned int a) { textalign = a; }
void Qtx::getTextExtent(const char *s, int *w, int *h) { QFontMetrics fm(*font); QRect rect = fm.boundingRect(s); *w = rect.width() + 5; *h = rect.height() + 5; }
int Qtx::getTextExtentX(const char *s) { QFontMetrics fm(*font); QRect rect = fm.boundingRect(s); return rect.width() + 5; }
int Qtx::getTextExtentY(const char *s) { QFontMetrics fm(*font); QRect rect = fm.boundingRect(s); return rect.height() + 5; }
void Qtx::msleep(unsigned long ms)  { QTime time; time.start(); for(;(unsigned long)time.elapsed() < ms;) app -> processEvents(); }
bool Qtx::in(QPoint p, int x, int y, int x1, int y1) { QRect r(x, y, x1, y1); return r.contains(p, true); }
QImage* Qtx::toImage() { return new QImage(pixmap -> toImage()); }
QPixmap* Qtx::createDC(int x, int y, unsigned char *data, int size) { QPixmap *pix = new QPixmap(x, y); pix -> loadFromData(data, size); return pix; }
void Qtx::drawImage(int x, int y, QPixmap pix) {  painter -> drawImage(x, y, pix.toImage()); if(!begin) container -> setPixmap(*pixmap);  } // M.B.I.
void Qtx::addKeyHandler(void (*handler)(int)) { container -> keyhandler = handler; }
void Qtx::addMouseHandler(void (*handler)(int, int, int, bool)) { container -> mousehandler = handler; }
void Qtx::addTimerHandler(void (*handler)(void *p), void *p, unsigned time) { container -> timerhandler = handler; container -> thparam = p; container -> startTimer(time);  }

Qtx::Qtx(char *s)
{
    int i = 0;
    painter = NULL;
    pixmap = NULL;
    container = NULL;
    font = NULL;
    dialog = NULL;
    argc = 1;
    argv[0] = s;
    argv[1] = NULL;
    if(qtx == NULL) 
	app = new QApplication(argc, argv); // argv may be modified
    else
	for(; qtxlist[i] != NULL; i++);
    qtxlist = (Qtx**)realloc(qtxlist, (i+2) * sizeof(Qtx*));
    qtxlist[i] = this;
    qtxlist[i+1] = NULL;
    if(qtx != NULL)
	if(qtx -> app != NULL) app = qtx -> app; // copy qapplication to self
    title = s;
    begin = false;
    setDefaults();
}

Qtx::~Qtx()
{
    if(font != NULL)  delete font; 
    if(container != NULL)  delete container; 
    if(painter != NULL) delete painter;
    if(pixmap != NULL)  delete pixmap; 
}

void Qtx::setDefaults()
{
    QRect rec = QApplication::desktop() -> screenGeometry();
    screenWidth = rec.width();
    screenHeight = rec.height();
    textangle = 0;
    windowWidth = 0;
    windowHeight = 0;
    thickness = 1;
    textalign = Qt::AlignAbsolute;
}

inline void Qtx::___createWindow(int x, int y, int width, int height)
{
    windowWidth = width;
    windowHeight = height;

    QPalette palette;
    pixmap = new QPixmap(width, height);
    pixmap -> fill(palette.color(QPalette::Window));

    painter = new QPainter(pixmap);
//    painter -> setRenderHint(QPainter::Antialiasing);
    painter -> setPen(QPen(Qt::black, thickness, Qt::SolidLine, Qt::RoundCap));
    painter -> setBrush(QBrush(palette.color(QPalette::Window)));

    font = new QFont("Tahoma",8);
    font -> setPointSize(14);
    painter -> setFont(*font);

    container = new QTxContainer;

    container -> setGeometry(x, y, pixmap -> width(), pixmap -> height());
    container -> setPixmap(*pixmap);
    container -> setMinimumSize( pixmap -> width(), pixmap -> height() );
    container -> setMaximumSize( pixmap -> width(), pixmap -> height() );
    container -> setWindowTitle(title);
    container -> setMouseTracking(true);
    container -> show();

}

int Qtx::createWindow(int width, int height)
{
    int x = (screenWidth - width) / 2,
        y = (screenHeight - height) / 2;
    ___createWindow(x, y, width, height);
    return 0;
}

int Qtx::createWindow(int x, int y, int width, int height)
{
    ___createWindow(x, y, width, height);
    return 0;
}



void Qtx :: drawLine(int x1, int y1, int x2, int y2)
{
    _LESSZERO(x1);
    _LESSZERO(y1);
    _LESSZERO(x2);
    _LESSZERO(y2);
    painter -> drawLine(x1,y1,x2,y2);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx :: drawCircle(int x, int y, int radius)
{
    _LESSZERO(x);
    _LESSZERO(y);
    painter -> drawEllipse(x-radius,y-radius,radius*2, radius*2);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx :: drawEllipse(int x, int y, int radius1, int radius2)
{
//    painter -> drawEllipse(x-radius1, y-radius2, radius1*2, radius2*2);
    _LESSZERO(x);
    _LESSZERO(y);
    painter -> drawEllipse(x, y, radius1-x, radius2-y);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx :: drawRectangle(int x1, int y1, int x2, int y2)
{
    _LESSZERO(x1);
    _LESSZERO(y1);
    _LESSZERO(x2);
    _LESSZERO(y2);
    QRect rect(x1 < x2 ? x1 : x2, y1 < y2 ? y1 : y2, ABS(x2 - x1), ABS(y2-y1));
    painter->drawRect(rect);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx::drawArc(int x0, int y0, int x1, int y1, int startAngle, int totalAngle)
{
    _LESSZERO(x0);
    _LESSZERO(y0);
    _LESSZERO(x1);
    _LESSZERO(y1);
    painter->drawArc(QRect(x0, y0, x1-x0, y1-x0), startAngle, totalAngle);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx::drawPie(int x0, int y0, int x1, int y1, int startAngle, int totalAngle)
{
    _LESSZERO(x0);
    _LESSZERO(y0);
    _LESSZERO(x1);
    _LESSZERO(y1);
    painter->drawPie(QRect(x0, y0, x1-x0, y1-y0), startAngle, totalAngle);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx::drawChord(int x0, int y0, int x1, int y1, int startAngle, int totalAngle)
{
    _LESSZERO(x0);
    _LESSZERO(y0);
    _LESSZERO(x1);
    _LESSZERO(y1);
    painter->drawArc(QRect(x0, y0, x1-x0, y1-y0), startAngle, totalAngle);
    if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx::drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    drawLine(x1, y1, x2,y2);
    drawLine(x2, y2, x3,y3);
    drawLine(x3, y3, x1,y1);
}

int Qtx::drawText(int x, int y, int w, int h, 
                    int flags, const QString &text)
{
    painter->save();
    if(flags == Qt::AlignCenter) x-=w/2;
    painter->translate(x, y);
    painter->rotate(textangle);
    painter->drawText(0, 0, w, h, flags, text);
    if(!begin) container -> setPixmap(*pixmap); 
    painter->restore();
    return 0;
}

int Qtx::setColor(unsigned int color, int thickness)
{
    int alpha = 255;
    int r = (color>>16) & 0xff; 
    int g = (color>>8) & 0xff;
    int b = (color) & 0xff;
    if(color == 0xffffffff) alpha = 0;
    painter -> setPen(QPen(QColor(r, g, b, alpha), thickness, Qt::SolidLine, Qt::RoundCap));
    this -> thickness = thickness;
    return 0;
}

int Qtx::setColor(int r, int g, int b, int thickness)
{
    painter -> setPen(QPen(QColor(r, g, b), thickness, Qt::SolidLine, Qt::RoundCap));
    this -> thickness = thickness;
    return 0;
}

int Qtx::setFillColor(unsigned int color)
{
    int alpha = 255;
    int r = (color>>16) & 0xff; 
    int g = (color>>8) & 0xff;
    int b = (color) & 0xff;
    if(color == 0xffffffff) alpha = 0;
    painter -> setBrush(QBrush(QColor(r, g, b, alpha)));
    return 0;
}

int Qtx::setFillColor(int r, int g, int b)
{
    painter -> setBrush(QBrush(QColor(r, g, b)));
    return 0;
}


void Qtx::refreshWindow()
{
    container -> setPixmap(*pixmap);
    container -> repaint();
    QCoreApplication::processEvents();
    container -> repaint();
    container -> setPixmap(*pixmap);
    qApp -> processEvents();
}

void Qtx::clearWindow()
{
    painter -> eraseRect(pixmap->rect());
//    painter -> setRenderHint(QPainter::Antialiasing);
    container -> setPixmap(*pixmap);
}


void Qtx::drawPixel(int x, int y, int red, int green, int blue)
{
    int t = thickness;
    setColor(red, green, blue, 1);
    drawLine(x, y, x, y);
    setColor(red, green, blue, t);
}
void Qtx::drawPixel(int x, int y, unsigned int color)
{
    int t = thickness;
    setColor(color, 1);
    drawLine(x, y, x, y);
    setColor(color, t);
}

void Qtx::getPixel(int x, int y, int *r, int *g, int *b)
{
    _LESSZERO(x);
    _LESSZERO(y);
    QColor c(pixmap -> toImage().pixel(QPoint(x,y)));
    *r = c.red();
    *g = c.green();
    *b = c.blue();
}

void Qtx::drawPolygon(const QTxPoint *points, int numPoints)
{
    QPolygon poly;
    for(int i = 0; i < numPoints; i++) poly << *points[i].p;
    painter -> drawPolygon(poly);
    if(!begin) container -> setPixmap(*pixmap); 
}


void Qtx::floodFill(int x, int y, QImage& image, QRgb oldColor, QRgb newColor)
{
   if (oldColor == newColor) return;

            QStack<QPoint> stk;
            QPoint pt;
 
            int y1;
            bool spanLeft, spanRight;
 
            stk.push(QPoint(x, y));
 
            while (!stk.empty()) {
                pt = stk.pop();
                x = pt.x();
                y = pt.y();
                y1 = y;
                while (y1 >= 0 && image.pixel(x, y1) != oldColor && image.pixel(x, y1) != newColor) y1--; // goes up till border
                y1++; // first pixel we need to redraw is under

                spanLeft = spanRight = false; // dont span to the left/right side
                while (y1 < image.height() && image.pixel(x, y1) != oldColor && image.pixel(x, y1) != newColor) {
                    image.setPixel(x, y1, newColor);
                    if (!spanLeft && x > 0 && image.pixel(x-1, y1) != oldColor  && image.pixel(x-1, y1) != newColor) {
                        stk.push(QPoint(x-1, y1));
                        spanLeft = true;
                    } else if(spanLeft && x > 0 && (image.pixel(x-1, y1) == oldColor || image.pixel(x-1, y1) == newColor)) {
                        spanLeft = false;
                    }
                    if (!spanRight && x < (image.width() - 1) && image.pixel(x+1, y1) != oldColor && image.pixel(x+1, y1) != newColor) {
                        stk.push(QPoint(x+1, y1));
                        spanRight = true;
                    } else if(spanRight && (x < image.width() - 1) && (image.pixel(x+1, y1) == oldColor || image.pixel(x+1, y1) == newColor)) {
                        spanRight = false;
                    }
                    y1++;
                }
            }
   painter -> drawImage(0,0, image);
   if(!begin) container -> setPixmap(*pixmap); 
}

void Qtx::floodFill(int x, int y, unsigned int oldColor)
{
  int r, g, b;
    _LESSZERO(x);
    _LESSZERO(y);
  getBrushColor(&r, &g, &b);
  QColor newColor(r, g, b);
  r = (oldColor>>16) & 0xff; 
  g = (oldColor>>8) & 0xff;
  b = (oldColor) & 0xff;
  QColor oC(r, g, b);
  QImage image = pixmap -> toImage();
  floodFill(x, y, image, oC.rgb(),  newColor.rgb());
}


void Qtx::setFont(const char *name, int sizeY, int sizeX, bool bold, bool italic, bool underline, bool strikeout, int angle)
{
    textangle = angle;
    font = new QFont(name, sizeY, -1, italic);
    font -> setBold(bold);
    font -> setStrikeOut(strikeout);
    font -> setUnderline(underline);
    painter -> setFont(*font);
    UNUSED(sizeX);
}
QPixmap *Qtx::loadImage(const char *filename, unsigned int flags, unsigned int lflags)
{
//    QImage image(filename);
    UNUSED(flags);
    UNUSED(lflags);
    return new QPixmap(filename);//image;
}
bool Qtx::copyImage(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, unsigned long rOp0)
{
    // painter.drawPixmap(pixmapOffset, pixmap);

    //    painter.save();
    //    painter.translate(newX, newY);
    //    painter.scale(scaleFactor, scaleFactor);
    //    QRectF exposed = painter.matrix().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
    //    painter.drawPixmap(exposed, pixmap, exposed);
    //    painter.restore();
    

    _LESSZERO(xDest);
    _LESSZERO(yDest);
    _LESSZERO(xSrc);
    _LESSZERO(ySrc);
/*    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    QImage isrc(src -> toImage());
    QImage idest(dest -> toImage());
    isrc.save(&buffer, "PNG"); 
    idest.loadFromData(ba, "PNG");
    if(dest ==  pixmap)
    {
	idest.setOffset(QPoint(xSrc, ySrc));
	painter -> drawImage(xDest, yDest, idest);
        if(!begin) container -> setPixmap(*pixmap); 
    }*/
    if(dest == pixmap)
    {
       painter -> drawPixmap(QRect(xDest, yDest, width, height), *src, QRect(xSrc, ySrc, width, height));
       if(!begin) container -> setPixmap(*pixmap); 
    }
//    UNUSED(width);
//    UNUSED(height);
    UNUSED(rOp0);
    return true;
}

bool Qtx::copyImageTr(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, unsigned int color)
{
    _LESSZERO(xDest);
    _LESSZERO(yDest);
    _LESSZERO(xSrc);
    _LESSZERO(ySrc);
    if(dest == pixmap)
    {
//       dest -> fill(Qt::Transparent);
       painter -> drawPixmap(QRect(xDest, yDest, width, height), *src, QRect(xSrc, ySrc, width, height));
       if(!begin) container -> setPixmap(*pixmap); 
    }
    UNUSED(color);
    return true;
}

bool Qtx::copyImageAlpha(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, double alpha)
{
    _LESSZERO(xDest);
    _LESSZERO(yDest);
    _LESSZERO(xSrc);
    _LESSZERO(ySrc);
    if(dest == pixmap)
    {
//       dest -> fill(Qt::Transparent);
       painter -> drawPixmap(QRect(xDest, yDest, width, height), *src, QRect(xSrc, ySrc, width, height));
       painter -> setOpacity(alpha);
       if(!begin) container -> setPixmap(*pixmap); 
    }
    return true;
}




unsigned Qtx::messageBox(const char *text, const char *header, unsigned flags)
{
    QMessageBox msgbox;
    msgbox.setWindowTitle(header);
    msgbox.setText(text);
    msgbox.setIcon(QMessageBox::Information);
    msgbox.setStandardButtons(QMessageBox::Ok);
    msgbox.setDefaultButton(QMessageBox::Ok);
    UNUSED(flags);
    return msgbox.exec();
}

const char *Qtx::inputBox(const char *text, const char *caption, const char *input)
{
    bool ok;
    static char s[1024];
    QString tx = QInputDialog::getText(  NULL,  QString(caption), QString(text), QLineEdit::Normal, QString(input), &ok);
    if(ok && !tx.isEmpty())
    {
	strcpy(s, tx.toStdString().c_str());
	return s;
    }
    return NULL;
}

void Qtx::notifyIcon(const char *title, const char *text, const char *filename = NULL)
{
//     QMenu *trayMenu = new QMenu(container);
//    trayMenu->addAction(text);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(container);
    if(filename == NULL)
        trayIcon -> setIcon(QIcon(*pixmap));
    else
        trayIcon -> setIcon(QIcon(filename));

//    trayIcon->setContextMenu(trayMenu);

    trayIcon->show();
    trayIcon->showMessage(QString(title), QString(text), QSystemTrayIcon::Information, 5000);
//    trayIcon->showMessage("Well...", "Here I should be I guess?");
}

/*
void Qtx::playSound(const char *filename)
{
//    QSound::play(filename);
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(filename));
    effect.setLoopCount(QSoundEffect::Infinite);
    effect.setVolume(0.50f);
    effect.play();
}
*/
QPushButton *Qtx::dlgButton(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    return container -> dlgButton(x, y, w, h, t, p, xml);
}

QTextEdit *Qtx::dlgTextEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    return container -> dlgTextEdit(x, y, w, h, t, p, xml);
}

QLineEdit *Qtx::dlgEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    return container -> dlgEdit(x, y, w, h, t, p, xml);
}

QLabel *Qtx::dlgLabel(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    return container -> dlgLabel(x, y, w, h, t, p, xml);
}

QCheckBox *Qtx::dlgCheckBox(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml)
{
    return container -> dlgCheckBox(x, y, w, h, t, state, p, xml);
}

QRadioButton *Qtx::dlgRadioButton(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml)
{
    return container -> dlgRadioButton(x, y, w, h, t, state, p, xml);
}

QGroupBox *Qtx::dlgGroupBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list)
{
    int n;
    QButtonGroup *buttongroup = container -> dlgButtonGroup(id, p, xml);
    QVBoxLayout *vbox = new QVBoxLayout;
    for(n = 0; list[n] != NULL; n++)
    {
        QRadioButton *radio1 = new QRadioButton(QString(list[n]), qtx -> container);
	    if(*id == n) radio1 -> setChecked(true);
        buttongroup -> addButton(radio1, n);
	vbox->addWidget(radio1);
        vbox->addStretch(1);
    }
    QGroupBox *groupbox = new QGroupBox(QString(t), qtx -> container);
    groupbox -> setGeometry(x, y, w, h);
    groupbox -> setLayout(vbox);
    groupbox -> show();
    return groupbox;
}

QComboBox *Qtx::dlgComboBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list)
{
    return container -> dlgComboBox(x, y, w, h, t, id, p, xml, list);
}

QListWidget *Qtx::dlgListBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list)
{
    return container -> dlgListBox(x, y, w, h, t, id, p, xml, list);
}
