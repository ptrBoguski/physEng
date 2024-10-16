#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "IRigidbody.h"

class Rigidbody : public IRigidbody {
public:
  Rigidbody();
  ~Rigidbody();

  void applyForce(const boost::numeric::ublas::vector<double>& force) override;
  void update(double deltaTime) override;

  double getMass() const override;
  void setMass(double mass) override;
  boost::numeric::ublas::vector<double> getVelocity() const override;
  boost::numeric::ublas::vector<double> getPosition() const override;

private:
  class RigidbodyImpl;
  RigidbodyImpl* pImpl;
};

#endif // RIGIDBODY_H
