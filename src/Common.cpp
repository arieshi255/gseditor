/**
 * Copyright 2022 Skyliegirl33.
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Common.h"

uint32_t GameCommon::decompress16(uint32_t param1, std::string output_file, double offset) {
    std::ofstream temp_file(output_file, std::ios::in | std::ios::binary);

    if (!temp_file.is_open() || !rom_file.is_open())
        return false;

    // Call to unknown function (uses param1)
    // int32_t FUN_UNKNOWN(byte array[], param1)

    uint8_t unk[0x8];
    int32_t dummy = 0;

    char buf[0xFF];
    char out_buf[0xFF];

    dummy >>= 1;

    int32_t unk2 = dummy + 0x4A;
    char unk3 = (char)dummy;


    // Start of header(?)
    out_buf[0] = 0x42;
    out_buf[1] = 0x4D;
    out_buf[2] = unk3 + 'J';
    out_buf[3] = ((uint32_t)unk2 >> 8);


    rom_file.read(buf, 1);

  return false;
}

void GameCommon::loadFile(std::string filename) {
  if (!rom_file.is_open()) {
    rom_file.open(filename); 
  } else {
    rom_file.close();
    rom_file.open(filename);
  }
}