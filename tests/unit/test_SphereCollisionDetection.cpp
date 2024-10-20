#include <gtest/gtest.h>
#include "../../include/collision/SphereCollisionDetection.h"
#include "../../include/rigidbody/SphericRigidbody.h"
#include <boost/numeric/ublas/vector.hpp>

class SphereCollisionDetectionTest : public ::testing::Test {
protected:
    SphereCollisionDetection collisionDetection;
};


TEST_F(SphereCollisionDetectionTest, OneObjectZeroPositionNonZeroRadius) {
    SphericRigidbody a(1.0, 1.0); // Radius 1.0, Mass 1.0
    SphericRigidbody b(0.0, 1.0); // Radius 0.0, Mass 1.0

    // One object has zero radius
    EXPECT_TRUE(collisionDetection.checkCollision(a, b));
}

TEST_F(SphereCollisionDetectionTest, BothObjectsNonZeroPositionNoOverlap) {
    SphericRigidbody a(1.0, 1.0); // Radius 1.0, Mass 1.0
    SphericRigidbody b(1.0, 1.0); // Radius 1.0, Mass 1.0

    // Set positions of a and b to non-overlapping
    boost::numeric::ublas::vector<double> positionA(3);
    positionA(0) = 3.0;
    positionA(1) = 0.0;
    positionA(2) = 0.0;
    a.setPosition(positionA);

    boost::numeric::ublas::vector<double> positionB(3);
    positionB(0) = -3.0;
    positionB(1) = 0.0;
    positionB(2) = 0.0;
    b.setPosition(positionB);

    EXPECT_FALSE(collisionDetection.checkCollision(a, b));
}

TEST_F(SphereCollisionDetectionTest, Collide_ZeroPosition_NonZeroRadii) {
    SphericRigidbody a(1.0, 1.0); // Radius 1.0, Mass 1.0
    SphericRigidbody b(1.0, 1.0); // Radius 1.0, Mass 1.0
    EXPECT_TRUE(collisionDetection.checkCollision(a, b));
}

TEST_F(SphereCollisionDetectionTest, Collide_ZeroPosition_ZeroRadii) {
    SphericRigidbody a(0.0, 1.0); // Radius 0.0, Mass 1.0
    SphericRigidbody b(0.0, 1.0); // Radius 0.0, Mass 1.0
    EXPECT_TRUE(collisionDetection.checkCollision(a, b));
}

TEST_F(SphereCollisionDetectionTest, NoCollide_NonZeroPosition_NoOverlap) {
    SphericRigidbody a(1.0, 1.0); // Radius 1.0, Mass 1.0
    SphericRigidbody b(1.0, 1.0); // Radius 1.0, Mass 1.0

    boost::numeric::ublas::vector<double> positionA(3);
    positionA(0) = 3.0;
    positionA(1) = 0.0;
    positionA(2) = 0.0;
    a.setPosition(positionA);

    boost::numeric::ublas::vector<double> positionB(3);
    positionB(0) = -3.0;
    positionB(1) = 0.0;
    positionB(2) = 0.0;
    b.setPosition(positionB);

    EXPECT_FALSE(collisionDetection.checkCollision(a, b));
}

TEST_F(SphereCollisionDetectionTest, Collide_AtEdgeOfCollision) {
    SphericRigidbody a(1.0, 1.0); // Radius 1.0, Mass 1.0
    SphericRigidbody b(1.0, 1.0); // Radius 1.0, Mass 1.0

    boost::numeric::ublas::vector<double> positionA(3);
    positionA(0) = 2.0;
    positionA(1) = 0.0;
    positionA(2) = 0.0;
    a.setPosition(positionA);

    boost::numeric::ublas::vector<double> positionB(3);
    positionB(0) = 0.0;
    positionB(1) = 0.0;
    positionB(2) = 0.0;
    b.setPosition(positionB);

    EXPECT_TRUE(collisionDetection.checkCollision(a, b));
}
