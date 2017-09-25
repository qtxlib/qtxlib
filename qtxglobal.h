/*
	QTXLib, (c) E.Gaevsky, A.Legalov, 2016.
	Simple cross-platform graphics library. Based on QT.


	Global macros definition file.
	It used when macro EXTERN_QTX is defined (user project linked with libqtx.so).
	
*/

#ifndef QTXGLOBAL_H
#define QTXGLOBAL_H

#include <QtCore/qglobal.h>
#include <QApplication>
#include <QPainter>
#include <QImage>
#include <QDesktopWidget>
#include <QGraphicsTextItem>
#include <QTime>
#include <QStack>
#include <QMessageBox>
#include <QInputDialog>
#include <QSystemTrayIcon>
#include <QBuffer>
//#include <QSoundEffect>
#include <stdio.h>


//#if defined(QTXLIB_LIBRARY)
#define QTXLIBSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define QTXLIBSHARED_EXPORT Q_DECL_IMPORT
//#endif

#ifndef UNUSED
#define UNUSED(p) (void)p // prevents 'unused parameter' compiler warnings
#endif

#endif
