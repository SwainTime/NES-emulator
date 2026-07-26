// -----------------------------------------------------------------------------
// File: Bus.h
// Description: Interface of the bus for the 6502 CPU core.
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>

class Bus {
    public:
        Bus();
        ~Bus();

    //Devices on the bus
    public:
        olc6502 cpu;
        //fake RAM
        std::array <uint8_t, 64 * 1024> ram;

    //Read and write
    public: 
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool bReadOnly = false);
};