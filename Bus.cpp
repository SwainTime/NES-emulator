// -----------------------------------------------------------------------------
// File: Bus.cpp
// Description: Implementation of the bus for the 6502 CPU core.
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#include "Bus.h"

Bus::Bus() {
    //Clear RAM contents
    for(auto &i : ram)
        i = 0x00;
    
    //Connect CPU
    cpu.connectBus(this);
}

Bus::~Bus() {

}

void Bus::write(uint16_t addr, uint8_t data) {
    if(addr >= 0x0000 && addr <= 0xFFFF)
        ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly) {
    if(addr >= 0x0000 && addr <= 0xFFFF)
        return ram[addr];
    
    return 0x00;
}