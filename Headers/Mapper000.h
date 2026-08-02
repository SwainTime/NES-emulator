#pragma once
#include <cstdint>

#include "Mapper.h"

// mappers do not provide data, just translate addresses.

class Mapper000 : public Mapper {
    public:
        Mapper000(uint8_t prgBanks, uint8_t chrBanks);
        ~Mapper000();
    
    public:
        bool cpuMapRead(uint16_t addr, uint32_t &mappedAddr) override;
        bool cpuMapWrite(uint16_t addr, uint32_t &mappedAddr) override;
        bool ppuMapRead(uint16_t addr, uint32_t &mappedAddr) override;
        bool ppuMapWrite(uint16_t addr, uint32_t &mappedAddr) override;
};