#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "IRigidbody.h"
#include <boost/numeric/ublas/vector_expression.hpp>

class Rigidbody : public IRigidbody {
public:
  virtual ~Rigidbody() = default;

  void applyForce(const boost::numeric::ublas::vector<double>& force) override{
    accumulatedForce += force;
  }
  void applyImpulse(const boost::numeric::ublas::vector<double>& force) override{
    velocity += force / mass;
  }
  void update(double deltaTime) override{
    applyImpulse(accumulatedForce);
    accumulatedForce.clear();
    position += velocity * deltaTime;
  }
  double getMass() const override {
    return mass;
  }
  void setMass(double mass) override {
    this->mass = mass;
  }
  boost::numeric::ublas::vector<double> getVelocity() const override {
    return velocity;
  }
  boost::numeric::ublas::vector<double> getPosition() const override {
    return position;
  }
  void setPosition(boost::numeric::ublas::vector<double> position) override {
    this->position = position;
  }
  void setRestitution(double restitution) override {
    this->restitution = restitution;
  }
  double getRestitution() const override {
    return restitution;
  }
  // TODO fix for inf mass
  void resolveCollision(IRigidbody& other) override {
    // Calculate the normal vector between two rigidbodies
    boost::numeric::ublas::vector<double> normal = other.getPosition() - this->getPosition();
    double distance = boost::numeric::ublas::norm_2(normal);

    //normalize 
    if (distance > 0.0){
      normal /= distance;
    }

    // Calculate the relative velocity
    boost::numeric::ublas::vector<double> relativeVelocity = other.getVelocity() - this->getVelocity();
    double velocityAlongNormal = boost::numeric::ublas::inner_prod(relativeVelocity, normal);

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0){
      return;
    }

    //calculate effective restitution
    double effectiveRestitution = std::min(this->getRestitution(), other.getRestitution());

    //calculate impulse force
    double impulseScalar = -(1 + effectiveRestitution) * velocityAlongNormal;
    impulseScalar /= (1 / this->getMass() + 1 / other.getMass());
  
    boost::numeric::ublas::vector<double> impulse = impulseScalar * normal;

    this->applyImpulse(-impulse);
    other.applyImpulse(impulse);
  }

  
protected:
  double mass;
  boost::numeric::ublas::vector<double> velocity;
  boost::numeric::ublas::vector<double> position;
  boost::numeric::ublas::vector<double> accumulatedForce;
  double restitution = 1;
};

#endif // RIGIDBODY_H
