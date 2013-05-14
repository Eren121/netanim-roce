#ifndef LOGQT_H
#define LOGQT_H

#include <QPointF>
#include <QRectF>
#include <iostream>

std::ostream & operator << (std::ostream & os, QPointF pt);
std::ostream & operator << (std::ostream & os, QRectF r);

#endif // LOGQT_H
