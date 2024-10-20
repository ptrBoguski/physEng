#pragma once
#include "../rigidbody/SphericRigidbody.h"
#include "ICollisionDetection.h"
#include <boost/numeric/ublas/vector_expression.hpp>
// for debugging
#include "../../src/utils/VectorUtils.h"


class SphereCollisionDetection : public ICollisionDetection {
public:
  // This function is defined in the header file for performance reasons,
  // as it is small and frequently called, allowing for potential inlining.
  bool checkCollision(const Rigidbody &a, const Rigidbody &b) const override {
    const SphericRigidbody *sa = dynamic_cast<const SphericRigidbody *>(&a);
    const SphericRigidbody *sb = dynamic_cast<const SphericRigidbody *>(&b);

    if (sa && sb) {
      return checkSphereCollision(*sa, *sb);
    }
    return false;
  }

private:
  bool checkSphereCollision(const SphericRigidbody &a,
                            const SphericRigidbody &b) const {
    // Calculate the distance between the centers of the two spheres
    boost::numeric::ublas::vector<double> diff = a.getPosition() - b.getPosition();
    double distSq = boost::numeric::ublas::inner_prod(diff, diff);
    double radiusSum = a.getRadius() + b.getRadius();

    // Debug output
    /*std::cout << "Position A: " << a.getPosition()*/
    /*          << ", Position B: " << b.getPosition() << std::endl;*/
    /*std::cout << "Radius A: " << a.getRadius()*/
    /*          << ", Radius B: " << b.getRadius() << std::endl;*/
    /*std::cout << "Distance Squared: " << distSq*/
    /*          << ", Radius Sum Squared: " << (radiusSum * radiusSum)*/
    /*          << ", Diff: " << diff*/
    /*          << std::endl;*/

    // Check if distance squared is less than or equal to the sum of their radii
    return distSq <= (radiusSum * radiusSum);
  }
};
