// -----------------------------------------------------------------------------
// File: Bus.h
// Description: Interface of the bus for the 6502 CPU core.
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>
#include "olc2C02.h"

class Bus {
    public:
        Bus();
        ~Bus();

    // Devices on the bus
    public:
        olc6502 cpu;
        // PPU
        olc2C02 ppu; 
        // fake RAM
        std::array <uint8_t, 2048> cpuRam;

    // Read and write
    public: 
        void cpuWrite(uint16_t addr, uint8_t data);
        uint8_t cpuRead(uint16_t addr, bool readOnly = false);
};