#include "logqt.h"

std::ostream & operator << (std::ostream & os, QPointF pt)
{
  os << "QPointF [x,y]:[" << pt.x() << "," << pt.y() << "]";
  return os;
}

std::ostream & operator << (std::ostream & os, QRectF r)
{
  os << "QRectF topLeft:" << r.topLeft() << " bottomRight:" << r.bottomRight();
  return os;
}


std::ostream & operator << (std::ostream & os, QTransform t)
{
    os << "QTransform m11:" << t.m11() << " m22:" << t.m22();
    return os;
}
