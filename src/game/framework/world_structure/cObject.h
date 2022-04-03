// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <memory>
#include <string>
#include "../engine/Aliases.h"
#include "../engine/cRandom.h"
namespace Forradia {

class cObject {
 public:
  explicit cObject(std::string ObjectTypeName, bool RandomScaling = true,
                   bool RandomRotation = true, float rotation = 0);

  // Object usage

  void UseOn(const std::shared_ptr<cObject> &Other);

  // Core

  int ObjectType = 0;

  // Rendering

  float Rotation = 0.0f;
  float Scaling = 1.0f;

 private:
  void TransformInto(std::string ObjectName);

  cRandom Random;
};

}  // namespace Forradia
