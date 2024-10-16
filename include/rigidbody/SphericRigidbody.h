#ifndef SPHERIC_RIGIDBODY_H
#define SPHERIC_RIGIDBODY_H

#include "Rigidbody.h"

class SphericRigidbody : public Rigidbody {
public:
  SphericRigidbody(double radius, double mass);
  virtual ~SphericRigidbody();

  double getRadius() const;
  void setRadius(double radius);

protected:
  double radius;
};

#endif // SPHERIC_RIGIDBODY_H
