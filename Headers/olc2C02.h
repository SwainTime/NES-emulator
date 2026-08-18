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
        olc::Sprite& getPatternTable(uint8_t i, uint8_t palette);
        olc::Pixel& getColorFromPaletteRam(uint8_t palette, uint8_t pixel);
        bool frame_complete = false;
    
    private:
        std::shared_ptr<Cartridge> cartridge;
        uint8_t nameTable[2][1024]; // 2KB split into two
        uint8_t paletteTable[32]; 
        uint8_t patternTable[2][4096];

    private:
	    int16_t scanline = 0; // horizontal line
	    int16_t cycle = 0; // position within that line

        union {
            struct {
                uint8_t unused : 5;
                uint8_t spriteOverflow : 1; // too many sprites on a scanline
                uint8_t spriteZeroHit : 1; // sprite 0 overlaps a background pixel. Sprite 0 is used for timing effects, like knowing when the scanline has reached a certain point
                uint8_t verticalBlank : 1; // PPU is in vblank period. Vblank is when the PPU has finished drawing the current frame and is not drawing anything
            };
            uint8_t reg;
        } status;

        union {
            struct {
                uint8_t grayscale : 1;
                uint8_t renderBackGroundLeft : 1;
                uint8_t renderSpritesLeft : 1;
                uint8_t renderBackground : 1;
                uint8_t renderSprites : 1;
                uint8_t enhanceRed : 1;
                uint8_t enhanceGreen : 1;
                uint8_t enhanceBlue : 1;
            };

            uint8_t reg;
        } mask;

        union PPUCTRL {
            struct {
                uint8_t nametableX : 1; // selects the horizontal nametable bit
                uint8_t nametableY : 1; // selects the vertical nametable bit
                uint8_t incrementMode : 1; // chooses whether PPU address increments by 1 or 32
                uint8_t patternSprite : 1; // selects which pattern table sprites use
                uint8_t patternBackground : 1; // selects which pattern table the background uses
                uint8_t spriteSize : 1; // chooses sprite size: 8x8 or 8x16
                uint8_t slaveMode : 1; // unused on NES
                uint8_t enableNmi : 1; // enables NMI generation at the start of veritcal blank, so basically the ppu can interrupt the CPU to do stuff.
            };
            uint8_t reg;
        } control;

        uint8_t addressLatch = 0x00; // read from low byte or high byte
        uint8_t ppuDataBuffer = 0x00; // when we read from the PPU, it is delayed by one cycle, so we need a buffer
        uint16_t ppuAddress = 0x0000; // compiled address;

    public:
        void connectCartridge(const std::shared_ptr<Cartridge> &cartridge);
        void clock();
        bool nmi = false;
};