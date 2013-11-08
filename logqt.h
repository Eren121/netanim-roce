#ifndef LOGQT_H
#define LOGQT_H

#include <QPointF>
#include <QRectF>
#include <QTransform>
#include <iostream>
#include "animpacket.h"

namespace netanim {
std::ostream & operator << (std::ostream & os, QPointF pt);
std::ostream & operator << (std::ostream & os, QRectF r);
std::ostream & operator << (std::ostream & os, QTransform t);
std::ostream & operator << (std::ostream & os, AnimPacket * p);

void logQString (QString msg);
void logQString (bool b);

}

#endif // LOGQT_H
