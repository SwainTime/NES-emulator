#include "olc2C02.h"
#include <memory>
#include "Cartridge.h"

olc2C02::olc2C02()
{
	// all colors the NES has
	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);

	sprScreen = new olc::Sprite(256, 240);
	sprNameTable[0] = new olc::Sprite(256, 240);
	sprNameTable[1] = new olc::Sprite(256, 240);
	sprPatternTable[0] = new olc::Sprite(128, 128);
	sprPatternTable[1] = new olc::Sprite(128, 128);
}


olc2C02::~olc2C02()
{
	delete sprScreen;
	delete sprNameTable[0];
	delete sprNameTable[1];
	delete sprPatternTable[0];
	delete sprPatternTable[1];
}

olc::Sprite& olc2C02::getScreen()
{
	return *sprScreen;
}

olc::Sprite & olc2C02::getNameTable(uint8_t i)
{
	return *sprNameTable[i];
}

olc::Sprite & olc2C02::getPatternTable(uint8_t i, uint8_t palette)
{
	// these two fors iterate through the tiles
	for (uint16_t tileX = 0; tileX < 16; tileX++) {
		for (uint16_t tileY = 0; tileY < 16; tileY++) {
			uint16_t offset = tileX * 256 + tileY * 16; // we multiply with 256 because each row in the pattern table is 256 bytes wide and then every tile is 16 bytes

			for (uint16_t x = 0; x < 8; x++) {
				uint8_t  tileLsb = ppuRead(i * 0x1000 + offset + x, false);
				uint8_t  tileMsb = ppuRead(i * 0x1000 + offset + x + 8, false);

				for (uint16_t y = 0; y < 8; y++) {
					uint8_t pixel = ((tileMsb & 1) << 1) | (tileLsb & 1); // we combine the least significant bits of each variable to get a value between 0 and 3
					tileLsb >>= 1;
					tileMsb >>= 1;

					sprPatternTable[i] -> SetPixel(
						tileX * 8 + (7 - y), // the first extracted pixel is the rightmost one
						tileY  * 8 + x,
						getColorFromPaletteRam(palette, pixel)
					);
				}
			}
		}
	}
	return *sprPatternTable[i];
}

olc::Pixel& olc2C02::getColorFromPaletteRam(uint8_t palette, uint8_t pixel) {
	return palScreen[ppuRead(0x3F00 + (palette * 4) + pixel, false)];
}
uint8_t olc2C02::cpuRead(uint16_t addr, bool readOnly) {
    uint8_t data = 0x00;

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
			data = (status.reg & 0xE0) | (ppuDataBuffer & 0x1F); // the top three bits are the status register, the bottom five bits are the last value on the data bus
			status.verticalBlank = 0;
			addressLatch = 0;
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
			data = ppuDataBuffer;
			ppuDataBuffer = ppuRead(ppuAddress, readOnly);

			if (ppuAddress >= 0x3F00) data = ppuDataBuffer;
			ppuAddress += (control.incrementMode ? 32 : 1);
			break;
	}

    return data;
}

void olc2C02::cpuWrite(uint16_t addr, uint8_t data) {
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
    		control.reg = data;
            break;
        case 0x0001: // Mask
    		mask.reg = data;
            break;
        case 0x0002: // Status
    		// can't write to the status
            break;
        case 0x0003: // OAM Address
            break;
        case 0x0004: // OAM Data
            break;
        case 0x0005: // Scroll
            break;
        case 0x0006: // PPU Address
    		// write to either the low bytes or high bytes based on addressLatch.
    		if (addressLatch == 0) {
    			ppuAddress = (ppuAddress & 0x00FF) | (data << 8);
    			addressLatch = 1;
    		} else {
    			ppuAddress = (ppuAddress & 0xFF00) | data;
    			addressLatch = 0;
    		}
            break;
        case 0x0007: // PPU Data
    		ppuWrite(ppuAddress, data);
    		ppuAddress += (control.incrementMode ? 32 : 1);
            break;
	}
}

uint8_t olc2C02::ppuRead(uint16_t addr, bool readOnly) {
    uint8_t data = 0x00;
    addr &= 0x3FFF;
 
    // first if: prio to cartridge
	// 0x0000 -> 0x1FFF - pattern table
	// 0x2000 -> 0x3EFF - name table
	// 0x3F00 -> 0x3FFF - palette table
    if(cartridge -> ppuRead(addr, data)) {

    } else if (addr >= 0x0000 && addr <= 0x1FFF) {
    	// if bit 12 of the address is 0, then it takes the leftside part(0x0000 -> 0x0FFFF), if it's 1, then it takes the rightside part(0x1000 -> 0x1FFF)
    	// addr & 0x0FFF keeps only the lower bits
		data = patternTable[(addr >> 12) & 0x0001][addr & 0x0FFF];

    } else if (addr >= 0x2000 && addr <= 0x3EFF) {

    } else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F; // mask the bottom five bits
    	// hard code the mirroring
    	if (addr == 0x0010) addr = 0x0000;
    	if (addr == 0x0014) addr = 0x0004;
    	if (addr == 0x0018) addr = 0x0008;
    	if (addr == 0x001C) addr = 0x000C;
		data = paletteTable[addr];
    }
    return data;
}
void olc2C02::ppuWrite(uint16_t addr, uint8_t data) {
    //placeholder
    addr &= 0x3FFF;

    // prio to cartridge
	// first if: prio to cartridge
	// 0x0000 -> 0x1FFF - pattern table
	// 0x2000 -> 0x3EFF - name table
	// 0x3F00 -> 0x3FFF - palette table
	if(cartridge -> ppuWrite(addr, data)) {

	} else if (addr >= 0x0000 && addr <= 0x1FFF) {
		// usually a ROM, but in case it is a RAM
		data = patternTable[(addr >> 12) & 0x0001][addr & 0x0FFF];
	} else if (addr >= 0x2000 && addr <= 0x3EFF) {

	} else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F; // mask the bottom five bits
		// hard code the mirroring
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		paletteTable[addr] = data;
	}
}

void olc2C02::connectCartridge(const std::shared_ptr<Cartridge> &cartridge) {
    this->cartridge = cartridge;
}

void olc2C02::clock()
{
	if (scanline == -1 && cycle == 1) {
		status.verticalBlank = 0;
	}
	if (scanline == 241 && cycle == 1) {
		status.verticalBlank = 1;
		if (control.enableNmi) {
			nmi = true;

		}
	}
	// Fake some noise for placeholder
	uint8_t randVal = rand();
	if(randVal % 2 == 1)
		sprScreen->SetPixel(cycle - 1, scanline, palScreen[0x3F]);
	else
		sprScreen->SetPixel(cycle - 1, scanline, palScreen[0x30]);

	// Advance renderer - it never stops, it's relentless
	// it goes throw 341 x 261 clock cycles to produce one complete video frame
	cycle++;
	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}