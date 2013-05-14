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


