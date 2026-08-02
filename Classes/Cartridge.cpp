#include "Cartridge.h"

Cartridge::Cartridge(const std::string &fileName) {
    // iNES format header
    struct sHeader {
        char name[4];
        uint8_t prgRomChunks;
        uint8_t chrRomChunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prgRamSize;
        uint8_t tvSystem1;
        uint8_t tvSystem2;
        char unused[5];
    } header; // from the wiki

    isImageValid = false;
    std::ifstream file;
    file.open(fileName, std::ifstream::binary);
    if(file.is_open()) {
        // read file header
        file.read((char*) &header, sizeof(header)); // it reads from the file and puts it directly in the header

        if(header.mapper1 & 0x04) // next 512 byte are used for training info
            file.ignore(512); // we treat it as junk
        
        mapperId = (header.mapper2 & 0xF0) | (header.mapper1 >> 4); // takes the upper 4 bit of mapper 1 and mapper 2 and merges them to create the mapper id

        uint8_t fileType = 1;
        if(fileType == 0) {

        }
        else if(fileType == 1) {
            prgBanks = header.prgRomChunks;
            prgMemory.resize(prgBanks * 16384); // resize it in prgBanks of 16384 bytes(16 KB)
            file.read((char*)prgMemory.data(), prgMemory.size()); // writes the data of the PRG memory
        }
        else if(fileType == 2) {
             
        }


        // Load mapper based on id
        if(mapperId == 0) {
            mapper = std::make_shared<Mapper000>(prgBanks, chrBanks);
        }
        
        isImageValid = true;
        file.close(); 
    } 

}

Cartridge::~Cartridge() {

}

bool Cartridge::imageValid()
{
	return isImageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
    uint32_t mappedAddr = 0;
    if(mapper -> cpuMapRead(addr, mappedAddr)) {
        data = prgMemory[mappedAddr];
        return true;
    }
    return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mappedAddr = 0;
    if(mapper -> cpuMapRead(addr, mappedAddr)) {
        prgMemory[mappedAddr] = data;
        return true;
    }
    return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t &data)
{
    uint32_t mappedAddr = 0;
    if(mapper -> ppuMapRead(addr, mappedAddr)) {
        data = chrMemory[mappedAddr];
        return true;
    }

    return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mappedAddr = 0;
    if(mapper -> ppuMapRead(addr, mappedAddr)) {
        chrMemory[mappedAddr] = data;
        return true;
    }
    return false;
}
