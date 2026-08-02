// -----------------------------------------------------------------------------
// File: olc2C02.h
// Description: Interface of the PPU
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include<cstdint>
#include <memory>


#include "olcPixelGameEngine.h"
#include "Cartridge.h"

class olc2C02 {
    public:
        olc2C02();
        ~olc2C02();

        // these two communicate with the main bus
        uint8_t cpuRead(uint16_t addr, bool readOnly); // CPU reads from the PPU
        void cpuWrite(uint16_t addr, uint8_t data); // CPU writes to the PPU

        // these two communicate with the PPU bus
        uint8_t ppuRead(uint16_t addr, bool readOnly); 
        void ppuWrite(uint16_t addr, uint8_t data);

    private:
        olc::Pixel  palScreen[0x40];
        olc::Sprite* sprScreen;
        olc::Sprite* sprNameTable[2];
        olc::Sprite* sprPatternTable[2];
    
    public:
        // Debugging Utilities
        olc::Sprite& getScreen();
        olc::Sprite& getNameTable(uint8_t i);
        olc::Sprite& getPatternTable(uint8_t i);
        bool frame_complete = false;
    
    private:
        std::shared_ptr<Cartridge> cartridge;
        uint8_t nameTable[2][1024]; // 2KB split into two
        uint8_t paletteTable[32]; 
        uint8_t patternTable[2][4096];

    private:
	    int16_t scanline = 0; // row
	    int16_t cycle = 0; // column
    
    public:
        void connectCartridge(const std::shared_ptr<Cartridge> &cartridge);
        void clock();
};