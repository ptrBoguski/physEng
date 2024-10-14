#include <gtest/gtest.h>
#include <boost/numeric/ublas/vector.hpp>
#include "../../include/rigidbody/Rigidbody.h"

TEST(RigidbodyTest, ApplyForceUpdatesVelocity){
  Rigidbody rb;
  boost::numeric::ublas::vector<double> initialVelocity(3);
  initialVelocity.clear();

  // Apply Force
  boost::numeric::ublas::vector<double> force(3); 
  force(0) = 1.0;
  force(1) = 2.0;
  force(2) = 3.0;

  rb.applyForce(force);

  //Check if the velocity is updated correctly
  boost::numeric::ublas::vector<double> expectedVelocity = force;
  boost::numeric::ublas::vector<double> actualVelocity = rb.getVelocity();
  EXPECT_EQ(expectedVelocity.size(), actualVelocity.size());
  for (std::size_t i = 0; i < expectedVelocity.size(); ++i) {
    EXPECT_NEAR(expectedVelocity(i), actualVelocity(i), 1e-5);
  }
}

