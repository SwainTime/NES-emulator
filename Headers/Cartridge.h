// -----------------------------------------------------------------------------
// File: Cartridge.h
// Description: Interface of the cartridge. It supplies the game data
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Mapper000.h"

class Cartridge {
    public:
        Cartridge(const std::string &fileName);
        ~Cartridge();

    private:
        bool isImageValid = false;
        std::vector<uint8_t> prgMemory; // Contain the game code and logic(CPU) // $8000-$FFFF
        std::vector<uint8_t> chrMemory; // Contains tile and sprite graphic data(PPU) $0000-$1FFF
        uint8_t mapperId = 0;
        uint8_t prgBanks = 0;
        uint8_t chrBanks = 0;
        
        std::shared_ptr<Mapper> mapper;
    
    //reads and writes are boolean to tell the system whether the cartridge is handling the reads/writes
    public:
        bool imageValid();
        // Communication with the main bus
        bool cpuRead(uint16_t addr, uint8_t &data);
        bool cpuWrite(uint16_t addr, uint8_t data);

        // Communication with the PPU
        bool ppuRead(uint16_t addr, uint8_t &data);
        bool ppuWrite(uint16_t addr, uint8_t data);
};