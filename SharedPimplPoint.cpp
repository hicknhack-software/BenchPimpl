#include "SharedPimplPoint.h"
#include "SharedPimplPoint_p.h"

SharedPimplPoint::Implementation::Implementation(double x, double y) : x(x), y(y) {
}

SharedPimplPoint::SharedPimplPoint(double x, double y)
    : Base(std::make_shared<Implementation>(x, y)) {
}

double
SharedPimplPoint::x() const {
  return p<Implementation>()->x;
}

double
SharedPimplPoint::y() const {
  return p<Implementation>()->y;
}

SharedPimplPoint::SharedPimplPoint(std::shared_ptr<SharedPimplPoint::Implementation> implementation)
    : Base(implementation) {
}
