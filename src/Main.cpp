// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//      ______  _____  _____   _____   _____  ___    __   _____
//     / ____/ / _  / /    /  /    /  /    / / _ \  / /  /    /
//    / /_    / // / /  ^_/  /  ^_/  /  ^ / / // / / /  /  ^ /
//   / __/   / // / / . \   / . \   / // / / // / / /  / // /
//  /_/     /____/ /_/ \_\ /_/ \_\ /_//_/ /____/ /_/  /_//_/
//

#include "implementation/cGameInstance.h"

// Creates game instance and runs it

// Linux
// int main()

// Windows
int wmain() {
  Forradia::cGameInstance().StartGame();

  return 0;
}
