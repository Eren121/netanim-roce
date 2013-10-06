#ifndef LOGQT_H
#define LOGQT_H

#include <QPointF>
#include <QRectF>
#include <QTransform>
#include <iostream>
#include "animpacket.h"

std::ostream & operator << (std::ostream & os, QPointF pt);
std::ostream & operator << (std::ostream & os, QRectF r);
std::ostream & operator << (std::ostream & os, QTransform t);
std::ostream & operator << (std::ostream & os, AnimPacket * p);

#endif // LOGQT_H
