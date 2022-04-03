// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include <string>
#include "Aliases.h"
#include "cVector3.h"

namespace Forradia {

class cMaterial {
 public:
  std::string name;
  cVector3 ka;
  cVector3 kd;
  cVector3 ks;
  float ns = 0.0f;
  float ni = 0.0f;
  float d = 0.0f;
  int illum = 0;
  std::string mapKa;
  std::string mapKd;
  std::string mapKs;
  std::string mapNs;
  std::string mapD;
  std::string mapBump;
};

}  // namespace Forradia
