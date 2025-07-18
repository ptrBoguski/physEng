#ifndef IRIGIDBODY_H
#define IRIGIDBODY_H

#include <boost/numeric/ublas/vector.hpp>

class IRigidbody {
public:
  virtual ~IRigidbody() = default;
  
  virtual void applyForce(const boost::numeric::ublas::vector<double>& force) = 0;
  virtual void applyImpulse(const boost::numeric::ublas::vector<double>& force) = 0;
  virtual void update(double deltaTime) = 0;

  virtual double getMass() const = 0;
  virtual void setMass(double mass) = 0;
  virtual boost::numeric::ublas::vector<double> getVelocity() const = 0;
  virtual boost::numeric::ublas::vector<double> getPosition() const = 0;
  virtual void setPosition(boost::numeric::ublas::vector<double> position) = 0;
  virtual double getRestitution() const = 0;
  virtual void setRestitution(double restitution) = 0;
  virtual void resolveCollision(IRigidbody& other) = 0;

};

#endif // IRIGIDBODY_H
