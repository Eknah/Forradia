// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <vector>
#include <string>
#include "../engine/Aliases.h"

namespace Forradia {

class cAlgorithmsStrings {
 public:
  void Split(const std::string &in, std::vector<std::string> *out,
                    std::string token);

  std::string Tail(const std::string &in);

  std::string FirstToken(const std::string &in);
};
}  // namespace Forradia
