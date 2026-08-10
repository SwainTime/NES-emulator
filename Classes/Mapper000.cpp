#include "Mapper000.h"

Mapper000::Mapper000(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks) {
    
}

Mapper000::~Mapper000() {

}

bool Mapper000::cpuMapRead(uint16_t addr, uint32_t &mappedAddr) {
    if(addr >= 0x8000 && addr <= 0xFFFF) {
        // if the nr of prg banks is more than one, then we know the cpu is 32KB
        if(prgBanks > 1)
            mappedAddr = addr & 0x7FFF;
        else
            mappedAddr = addr & 0x3FFF; // one 16KB of PRG ROM< so the single 16KB banks is mirrored twice
        return true;
    }

    return false;
}

bool Mapper000::cpuMapWrite(uint16_t addr, uint32_t &mappedAddr) {
    if(addr >= 0x8000 && addr <= 0xFFFF) {
        // if the nr of prg banks is more than one, then we know the cpu is 32KB
        if(prgBanks > 1)
            mappedAddr = addr & 0x7FFF;
        else
            mappedAddr = addr & 0x3FFF; // one 16KB of PRG ROM< so the single 16KB banks is mirrored twice
        return true;
    }

    return false;
}

bool Mapper000::ppuMapRead(uint16_t addr, uint32_t &mappedAddr) {
    if(addr >= 0x0000 && addr <= 0x1FFF) {
        //here there is no bank switching
        mappedAddr = addr;
        return true;
    }

    return false;
}

bool Mapper000::ppuMapWrite(uint16_t addr, uint32_t &mappedAddr) {
    // this does nothing because the cartridge is not interested in this

    return false;
}
