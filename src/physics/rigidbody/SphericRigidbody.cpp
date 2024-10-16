#include "../../../include/rigidbody/SphericRigidbody.h"

SphericRigidbody::SphericRigidbody(double radius, double mass) : radius(radius){
  this->mass = mass;
  velocity = boost::numeric::ublas::vector<double>(3);
  position = boost::numeric::ublas::vector<double>(3);

  velocity.clear();
  position.clear();
}

SphericRigidbody::~SphericRigidbody(){};

double SphericRigidbody::getRadius() const { return radius; }
void SphericRigidbody::setRadius(double radius) { this->radius = radius; }
