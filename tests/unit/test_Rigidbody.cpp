#include "../../include/rigidbody/Rigidbody.h"
#include <boost/numeric/ublas/vector.hpp>
#include <gtest/gtest.h>

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
TEST_F(RigidbodyTest, ApplyImpulseUpdatesVelocity) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 0.0;
  force(2) = 0.0;
  rigidbody->applyImpulse(force);
  EXPECT_DOUBLE_EQ(rigidbody->getVelocity()(0), 0.5);
}

TEST_F(RigidbodyTest, UpdateChangesPosition) {
  boost::numeric::ublas::vector<double> force(3);
  force(0) = 1.0;
  force(1) = 0.0;
  force(2) = 0.0;
  rigidbody->applyImpulse(force);
  rigidbody->update(5.0);
  EXPECT_DOUBLE_EQ(rigidbody->getPosition()(0), 2.5);
}
TEST_F(RigidbodyTest, GetAndSetMass) {
  EXPECT_DOUBLE_EQ(rigidbody->getMass(), 2.0);
  rigidbody->setMass(3.0);
  EXPECT_DOUBLE_EQ(rigidbody->getMass(), 3.0);
}
