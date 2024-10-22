#include "../../include/renderer/IRenderer.h"
#include "../../include/rigidbody/Rigidbody.h"
#include "../../include/rigidbody/SphericRigidbody.h"
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

    window = glfwCreateWindow(800, 800, "PhysEng Renderer", NULL, NULL);
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

    glViewport(0, 0, 800, 800);
  }


  void render(const Rigidbody &rigidbody) override {}
  // TODO: fix rendering scale
  void render(const SphericRigidbody &rigidbody) override {

    // Get the position of the Rigidbody
    auto position = rigidbody.getPosition();

    // Define circle parameters
    float radius = rigidbody.getRadius();   
    int numSegments = 100; // Number of segments for the circle
    if(color)
      glColor3f(1.0f, 0.0f, 0.0f);
    else
      glColor3f(1.0f, 1.0f, 1.0f);  // White color for default rendering

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

  }
  void set_color(bool red){
    this->color = red;
  }

  void clearScreen() override {
      glClear(GL_COLOR_BUFFER_BIT);
  }

  void cleanup() {
    glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();
  }

  // TODO: implement those functions 
  void swapBuffers() override {
    glfwSwapBuffers(window);
  };
  void pollEvents() override {};
  bool shouldClose() override { return false; };
protected: 
  bool color = false;
};
