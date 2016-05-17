#include "ChainedPimplRect.h"

class ChainedPimplRect::Implementation : protected chained::Implementation<ChainedPimplRect> {
public:
  Implementation(double w, double h) : w(w), h(h) {
  }

  double
  sum() const {
    return w + h + i()->x() + i()->y();
  }

  double w, h;
};

ChainedPimplRect::ChainedPimplRect(double x, double y, double w, double h)
    : ChainedPimplPoint(x, y) {
  new (p(this)) Implementation(w, h);
}

ChainedPimplRect::~ChainedPimplRect() {
  p(this)->~Implementation();
}

ChainedPimplRect*
ChainedPimplRect::create(double x, double y, double w, double h) {
  return chained::create<Interface>(x, y, w, h);
}

std::shared_ptr<ChainedPimplRect>
ChainedPimplRect::make_shared(double x, double y, double w, double h) {
  return chained::make_shared<Interface>(x, y, w, h);
}

double
ChainedPimplRect::width() const {
  return p(this)->w;
}

double
ChainedPimplRect::height() const {
  return p(this)->h;
}

double
ChainedPimplRect::sum() const {
  return p(this)->sum();
}

size_t
ChainedPimplRect::implementation_size() {
  return chained::implementation_size<Interface>() + ChainedPimplPoint::implementation_size();
}
