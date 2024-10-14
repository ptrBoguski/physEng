#ifndef RIGIDBODY_PRIVATE_H
#define RIGIDBODY_PRIVATE_H

#include "../../../include/rigidbody/Rigidbody.h"

class Rigidbody::RigidbodyImpl {
public:
  RigidbodyImpl();
  ~RigidbodyImpl();

  void applyForce(const boost::numeric::ublas::vector<double>& force);
  boost::numeric::ublas::vector<double> getVelocity() const;

private:
  double mass;
  boost::numeric::ublas::vector<double> velocity;
  boost::numeric::ublas::vector<double> position;
};



#endif // RIGIDBODY_PRIVATE_H
