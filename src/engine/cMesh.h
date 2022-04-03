// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include <string>
#include <vector>
#include "cMaterial.h"
#include "cVertex.h"

namespace Forradia {

class cMesh {
 public:
  cMesh() {}
  cMesh(std::vector<cVertex> Vertices_, std::vector<unsigned int> Indices_)
      : vertices(Vertices_), indices(Indices_) {}

  std::string meshName;
  std::vector<cVertex> vertices;
  std::vector<unsigned int> indices;
  cMaterial meshMaterial;
};

}  // namespace Forradia
