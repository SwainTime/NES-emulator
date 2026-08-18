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
    // give priority to the cartridge 
    if(cartridge -> cpuWrite(addr, data)) {
        
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF) // 8KB range
        cpuRam[addr & 0x07FF] = data;
    
    else if(addr >= 0x2000 && addr <= 0x3FFF) //in this range it talks with the ppu
        ppu.cpuWrite(addr & 0x0007, data); // the CPU range of talking with PPU is only 8 bytes (8 PPU registers)
}

uint8_t Bus::cpuRead(uint16_t addr, bool readOnly) {
    uint8_t data = 0x00;

    // give prio to cartridge
    if(cartridge -> cpuRead(addr, data)) {
        
    }
    else if(addr >= 0x0000 && addr <= 0x1FFF) // 8KB range that is mirrored every 2 KB
        data = cpuRam[addr & 0x07FF]; // basically does modulo 2KB
    
    else if(addr >= 0x2000 && addr <= 0x3FFF) //in this range it talks with the ppu
        data = ppu.cpuRead(addr & 0x0007, readOnly); // the CPU range of talking with PPU is only 8 bytes (8 PPU registers)
    
    return data;
}

void Bus::reset() {
    cpu.reset();
    sysClockTicks = 0;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge) {
    this->cartridge = cartridge;
    ppu.connectCartridge(cartridge);
}

void Bus::clock() {
    ppu.clock();
    if (sysClockTicks % 3 == 0) {
        cpu.clock();
    }

    if (ppu.nmi) {
        ppu.nmi = false;
        cpu.nmi();
    }

    sysClockTicks++;
}