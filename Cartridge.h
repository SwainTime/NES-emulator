// -----------------------------------------------------------------------------
// File: Cartridge.h
// Description: Interface of the cartridge. It supplies the game data
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
    
    public:
        // Communication with the main bus
        bool cpuRead(uint16_t addr, bool readOnly);
        bool cpuWrite(uint16_t addr, uint8_t data);

        //Communication with the PPU
        bool ppuRead(uint16_t addr, bool readOnly);
        bool ppuWrite(uint16_t addr, uint8_t data);
};