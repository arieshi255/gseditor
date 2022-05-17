/**
 * Copyright 2022 Skyliegirl33.
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <iostream>
#include "GoldenSun.h"

int main(int argc, char* argv[]) {
    GoldenSun gs;

    gs.loadFile("/home/lucy/Games/Golden Sun (USA, Europe).gba");

    // Pixels: 4367B8(?) / 138635160

    std::cout << gs.decompress16(0, "/home/lucy/Games/test.bmp", 0x20, 0x8436798) << std::endl;
}