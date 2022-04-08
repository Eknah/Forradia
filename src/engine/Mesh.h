// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include <string>
#include <vector>
#include "Material.h"
#include "Vertex.h"

namespace Forradia {

class Mesh {
 public:
  Mesh() {}
  Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
      : vertices(_vertices), indices(_indices) {}

  std::string meshName;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  Material meshMaterial;
};

}  // namespace Forradia
