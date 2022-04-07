// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <memory>
#include <string>
#include "../engine/Aliases.h"
#include "../engine/Random.h"
namespace Forradia {

class cObject {
 public:
  explicit cObject(std::string objectTypeName, bool randomScaling = true,
                   bool randomRotation = true, float _rotation = 0);

  // Object usage

  void UseOn(const std::shared_ptr<cObject> &other);

  // Core

  int objectType = 0;

  // Rendering

  float rotation = 0.0f;
  float scaling = 1.0f;

 private:
  void TransformInto(std::string objectName);

  cRandom random;
};

}  // namespace Forradia
