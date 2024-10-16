#include "../../../include/rigidbody/SphericRigidbody.h"

SphericRigidbody::SphericRigidbody(double radius) : radius(radius) {
  mass = 1.0;

  velocity = boost::numeric::ublas::vector<double>(3);
  position = boost::numeric::ublas::vector<double>(3);

  velocity.clear();
  position.clear();
}

SphericRigidbody::~SphericRigidbody(){};

double SphericRigidbody::getRadius() const { return radius; }
void SphericRigidbody::setRadius(double radius) { this->radius = radius; }
