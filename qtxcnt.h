/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	QTxContainer class definition file.
	This class represents a window (or working surface) to draw or to create an interface with some dialog controls.
	It also provides handling of mouse/keyboard/timer events.
	
*/

#ifndef QTXCNT_H
#define QTXCNT_H

#include <QLabel>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QComboBox>
#include <QListWidget>

typedef struct
{
    void(*handler)();
    void *data;
    QObject *sender;
    QTextEdit *textedit;
    QLineEdit *edit;
    QPushButton *button;
    QLabel *label;
    QCheckBox *checkbox;
    QRadioButton *radiobutton;
    QButtonGroup *buttongroup;
    QComboBox *combobox;
    QListWidget *list;
} ___QTXCONTROLEVENT;


class QTxContainer : public QLabel
{
Q_OBJECT

public:
    QTxContainer();
    virtual ~QTxContainer();
    void (*keyhandler)(int);
    void (*mousehandler)(int, int, int, bool);
    void (*timerhandler)(void*);
    QPushButton *dlgButton(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QTextEdit *dlgTextEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QLineEdit *dlgEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QLabel *dlgLabel(int x, int y, int w, int h, char *t, void(*p)(), char *xml);
    QCheckBox *dlgCheckBox(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml);
    QRadioButton *dlgRadioButton(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml);
    QButtonGroup *dlgButtonGroup(int *id, void(*p)(), char *xml);
    QComboBox *dlgComboBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list);
    QListWidget *dlgListBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list);
    void addevent(QObject *sender, void(*handler)(), void *data, QPushButton *button, QTextEdit *textedit, 
                  QLabel *label, QLineEdit *edit, QCheckBox *checkbox, QRadioButton *radiobutton, 
                  QButtonGroup *buttongroup, QComboBox *combobox, QListWidget *list);
    ___QTXCONTROLEVENT **events;
    void *thparam;
public slots:
  void clickedSlot();
  void stateChangedSlot(int);
  void toggledSlot(bool);
  void textChangedSlot();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void timerEvent(QTimerEvent *event);
};

#endif
