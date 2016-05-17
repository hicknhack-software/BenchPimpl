#include "PlainPoint.h"

PlainPoint::PlainPoint(double x, double y) : m_x(x), m_y(y) {
}

double
PlainPoint::x() const {
  return m_x;
}

double
PlainPoint::y() const {
  return m_y;
}
