// -----------------------------------------------------------------------------
// File: Bus.cpp
// Description: Implementation of the bus for the 6502 CPU core.
// Based on the olcNES architecture by David Barr (javidx9 / OneLoneCoder).
// -----------------------------------------------------------------------------

#include "Bus.h"

Bus::Bus() {
    //Clear RAM contents
    for(auto &i : cpuRam)
        i = 0x00;
    
    //Connect CPU
    cpu.connectBus(this);
}

Bus::~Bus() {

}

void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if(addr >= 0x0000 && addr <= 0x1FFF) // 8KB range
        cpuRam[addr & 0x07FF] = data;
    
    if(addr >= 0x2000 && addr <= 0x3FFF) //in this range it talks with the ppu
        ppu.cpuWrite(addr & 0x0007, data); // the CPU range of talking with PPU is only 8 bytes (8 PPU registers)
}

uint8_t Bus::cpuRead(uint16_t addr, bool readOnly) {
    uint8_t data = 0x00;

    if(addr >= 0x0000 && addr <= 0x1FFF) // 8KB range that is mirrored every 2 KB
        data = cpuRam[addr & 0x07FF]; // basically does modulo 2KB
    
    if(addr >= 0x2000 && addr <= 0x3FFF) //in this range it talks with the ppu
        ppu.cpuRead(addr & 0x0007, readOnly); // the CPU range of talking with PPU is only 8 bytes (8 PPU registers)
    
    return 0x00;
}