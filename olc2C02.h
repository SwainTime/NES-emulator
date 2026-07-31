// -----------------------------------------------------------------------------
// File: olc2C02.h
// Description: Interface of the PPU
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include<cstdint>

class olc2C02 {
    public:
        olc2C02();
        ~olc2C02();

        // these two communicate with the main bus
        uint8_t cpuRead(uint16_t addr, bool readOnly); // CPU reads from the PPU
        void cpuWrite(uint16_t addr, uint8_t data); // CPU writes to the PPU

        // these two communicate with the PPU bus
        uint8_t ppuRead(uint16_t addr, bool readOnly()); 
        void ppuWrite(uint16_t addr, uint8_t data);
};