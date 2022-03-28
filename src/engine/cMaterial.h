// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Aliases.h"
#include "cVector3.h"

namespace Forradia {

class cMaterial {
 public:
  std::string Name;
  cVector3 Ka;
  cVector3 Kd;
  cVector3 Ks;
  float Ns = 0.0f;
  float Ni = 0.0f;
  float D = 0.0f;
  int Illum = 0;
  std::string MapKa;
  std::string MapKd;
  std::string MapKs;
  std::string MapNs;
  std::string MapD;
  std::string MapBump;
};

}  // namespace Forradia
