#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <boost/numeric/ublas/vector.hpp>

class Rigidbody {
public:
  Rigidbody();
  ~Rigidbody();

  void applyForce(const boost::numeric::ublas::vector<double>& force);
  void update(double deltaTime);

  double getMass() const;
  void setMass(double mass);
  boost::numeric::ublas::vector<double> getVelocity() const;

private:
  class RigidbodyImpl;
  RigidbodyImpl* pImpl;
};

#endif // RIGIDBODY_H
