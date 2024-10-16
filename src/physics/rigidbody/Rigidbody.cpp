#include "Rigidbody.h"

Rigidbody::Rigidbody() : pImpl(new RigidbodyImpl()) {}

Rigidbody::~Rigidbody() { delete pImpl; }

void Rigidbody::applyForce(const boost::numeric::ublas::vector<double> &force) {
  pImpl->applyForce(force);
}

Rigidbody::RigidbodyImpl::RigidbodyImpl()
    : mass(1.0), velocity(3), position(3) {
  velocity.clear();
  position.clear();
}

Rigidbody::RigidbodyImpl::~RigidbodyImpl() {}

void Rigidbody::RigidbodyImpl::applyForce(
    const boost::numeric::ublas::vector<double> &force) {
  velocity += force;
}

boost::numeric::ublas::vector<double> Rigidbody::getVelocity() const {
  return pImpl->getVelocity();
}
boost::numeric::ublas::vector<double>
Rigidbody::RigidbodyImpl::getVelocity() const {
  return velocity;
}

boost::numeric::ublas::vector<double> Rigidbody::getPosition() const {
  return pImpl->getPosition();
}
boost::numeric::ublas::vector<double>
Rigidbody::RigidbodyImpl::getPosition() const {
  return position;
}

void Rigidbody::update(double deltaTime) {
  // Update position and velocity based on delta time
  pImpl->update(deltaTime);
}
void Rigidbody::RigidbodyImpl::update(double deltaTime) {
  // Update position and velocity based on delta time
  position += velocity * deltaTime;
}

double Rigidbody::getMass() const { return pImpl->getMass(); }

double Rigidbody::RigidbodyImpl::getMass() const { return mass; }

void Rigidbody::RigidbodyImpl::setMass(double mass) { this->mass = mass; }

void Rigidbody::setMass(double mass) { pImpl->setMass(mass); }
