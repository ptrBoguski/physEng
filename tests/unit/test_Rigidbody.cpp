#include "../../include/rigidbody/SphericRigidbody.h"
#include <boost/numeric/ublas/vector.hpp>
#include <gtest/gtest.h>

TEST(SphericRigidbodyTest, ApplyForceUpdatesVelocity) {
  SphericRigidbody rb(10.0, 1.0);
  boost::numeric::ublas::vector<double> initialVelocity(3);
  initialVelocity.clear();

  // Apply Force
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 2.0;
  force(2) = 3.0;

  rb.applyForce(force);

  // Check if the velocity is updated correctly
  boost::numeric::ublas::vector<double> expectedVelocity = force;
  boost::numeric::ublas::vector<double> actualVelocity = rb.getVelocity();
  EXPECT_EQ(expectedVelocity.size(), actualVelocity.size());
  for (std::size_t i = 0; i < expectedVelocity.size(); ++i) {
    EXPECT_NEAR(expectedVelocity(i), actualVelocity(i), 1e-5);
  }
}
TEST(SphericRigidbodyTest, UpdateUpdatesPosition) {
  SphericRigidbody rb(10.0, 1.0);

  // Apply Force
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 2.0;
  force(2) = 3.0;

  rb.applyForce(force);

  // Update to update position
  double deltaTime = 1.0;
  rb.update(deltaTime);

  // Check if the position is updated correctly

  boost::numeric::ublas::vector<double> expectedPosition = force;
  boost::numeric::ublas::vector<double> actualPosition = rb.getPosition();

  EXPECT_EQ(expectedPosition.size(), actualPosition.size());
  for (std::size_t i = 0; i < expectedPosition.size(); ++i) {
    EXPECT_NEAR(expectedPosition(i), actualPosition(i), 1e-5);
  }
}
