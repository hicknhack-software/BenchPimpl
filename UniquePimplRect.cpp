#include "UniquePimplRect.h"
#include "UniquePimplRect_p.h"

UniquePimplRect::Implementation::Implementation(double x, double y, double w, double h)
    : UniquePimplPoint::Implementation(x, y), w(w), h(h) {
}

double
UniquePimplRect::Implementation::sum() const {
  return x + y + w + h;
}

UniquePimplRect::UniquePimplRect(double x, double y, double w, double h)
    : UniquePimplPoint(new Implementation(x, y, w, h)) {
}

double
UniquePimplRect::width() const {
  return p<Implementation>()->w;
}

double
UniquePimplRect::height() const {
  return p<Implementation>()->h;
}

double
UniquePimplRect::sum() const {
  return p<Implementation>()->sum();
}

UniquePimplRect::UniquePimplRect(UniquePimplRect::Implementation* implementation)
    : UniquePimplPoint(implementation) {
}
