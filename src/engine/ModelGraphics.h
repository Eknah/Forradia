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

  void DrawModel(std::string modelName, float x, float y, float z,
                        float rotation, float specificScaling,
                 float ppacity = 1.0f) const;

  void DrawModel(int modelNameId, float x, float y, float z,
                        float rotation, float specificScaling,
                 float opacity = 1.0f) const;

 private:
  iEngine &engine;

  float modelScaling = 0.1f;
};

}  // namespace Forradia
