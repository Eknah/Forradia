// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "cMaterial.h"
#include "cVertex.h"

namespace Forradia {

class cMesh {
 public:
  cMesh() {}
  cMesh(std::vector<cVertex> &vertices, std::vector<unsigned int> &indices)
      : Vertices(vertices), Indices(indices) {}

  std::string MeshName;
  std::vector<cVertex> Vertices;
  std::vector<unsigned int> Indices;
  cMaterial MeshMaterial;
};

}  // namespace Forradia
