/**
 * Copyright 2022 Skyliegirl33.
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <string>
#include <fstream>

bool loadFile(std::string filename);

class GameCommon {
  private:
    std::ifstream rom_file;

  public:
    // Load ROM
    void loadFile(std::string filename);

    // Writes to a temporary .BMP file
    uint32_t decompress16(uint32_t param1, std::string output_file, uint32_t pixels, uint32_t offset);
};