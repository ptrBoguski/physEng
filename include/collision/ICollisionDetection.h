#pragma once
#include "../rigidbody/Rigidbody.h"

class ICollisionDetection {
public:
  virtual ~ICollisionDetection() = default;

  // Method to check collision between two rigidbodies
  virtual bool checkCollision(const Rigidbody& a, const Rigidbody& b) const = 0;
};
