// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"

namespace Forradia {

class cModelGraphics {
 public:
  explicit cModelGraphics(iEngine &engine) : engine(engine) {}

  // ---- Drawing operations ----

  void DrawModel(std::string ModelName, float X, float Y, float Z,
                        float Rotation, float SpecificScaling) const;

  void DrawModel(int ModelNameId, float X, float Y, float Z,
                        float Rotation, float SpecificScaling) const;

 private:
  iEngine &engine;

  float modelScaling = 0.1f;
};

}  // namespace Forradia
