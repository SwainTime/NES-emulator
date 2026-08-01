// -----------------------------------------------------------------------------
// File: Cartridge.h
// Description: Interface of the cartridge. It supplies the game data
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>

class Cartridge {
    public:
        Cartridge(const std::string &fileName);
        ~Cartridge();

    private:
        std::vector<uint8_t> PRGMemory; // Contain the game code and logic(CPU) // $8000-$FFFF
        std::vector<uint8_t> CHRMemory; // Contains tile and sprite graphic data(PPU) $0000-$1FFF
        uint8_t mapperID = 0;
        uint8_t PRGBanks = 0;
        uint8_t CHRBanks = 0;
    
    public:
        // Communication with the main bus
        bool cpuRead(uint16_t addr, bool readOnly);
        bool cpuWrite(uint16_t addr, uint8_t data);

        // Communication with the PPU
        bool ppuRead(uint16_t addr, bool readOnly);
        bool ppuWrite(uint16_t addr, uint8_t data);
};