/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	QTxPoint class definition file.
	This class represents a simple point on the screen.
	
*/

#ifndef QTXPOINT_H
#define QTXPOINT_H

#include <QPoint>

class QTXLIBSHARED_EXPORT QTxPoint
{
public:
    QTxPoint(int x, int y);
    QPoint* p;
    int X, Y;
};

#endif
