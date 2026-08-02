#pragma once
#include <cstdint>

class Mapper {
    public:
        Mapper(uint8_t prgBanks, uint8_t chrBanks);
        ~Mapper();
    
    public:
        // virtual lets each mapper provide its own mapping behavior.
        // we put boolean to know if the address was handled or not
        virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
        virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;
        virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
        virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;

    protected:
        uint8_t prgBanks = 0;
        uint8_t chrBanks = 0;
};