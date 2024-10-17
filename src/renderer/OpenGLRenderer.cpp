#include "../../include/renderer/IRenderer.h"
#include "../../include/rigidbody/Rigidbody.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

class OpenGLRenderer : public IRenderer {
public:
  GLFWwindow *window;

  void initialize() override {
    if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      return;
    }

    window = glfwCreateWindow(800, 600, "PhysEng Renderer", NULL, NULL);
    if (!window) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialize GLEW" << std::endl;
      return;
    }

    glViewport(0, 0, 800, 600);
  }

  void render(const Rigidbody &rigidbody) override {
    glClear(GL_COLOR_BUFFER_BIT);

    // Get the position of the Rigidbody
    auto position = rigidbody.getPosition();

    // Define circle parameters
    float radius = 0.05f;  // Adjust the radius as needed
    int numSegments = 100; // Number of segments for the circle

    // Render a circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(static_cast<float>(position(0)),
               static_cast<float>(position(1))); // Center of the circle
    for (int i = 0; i <= numSegments; ++i) {
      float angle = 2.0f * M_PI * i / numSegments;
      float x = radius * cos(angle);
      float y = radius * sin(angle);
      glVertex2f(static_cast<float>(position(0)) + x,
                 static_cast<float>(position(1)) + y);
    }
    glEnd();

    glfwSwapBuffers(window);
  }

  void clearScreen() override {
      glClear(GL_COLOR_BUFFER_BIT);
  }

  void cleanup() {
    glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();
  }

  // TODO 
  void swapBuffers() override {};
  void pollEvents() override {};
  bool shouldClose() override { return false; };
};
