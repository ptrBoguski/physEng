#include "../include/rigidbody/SphericRigidbody.h"
#include "./renderer/OpenGLRenderer.cpp"
#include "boost/numeric/ublas/vector.hpp"

// This is a playground file for testing and experimentation.

int main() {
  OpenGLRenderer renderer;
  renderer.initialize();

  SphericRigidbody rigidbody(10.0, 1.0); // Initialize at origin
  boost::numeric::ublas::vector<double> force(3);
  force(0) = .00003; // Example force along x-axis
  while (!glfwWindowShouldClose(renderer.window)) {
    renderer.render(rigidbody);
    rigidbody.update(1.0);
    rigidbody.applyForce(force);
    std::cout<<rigidbody.getVelocity()(0)<<std::endl;

    // Poll for and process events
    glfwPollEvents();
  }

  renderer.cleanup();
  return 0;
}
