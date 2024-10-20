#include "../../include/rigidbody/SphericRigidbody.h"
#include <boost/numeric/ublas/vector.hpp>
#include <gtest/gtest.h>

class SphericRigidbodyTest : public ::testing::Test {
protected:
  SphericRigidbody *sphericRigidbody;

  void SetUp() override { sphericRigidbody = new SphericRigidbody(10.0, 1.0); }

  void TearDown() override { delete sphericRigidbody; }
};

TEST_F(SphericRigidbodyTest, ConstructorInitializesCorrectly) {
  EXPECT_DOUBLE_EQ(sphericRigidbody->getRadius(), 10.0);
  EXPECT_DOUBLE_EQ(sphericRigidbody->getMass(), 1.0);
  boost::numeric::ublas::vector<double> initialVelocity =
      sphericRigidbody->getVelocity();
  boost::numeric::ublas::vector<double> initialPosition =
      sphericRigidbody->getPosition();
  EXPECT_EQ(initialVelocity.size(), 3);
  EXPECT_EQ(initialPosition.size(), 3);
  for (std::size_t i = 0; i < 3; ++i) {
    EXPECT_DOUBLE_EQ(initialVelocity(i), 0.0);
    EXPECT_DOUBLE_EQ(initialPosition(i), 0.0);
  }
}

TEST_F(SphericRigidbodyTest, ApplyImpulseUpdatesVelocity) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 2.0;
  force(2) = 3.0;

  sphericRigidbody->applyImpulse(force);

  boost::numeric::ublas::vector<double> expectedVelocity = force;
  boost::numeric::ublas::vector<double> actualVelocity =
      sphericRigidbody->getVelocity();
  EXPECT_EQ(expectedVelocity.size(), actualVelocity.size());
  for (std::size_t i = 0; i < expectedVelocity.size(); ++i) {
    EXPECT_NEAR(expectedVelocity(i), actualVelocity(i), 1e-5);
  }
}

TEST_F(SphericRigidbodyTest, UpdateUpdatesPosition) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 2.0;
  force(2) = 3.0;

  sphericRigidbody->applyImpulse(force);

  double deltaTime = 1.0;
  sphericRigidbody->update(deltaTime);

  boost::numeric::ublas::vector<double> expectedPosition = force;
  boost::numeric::ublas::vector<double> actualPosition =
      sphericRigidbody->getPosition();

  EXPECT_EQ(expectedPosition.size(), actualPosition.size());
  for (std::size_t i = 0; i < expectedPosition.size(); ++i) {
    EXPECT_NEAR(expectedPosition(i), actualPosition(i), 1e-5);
  }
}
TEST_F(SphericRigidbodyTest, GetRadius) {
  EXPECT_DOUBLE_EQ(sphericRigidbody->getRadius(), 10.0);
}

TEST_F(SphericRigidbodyTest, SetRadius) {
  sphericRigidbody->setRadius(2.0);
  EXPECT_DOUBLE_EQ(sphericRigidbody->getRadius(), 2.0);
}

TEST_F(SphericRigidbodyTest, SetRadiusNegative) {
  EXPECT_THROW(sphericRigidbody->setRadius(-1.0), std::invalid_argument);
}

TEST_F(SphericRigidbodyTest, SetRadiusZero) {
  sphericRigidbody->setRadius(0.0);
  EXPECT_DOUBLE_EQ(sphericRigidbody->getRadius(), 0.0);
}

TEST_F(SphericRigidbodyTest, SetRadiusLargeValue) {
  sphericRigidbody->setRadius(1000.0);
  EXPECT_DOUBLE_EQ(sphericRigidbody->getRadius(), 1000.0);
}

TEST_F(SphericRigidbodyTest, DestructorWorksCorrectly) {
  // This test is implicit; if the destructor has issues, it will likely cause a
  // crash or memory leak.
}
