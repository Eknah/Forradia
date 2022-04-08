// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <memory>
#include <string>
#include "../engine/Aliases.h"
#include "../engine/Random.h"
namespace Forradia {

class Object {
 public:
  explicit Object(std::string objectTypeName, bool randomScaling = true,
                   bool randomRotation = true, float _rotation = 0);

  // Object usage

  void UseOn(const std::shared_ptr<Object> &other);

  // Core

  int objectType = 0;

  // Rendering

  float rotation = 0.0f;
  float scaling = 1.0f;

 private:
  void TransformInto(std::string objectName);

  Random random;
};

}  // namespace Forradia
