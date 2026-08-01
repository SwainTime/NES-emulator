// -----------------------------------------------------------------------------
// File: Bus.h
// Description: Interface of the bus for the 6502 CPU core.
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include <array>
#include <memory>

#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"

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
        // cartridge
        std::shared_ptr<Cartridge> cartridge;

    // Read and write
    public: 
        void cpuWrite(uint16_t addr, uint8_t data);
        uint8_t cpuRead(uint16_t addr, bool readOnly = false);

    // System interface
    public: 
        void insertCartridge(const std::shared_ptr<Cartridge> &cartridge); // connects the cartridge to the internal buses6
        void reset(); // resets the system
	    void clock(); // system tick
    
    private:
        uint32_t sysClockTicks = 0; // system clock ticks
};