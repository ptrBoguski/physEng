#include "Rigidbody.h"


Rigidbody::Rigidbody() : pImpl(new RigidbodyImpl()) {}

Rigidbody::~Rigidbody() {
  delete pImpl;
}

void Rigidbody::applyForce(const boost::numeric::ublas::vector<double>& force){
  pImpl->applyForce(force);
}

Rigidbody::RigidbodyImpl::RigidbodyImpl()
  : mass(1.0),
velocity(3),
position(3)
{
  velocity.clear();
  position.clear();
}

Rigidbody::RigidbodyImpl::~RigidbodyImpl() {}

void Rigidbody::RigidbodyImpl::applyForce(const boost::numeric::ublas::vector<double>& force){
  velocity += force;
}

boost::numeric::ublas::vector<double> Rigidbody::getVelocity() const {
  return pImpl->getVelocity();
}
boost::numeric::ublas::vector<double> Rigidbody::RigidbodyImpl::getVelocity() const {
  return velocity;
}
