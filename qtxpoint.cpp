/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	QTxPoint class definition file.
	This class represents a simple point on the screen.
	
*/

QTxPoint::QTxPoint(int x, int y)
{ 
    p = new QPoint(x, y);
    X = x;
    Y = y;
}
