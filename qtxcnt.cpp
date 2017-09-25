/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	QTxContainer class definition file.
	This class represents a window (or working surface) to draw or to create an interface with some dialog controls.
	It also provides handling of mouse/keyboard/timer events.
	
*/

QTxContainer::QTxContainer()
{
    keyhandler = NULL;
    mousehandler = NULL;
    timerhandler = NULL;
    events = NULL; 
    thparam = NULL;
}

QTxContainer::~QTxContainer()
{
}

void QTxContainer::keyPressEvent(QKeyEvent *event)
{
   if(keyhandler != NULL)
        keyhandler(event -> key());
}

void QTxContainer::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(mousehandler != NULL)
       mousehandler(event -> globalX(), event -> globalY(), event -> button(), true);
}

void QTxContainer::mouseMoveEvent(QMouseEvent *event)
{
    if(mousehandler != NULL)
       mousehandler(event -> globalX(), event -> globalY(), event -> button(), false);
}

void QTxContainer::mousePressEvent(QMouseEvent * event)
{
    if(mousehandler != NULL)
       mousehandler(event -> globalX(), event -> globalY(), event -> button(), false);
}

void QTxContainer::timerEvent(QTimerEvent *event)
{
    if(timerhandler != NULL)
        timerhandler(thparam);
    UNUSED(event);
}

void QTxContainer::addevent(QObject *sender, void(*handler)(), void *data, QPushButton *button, QTextEdit *textedit, 
                        QLabel *label, QLineEdit *edit, QCheckBox *checkbox, QRadioButton *radiobutton, 
                        QButtonGroup *buttongroup, QComboBox *combobox, QListWidget *list)
{
    int i = 0;
    if(events != NULL)
	for(; events[i] != NULL; i++);
    events = (___QTXCONTROLEVENT**)realloc(events, (i+2) * sizeof(___QTXCONTROLEVENT*));
    events[i] = (___QTXCONTROLEVENT*)malloc(sizeof(___QTXCONTROLEVENT));
    events[i] -> handler = handler;
    events[i] -> sender = sender;
    events[i] -> data = data;
    events[i] -> button = button;
    events[i] -> textedit = textedit;
    events[i] -> edit = edit;
    events[i] -> label = label;
    events[i] -> checkbox = checkbox;
    events[i] -> radiobutton  = radiobutton;
    events[i] -> buttongroup  = buttongroup;
    events[i] -> combobox  = combobox;
    events[i] -> list  = list;
    events[i+1] = NULL;
}

