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

#include "../../include/rigidbody/Rigidbody.h"

class TestRigidbody : public Rigidbody {
public:
  TestRigidbody(double mass) {
    this->mass = mass;
    velocity = boost::numeric::ublas::vector<double>(3);
    velocity.clear();
    position = boost::numeric::ublas::vector<double>(3);
    position.clear();
  }
};

class RigidbodyTest : public ::testing::Test {
protected:
  TestRigidbody *rigidbody;

  void SetUp() override { rigidbody = new TestRigidbody(2.0); }

  void TearDown() override { delete rigidbody; }
};

TEST_F(RigidbodyTest, ApplyForceUpdatesVelocity) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 0.0;
  force(2) = 0.0;
  rigidbody->applyForce(force);
  EXPECT_DOUBLE_EQ(rigidbody->getVelocity()(0), 0.5);
}

TEST_F(RigidbodyTest, UpdateChangesPosition) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 0.0;
  force(2) = 0.0;
  std::cout << "Initial Position: " << rigidbody->getPosition()(0) << std::endl;
  rigidbody->applyForce(force);
  rigidbody->update(5.0);
  std::cout << "Updated Position: " << rigidbody->getPosition()(0) << std::endl;
  EXPECT_DOUBLE_EQ(rigidbody->getPosition()(0), 2.5);
}
TEST_F(RigidbodyTest, GetAndSetMass) {
  EXPECT_DOUBLE_EQ(rigidbody->getMass(), 2.0);
  rigidbody->setMass(3.0);
  EXPECT_DOUBLE_EQ(rigidbody->getMass(), 3.0);
}
