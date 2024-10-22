#include "../include/collision/SphereCollisionDetection.h"
#include "../include/rigidbody/SphericRigidbody.h"
#include "./renderer/OpenGLRenderer.cpp"
#include "boost/numeric/ublas/vector.hpp"
#include <chrono>
#include <iostream>
/*#include <limits>*/
#include <random>

// This is a playground file for testing and experimentation.

double
calculateTotalKineticEnergy(const std::vector<SphericRigidbody> &rigidbodies,
                            size_t start = 0) {
  double totalKineticEnergy = 0.0;

  for (size_t i = start; i < rigidbodies.size(); ++i) {
    const auto &velocity = rigidbodies[i].getVelocity();
    double speedSquared = boost::numeric::ublas::inner_prod(velocity, velocity);
    double kineticEnergy = 0.5 * rigidbodies[i].getMass() * speedSquared;
    totalKineticEnergy += kineticEnergy;
  }

  return totalKineticEnergy;
}
bool areVectorsEqual(const boost::numeric::ublas::vector<double> &v1,
                     const boost::numeric::ublas::vector<double> &v2,
                     double tolerance = 1e-5) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (std::size_t i = 0; i < v1.size(); ++i) {
    if (std::fabs(v1(i) - v2(i)) > tolerance) {
      return false;
    }
  }
  return true;
}

int main() {
  OpenGLRenderer renderer;
  renderer.initialize();

  const int numRigidbodies = 100; // Number of random rigid bodies
  std::vector<SphericRigidbody> rigidbodies;
  std::vector<boost::numeric::ublas::vector<double>> velocities;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> posDist(-1.0, 1.0);
  std::uniform_real_distribution<> velDist(-1, 1);

  // Add four large balls with infinite mass to cover screen edges
  double largeRadius = 100000.0; // Large enough to cover the edges
  // BUG: The collision resolution logic currently does not support using
  // actual infinite mass values (e.g., std::numeric_limits<double>::infinity()).
  // As a workaround, we use a very large finite value (1e100) to simulate
  // an "infinite" mass. This large value is intended to ensure that these
  // rigid bodies (e.g., screen edge boundaries) are not significantly affected
  // by collisions with other objects, effectively behaving as if they have
  // infinite mass.
  double infMass = 1e100;
  /*double infMass = std::numeric_limits<double>::infinity();*/

  // Top edge
  SphericRigidbody topEdge(largeRadius, infMass);
  boost::numeric::ublas::vector<double> topPosition(3);
  topPosition(0) = 0.5;
  topPosition(1) = 0.99 + largeRadius;
  topPosition(2) = 0.0;
  topEdge.setPosition(topPosition);
  rigidbodies.push_back(topEdge);

  // Bottom edge
  SphericRigidbody bottomEdge(largeRadius, infMass);
  boost::numeric::ublas::vector<double> bottomPosition(3);
  bottomPosition(0) = 0.5;
  bottomPosition(1) = -0.99 - largeRadius;
  bottomPosition(2) = 0.0;
  bottomEdge.setPosition(bottomPosition);
  rigidbodies.push_back(bottomEdge);

  // Left edge
  SphericRigidbody leftEdge(largeRadius, infMass);
  boost::numeric::ublas::vector<double> leftPosition(3);
  leftPosition(0) = -largeRadius - 0.99;
  leftPosition(1) = 0.5;
  leftPosition(2) = 0.0;
  leftEdge.setPosition(leftPosition);
  rigidbodies.push_back(leftEdge);

  // Right edge
  SphericRigidbody rightEdge(largeRadius, infMass);
  boost::numeric::ublas::vector<double> rightPosition(3);
  rightPosition(0) = 0.99 + largeRadius;
  rightPosition(1) = 0.5;
  rightPosition(2) = 0.0;
  rightEdge.setPosition(rightPosition);
  rigidbodies.push_back(rightEdge);

  for (int i = 0; i < numRigidbodies; ++i) {
    SphericRigidbody rigidbody(0.04, 1.0);
    boost::numeric::ublas::vector<double> position(3);
    position(0) = posDist(gen);
    position(1) = posDist(gen);
    position(2) = 0;
    rigidbody.setPosition(position);

    boost::numeric::ublas::vector<double> velocity(3);
    velocity(0) = velDist(gen);
    velocity(1) = velDist(gen);
    velocity(2) = 0;
    rigidbody.applyImpulse(velocity);

    rigidbodies.push_back(rigidbody);
    velocities.push_back(velocity);
  }
  boost::numeric::ublas::vector<bool> collision(rigidbodies.size());
  SphereCollisionDetection collisionDetection;
  auto previousTime = std::chrono::high_resolution_clock::now();

  while (!glfwWindowShouldClose(renderer.window)) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = currentTime - previousTime;
    double deltaTime = elapsed.count();
    previousTime = currentTime;

    renderer.clearScreen();
    for (size_t i = 0; i < rigidbodies.size(); ++i) {
      renderer.set_color(collision[i]);
      renderer.render(rigidbodies[i]);
    }

    collision.clear();
    for (size_t i = 0; i < rigidbodies.size(); ++i) {
      for (size_t j = i + 1; j < rigidbodies.size(); ++j) {
        if (collisionDetection.checkCollision(rigidbodies[i], rigidbodies[j])) {
          rigidbodies[i].resolveCollision(rigidbodies[j]);
          collision[i] = true;
          collision[j] = true;
        }  
      }
    }

    // Calculate and print the total kinetic energy
    double totalKineticEnergy = calculateTotalKineticEnergy(rigidbodies);
    double kinecitEnergyWithoutEdges =
        calculateTotalKineticEnergy(rigidbodies, 4);
    std::cout << "Total Kinetic Energy: " << totalKineticEnergy << std::endl;
    std::cout << "Without Edges: " << kinecitEnergyWithoutEdges << std::endl;

    for (size_t i = 4; i < rigidbodies.size(); ++i) {
      rigidbodies[i].update(deltaTime);
      if(rigidbodies[i].getPosition()(2) != 0 ){
        std::cout<<i<<": "<<rigidbodies[i].getPosition()<<std::endl;
      }
    }
    std::cout << 1 / deltaTime << std::endl;

    // Poll for and process events
    renderer.swapBuffers();
    glfwPollEvents();
  }

  renderer.cleanup();
  return 0;
}
