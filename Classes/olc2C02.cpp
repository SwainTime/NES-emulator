#include "olc2C02.h"
#include <memory>
#include "Cartridge.h"

// Helper function
void casesCpu(uint16_t addr, uint8_t& data) {

    // Control - Controls PPU settings(nametables, sprite height, etc)
    // Mask - Controls rendering options(background rendering, sprite rendering...)
    // Status - Reads PPU state
    // OAM address - sets the address pointer into OAM - the sprite memory where sprite informaton is stored
    // OAM data - Reads/writes sprite data at the current OAM address. Each sprite has position, tile index, attributes
    // Scroll - Sets the background scroll position(X and Y)
    // PPU address - Sets the address for reading/writing PPU RAM
    // PPU data - Reads/writes data from PPU RAM at the address set by PPU address. 
    switch (addr)
	{
        case 0x0000: // Control
            break;
        case 0x0001: // Mask
            break;
        case 0x0002: // Status
            break;
        case 0x0003: // OAM Address
            break;
        case 0x0004: // OAM Data
            break;
        case 0x0005: // Scroll
            break;
        case 0x0006: // PPU Address
            break;
        case 0x0007: // PPU Data
            break;
	}
}

uint8_t olc2C02::cpuRead(uint16_t addr, bool readOnly) {
    uint8_t data = 0x00;
    casesCpu(addr, data);

    return data;
}

uint8_t olc2C02::ppuRead(uint16_t addr, bool readOnly) {
    //placeholder
    uint8_t data = 0x00;
    addr &= 0x3FFF;
 
    // prio co cartridge
    if(cartridge -> ppuRead(addr, data)) {
        
    }

    return 0;
}
void olc2C02::ppuWrite(uint16_t addr, uint8_t data) {
    //placeholder
    addr &= 0x3FFF;

    // prio to cartridge
    if(cartridge -> ppuWrite(addr, data)) {
        
    }
}

void olc2C02::connectCartridge(const std::shared_ptr<Cartridge> &cartridge) {
    this->cartridge = cartridge;
    
}