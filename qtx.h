/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	Qtx class definition file.
	This class represents an environment to draw or to create an interface with dialog controls.
	
*/

#ifndef QTX_H
#define QTX_H

#include "qtxglobal.h"
#include "qtxpoint.h"
#include "qtxcnt.h"

class QTXLIBSHARED_EXPORT Qtx
{

public:
    Qtx(char *s);
    ~Qtx();
    QPixmap* getPixmap();
    void setDefaults();
    int createWindow(int, int);
    int createWindow(int, int, int, int);
    inline void ___createWindow(int, int, int, int);
    void refreshWindow();
    void clearWindow();
    int exec();
    void beginDraw();
    void endDraw();
    int getExtentX();
    int getExtentY();
    void getWindowRect(int *x, int *y, int *x1, int *y1);
    void getPenColor(int *r, int *g, int *b);
    void getBrushColor(int *r, int *g, int *b);
    int setColor(unsigned int color, int thickness);
    int setColor(int r, int g, int b, int thickness);
    int setFillColor(unsigned int color);
    int setFillColor(int r, int g, int b);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawCircle(int x, int y, int radius);
    void drawEllipse(int x1, int y1, int radius1, int radius2);
    void drawRectangle(int x1, int y1, int x2, int y2);
    int drawText(int x, int y, int w, int h, int flags, const QString &text);
    void drawPixel(int x, int y, int red, int green, int blue);
    void drawPixel(int x, int y, unsigned int color);
    void getPixel(int x, int y, int *r, int *g, int *b);
    void drawPolygon (const QTxPoint* points, int numPoints);
    void drawArc(int x0, int y0, int x1, int y1, int startAngle, int totalAngle);
    void drawPie(int x0, int y0, int x1, int y1, int startAngle, int totalAngle);
    void drawChord(int x0, int y0, int x1, int y1, int startAngle, int totalAngle);
    void drawTriangle (double x1, double y1, double x2, double y2, double x3, double y3);
    void floodFill(int x, int y, unsigned int oldColor);
    void floodFill(int x, int y, QImage& image, QRgb oldColor, QRgb newColor);
    void setTextAlign(unsigned int a);
    void getTextExtent(const char *s, int *w, int *h);
    int getTextExtentX(const char *s);
    int getTextExtentY(const char *s);
    void setFont(const char *name, int sizeY, int sizeX, bool bold, bool italic, bool underline, bool strikeout, int angle);
    void msleep(unsigned long ms);
    bool in(QPoint p, int x, int y, int x1, int y1);
    QImage *toImage();
    QPixmap *createDC(int x, int y, unsigned char *data, int size);
    QPixmap *loadImage(const char *filename, unsigned int flags, unsigned int lflags);
    void drawImage(int x, int y, QPixmap image);
    bool copyImage(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, unsigned long rOp0);
    bool copyImageTr(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, unsigned int color);
    bool copyImageAlpha(QPixmap *dest, int xDest, int yDest, int width, int height, QPixmap *src, int xSrc, int ySrc, double alpha);
    void addKeyHandler(void (*handler)(int));
    void addMouseHandler(void (*handler)(int, int, int, bool));
    void addTimerHandler(void (*handler)(void *p), void *p, unsigned time);
    unsigned messageBox(const char *text, const char *header, unsigned flags);
    const char *inputBox(const char *text, const char *caption, const char *input);
    void notifyIcon(const char *title, const char *text, const char *filename);
    QPushButton *dlgButton(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QTextEdit *dlgTextEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QLineEdit *dlgEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QLabel *dlgLabel(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QCheckBox *dlgCheckBox(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml);
    QRadioButton *dlgRadioButton(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml);
    QGroupBox *dlgGroupBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list);
    QComboBox *dlgComboBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list);
    QListWidget *dlgListBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list);
//  void playSound(const char *filename);

//private:
    QPainter *painter;
    QPixmap *pixmap;
    QTxContainer *container;
    QDialog *dialog;
    QFont *font;
    QApplication *app;
    int argc;
    char *argv[2];
    char *title;
    int screenWidth;
    int screenHeight;
    int windowWidth;
    int windowHeight;
    int textangle;
    int textalign;
    int thickness;
    bool begin;
};

#endif
