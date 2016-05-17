#include "SharedPimplRect.h"
#include "SharedPimplRect_p.h"

SharedPimplRect::Implementation::Implementation(double x, double y, double w, double h)
    : SharedPimplPoint::Implementation(x, y), w(w), h(h) {
}

double
SharedPimplRect::Implementation::sum() const {
  return x + y + w + h;
}

SharedPimplRect::SharedPimplRect(double x, double y, double w, double h)
    : SharedPimplPoint(std::make_shared<Implementation>(x, y, w, h)) {
}

double
SharedPimplRect::width() const {
  return p<Implementation>()->w;
}

double
SharedPimplRect::height() const {
  return p<Implementation>()->h;
}

double
SharedPimplRect::sum() const {
  return p<Implementation>()->sum();
}

SharedPimplRect::SharedPimplRect(std::shared_ptr<SharedPimplRect::Implementation> implementation)
    : SharedPimplPoint(implementation) {
}
