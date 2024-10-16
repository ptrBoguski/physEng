#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "IRigidbody.h"

class Rigidbody : public IRigidbody {
public:
  virtual ~Rigidbody() = default;

  void applyForce(const boost::numeric::ublas::vector<double>& force) override{
    velocity += force / mass;
  };
  void update(double deltaTime) override{
    position += velocity * deltaTime;
  };

  double getMass() const override {
    return mass;
  };
  void setMass(double mass) override {
    this->mass = mass;
  };
  boost::numeric::ublas::vector<double> getVelocity() const override {
    return velocity;
  };
  boost::numeric::ublas::vector<double> getPosition() const override {
    return velocity;
  };

protected:
  double mass;
  boost::numeric::ublas::vector<double> velocity;
  boost::numeric::ublas::vector<double> position;
};

#endif // RIGIDBODY_H