QPushButton *QTxContainer::dlgButton(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    QPushButton *widget = new QPushButton(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
    QObject::connect(widget, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    widget -> show();
    addevent(widget, p, NULL, widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QTextEdit *QTxContainer::dlgTextEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    QTextEdit *widget = new QTextEdit(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
    QObject::connect(widget, SIGNAL(textChanged()), this, SLOT(textChangedSlot()));
    widget -> show();
    addevent(widget, p, (void*)t, NULL, widget, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QLabel *QTxContainer::dlgLabel(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    QLabel *widget = new QLabel(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
//    QObject::connect(widget, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    widget -> show();
    addevent(widget, p, NULL, NULL, NULL, widget, NULL, NULL, NULL, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}


QLineEdit *QTxContainer::dlgEdit(int x, int y, int w, int h, char *t, void(*p)(), char *xml)
{
    QLineEdit *widget = new QLineEdit(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
    QObject::connect(widget, SIGNAL(editingFinished()), this, SLOT(textChangedSlot()));
    widget -> show();
    addevent(widget, p, (void*)t, NULL, NULL, NULL, widget, NULL, NULL, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QCheckBox *QTxContainer::dlgCheckBox(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml)
{
    QCheckBox *widget = new QCheckBox(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
    if(*state == true)
	widget -> setCheckState(Qt::Checked); else  widget -> setCheckState(Qt::Unchecked);
    QObject::connect(widget, SIGNAL(stateChanged(int)), this, SLOT(stateChangedSlot(int)));
    widget -> show();
    addevent(widget, p, (void*)state, NULL, NULL, NULL, NULL, widget, NULL, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QRadioButton *QTxContainer::dlgRadioButton(int x, int y, int w, int h, char *t, bool *state, void(*p)(), char *xml)
{
    QRadioButton *widget = new QRadioButton(this);
    widget -> setText(t);
    widget -> setGeometry(x, y, w, h);
    widget -> setChecked(*state);
    QObject::connect(widget, SIGNAL(toggled(bool)), this, SLOT(toggledSlot(bool)));
    widget -> show();
    addevent(widget, p, (void*)state, NULL, NULL, NULL, NULL, NULL, widget, NULL, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QButtonGroup *QTxContainer::dlgButtonGroup(int *id, void(*p)(), char *xml)
{
    QButtonGroup *widget = new QButtonGroup(this);
    QObject::connect(widget, SIGNAL(buttonClicked(int)), this, SLOT(stateChangedSlot(int)));
    addevent(widget, p, (void*)id, NULL, NULL, NULL, NULL, NULL, NULL, widget, NULL, NULL);
    UNUSED(xml);
    return widget;
}

QComboBox *QTxContainer::dlgComboBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list)
{
    QComboBox *widget = new QComboBox(this);
//    if(t != NULL)  widget -> lineEdit() -> setText(t);
    widget -> setGeometry(x, y, w, h);
    for(int i = 0; list[i] != NULL; i++) widget -> addItem(QString(list[i]));
    QObject::connect(widget, SIGNAL(activated(int)), this, SLOT(stateChangedSlot(int)));
    widget -> setCurrentIndex(*id);
    widget -> show();
    addevent(widget, p, (void*)id, NULL, NULL, NULL, NULL, NULL, NULL, NULL, widget, NULL);
    UNUSED(t);
    UNUSED(xml);
    return widget;
}

QListWidget *QTxContainer::dlgListBox(int x, int y, int w, int h, char *t, int *id, void(*p)(), char *xml, char **list)
{
    QListWidget *widget = new QListWidget(this);
    widget -> setGeometry(x, y, w, h);
    for(int i = 0; list[i] != NULL; i++) widget -> addItem(QString(list[i]));
    QObject::connect(widget, SIGNAL(currentRowChanged(int)), this, SLOT(stateChangedSlot(int)));
    widget -> setCurrentRow(*id);
    widget -> show();
    addevent(widget, p, (void*)id, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, widget);
    UNUSED(t);
    UNUSED(xml);
    return widget;
}

void QTxContainer::clickedSlot()
{
    for(int i = 0; events[i] != NULL; i++)
	if(events[i] -> sender == sender())
	{
	    if(events[i] -> handler != NULL)
		events[i] -> handler();
	    break;
	}
}

void QTxContainer::textChangedSlot()
{
    for(int i = 0; events[i] != NULL; i++)
	if(events[i] -> sender == sender())
	{
	    if(events[i] -> textedit != NULL)
	    {
		QString s(events[i] -> textedit -> toPlainText());
		strcpy((char*)events[i] -> data,  s.toStdString().c_str());
	    }
	    if(events[i] -> edit != NULL)
	    {
		QString s(events[i] -> edit -> displayText());
		strcpy((char*)events[i] -> data,  s.toStdString().c_str());
	    }
	    if(events[i] -> handler != NULL)
		events[i] -> handler();
	    break;
	}
}

void QTxContainer::stateChangedSlot(int state)
{
    for(int i = 0; events[i] != NULL; i++)
	if(events[i] -> sender == sender())
	{
	    if(events[i] -> checkbox != NULL)
	    {
		if(state == Qt::Checked)
		    *(bool*)events[i] -> data = true;
		else
		    *(bool*)events[i] -> data = false;
		
	    }
	    if(events[i] -> buttongroup != NULL)
		*(int*)events[i] -> data = state;

	    if(events[i] -> combobox != NULL)
		*(int*)events[i] -> data = state;
		
	    if(events[i] -> list != NULL)
		*(int*)events[i] -> data = state;

	    if(events[i] -> handler != NULL)
		events[i] -> handler();
	    break;
	}
}
void QTxContainer::toggledSlot(bool checked)
{
    for(int i = 0; events[i] != NULL; i++)
	if(events[i] -> sender == sender())
	{
	    if(events[i] -> radiobutton != NULL)
		*(bool*)events[i] -> data = checked;
		
	    if(events[i] -> handler != NULL)
		events[i] -> handler();
	    break;
	}
}
