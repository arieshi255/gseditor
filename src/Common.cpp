/**
 * Copyright 2022 Skyliegirl33.
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <memory>
#include <algorithm>
#include <iostream>
#include "Common.h"

uint32_t GameCommon::decompress16(uint32_t param1, std::string output_file, uint32_t pixels, uint32_t offset) {
  std::ofstream temp_file(output_file, std::ios::out | std::ios::binary);

  if (!temp_file.is_open() || !rom_file.is_open())
    return false;

  rom_file.seekg(0, rom_file.end);
  const uint32_t length = rom_file.tellg();
  rom_file.seekg(0, rom_file.beg);

  // Call to unknown function (uses param1)
  // int32_t FUN_UNKNOWN(byte array[], param1)

  int32_t pixel_size = 602; // Should be return value of the unknown function (seems to be the size in MB..)

  std::unique_ptr<char[]> buf = std::unique_ptr<char[]>(new char[length]);
  std::unique_ptr<char[]> out_buf = std::unique_ptr<char[]>(new char[length]);

  //pixel_size >>= 1;

  int32_t unk2 = (pixel_size >> 1) + 0x4A;

  // Start of BMP header
  out_buf[0] = 0x42; // B
  out_buf[1] = 0x4D; // M
  // Size
  out_buf[2] = 0x4A;
  out_buf[3] = 0x02;
  out_buf[4] = 0;
  out_buf[5] = 0;
  // Data index
  out_buf[10] = 0x4A;
  out_buf[11] = 0;
  out_buf[12] = 0;
  out_buf[13] = 0;
  // BITMAPCOREHEADER
  out_buf[14] = 0xC;
  out_buf[18] = 32;
  out_buf[19] = 0;
  out_buf[20] = 33;
  out_buf[21] = 0;
  out_buf[22] = 1;
  out_buf[23] = 0;
  out_buf[24] = 4;
  out_buf[25] = 0;
  out_buf[26] = 0xFF;
  out_buf[27] = 0xFF;
  out_buf[28] = 0xFF;

  rom_file.read(buf.get(), length);

  uint32_t index = 0;

  bool isDone = (pixels >> 1) == 0;
  bool isLess = false;

  // Zero out pixel data?
  while (!isDone && !isLess) {
    out_buf[index + 0x4A] = 0;

    ++index;

    isDone = (pixels >> 1) == index;
    isLess = (pixels >> 1) < index;
  }

  uint32_t bmp_offset = 1;
  uint32_t pos = 0;

  if (pixels != 0) {
    index = pixels >> 1;
    uint32_t index2 = index;

    do {
      if (index != 0) {
        auto rom_data = &buf[0] + (pixels - bmp_offset) * pixels;
        auto bmp_data = &out_buf[0] + index2 + 0x4A;
        uint32_t back_pos = index;

        do {
          auto idx1 = rom_data - 0x40000;
          auto idx2 = rom_data - 0x3FFFF;

          rom_data += 2;

          *bmp_data = *idx2 & 0xF | (uint8_t)((*idx1 & 0xF) << 4);
          ++bmp_data;
          
          --back_pos;
        } while (back_pos != 0);
      }

      ++pos;
      index2 += index;
    } while (pos <= pixels);
  }

  temp_file.write(out_buf.get(), (pixels >> 1) + 0x4a + pixel_size);
  temp_file.close();

  return temp_file.fail();
}

void GameCommon::loadFile(std::string filename) {
  if (!rom_file.is_open()) {
    rom_file.open(filename, std::ios::in | std::ios::binary); 
  } else {
    rom_file.close();
    rom_file.open(filename, std::ios::in | std::ios::binary);
  }
}