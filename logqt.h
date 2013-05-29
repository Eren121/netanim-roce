#ifndef LOGQT_H
#define LOGQT_H

#include <QPointF>
#include <QRectF>
#include <QTransform>
#include <iostream>

std::ostream & operator << (std::ostream & os, QPointF pt);
std::ostream & operator << (std::ostream & os, QRectF r);
std::ostream & operator << (std::ostream & os, QTransform t);

#endif // LOGQT_H
