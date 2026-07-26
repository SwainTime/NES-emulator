#include "olc6502.h"
#include "Bus.h"    

olc6502::olc6502() {
    typedef olc6502 a;
    lookup = {
        { "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
    };
}

olc6502::~olc6502() {
    
}

uint8_t olc6502::read(uint16_t a) {
    return bus->read(a, false); 
}

void olc6502::write(uint16_t a, uint8_t d) {
    bus->write(a, d); 
}

void olc6502::clock() {
    if(cycles == 0) {
        opCode = read(pc);
        pc++;

        //starting nr of cycles of the operation
        cycles = lookup[opCode].cycles;

        auto addrMode = lookup[opCode].addrMode; 
        uint8_t nrOfCyclesAddr = (this->*addrMode)(); 
        
        auto operate = lookup[opCode].operate;
        uint8_t nrOfCyclesOperate = (this->*operate)();

        cycles += (nrOfCyclesAddr & nrOfCyclesOperate);
    }

    cycles--;
}

void olc6502::reset() {
    accum = 0;
    x = 0;
    y = 0;
    stp = 0xFD;
    status = U;
    fetched = 0x00;

    addrAbs = 0xFFFC;
    uint16_t lowBytes = read(addrAbs);
    uint16_t highBytes = read(addrAbs + 1);
    pc = (highBytes << 8) | lowBytes;
    cycles = 8;
}

void olc6502::irq() {
    if(getFlag(I) == 0) {
        //It first writes the pc to the stack
        write(0x0100 + stp, (pc >> 8) & 0x00FF);
        stp--;
        write(0x0100 + stp, pc & 0x00FF);
        stp--;

        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        write(0x0100 + stp, status);
        stp--;

        addrAbs = 0xFFFE;
        uint16_t lowBytes = read(addrAbs);
        uint16_t highBytes = read(addrAbs + 1);
        pc = (highBytes << 8) | lowBytes;
        
        cycles = 7;
    }
}

void olc6502::nmi() {
    if(getFlag(I) == 0) {
        //It first writes the pc to the stack
        write(0x0100 + stp, (pc >> 8) & 0x00FF);
        stp--;
        write(0x0100 + stp, pc & 0x00FF);
        stp--;

        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        write(0x0100 + stp, status);
        stp--;

        addrAbs = 0xFFFA;
        uint16_t lowBytes = read(addrAbs);
        uint16_t highBytes = read(addrAbs + 1);
        pc = (highBytes << 8) | lowBytes;
        
        cycles = 8;
    }
}

uint8_t olc6502::getFlag(FLAG6502 f)
{
	if(status & f)
        return 1;
    return 0;
}

void olc6502::setFlag(FLAG6502 f, bool v) {
    if(v == 1)
        status |= f;
    else
        status &= ~f;
}

//Implementation of addressing modes

uint8_t olc6502::IMP() {
    fetched = accum;
    return 0;
}

uint8_t olc6502::IMM() {
    addrAbs = pc++;
    return 0;
}

uint8_t olc6502::ZP0() {
    addrAbs = read(pc++);
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t olc6502::ZPX() {
    addrAbs = read(pc++) + x;
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t olc6502::ZPY() {
    addrAbs = read(pc++) + y;
    addrAbs &= 0x00FF;
    return 0;
}

uint8_t olc6502::ABS() {
    uint8_t lowBytes = read(pc++);
    uint8_t highBytes = read(pc++);
    addrAbs = (highBytes << 8) + lowBytes;
    return 0;
}

uint8_t olc6502::ABX() {
    uint16_t lowBytes = read(pc++);
    uint16_t highBytes = read(pc++);
    addrAbs = (highBytes << 8) + lowBytes;
    addrAbs += x;


    if((addrAbs & 0x00FF) != lowBytes)
        return 1;
    return 0;
}

uint8_t olc6502::ABY() {
    uint16_t lowBytes = read(pc++);
    uint16_t highBytes = read(pc++);
    addrAbs = (highBytes << 8) + lowBytes;
    addrAbs += y;


    if((addrAbs & 0x00FF) != lowBytes)
        return 1;
    return 0;
}

uint8_t olc6502::IND() {
    uint16_t lowBytes = read(pc++);
    uint16_t highBytes = read(pc++);
    uint16_t pointer = (highBytes << 8) + lowBytes;

    if(lowBytes == 0x00FF)
        addrAbs = ((pointer & 0xFF00) | read(pointer)); // Bug in hardware
    else 
        addrAbs = (read(pointer + 1) << 8) + read(pointer);

    return 0;
}

uint8_t olc6502::IZX() {
    uint16_t pointer = read(pc++);

    uint16_t lowBytes = read((uint16_t)(pointer + (uint16_t)x) & 0x00FF);
    uint16_t highBytes = read((uint16_t)(pointer + (uint16_t)x + 1) & 0x00FF);

    addrAbs = (highBytes << 8) + lowBytes;

    return 0;
}

uint8_t olc6502::IZY() {
    uint16_t pointer = read(pc++);

    uint16_t lowBytes = read(pointer & 0x00FF);
    uint16_t highBytes = read((pointer + 1) & 0x00FF);

    addrAbs = (highBytes << 8) + lowBytes;
    addrAbs += y;

    if((addrAbs & 0x00FF) != lowBytes)
        return 1;
    return 0;
}

uint8_t olc6502::REL() {
    addrRel = read(pc++);

    if(addrRel & 0x80)
        addrRel |= 0xFF00;
    return 0;
}

// Instructions

uint8_t olc6502::fetch() {
    if(lookup[opCode].addrMode != &olc6502::IMP) 
        fetched = read(addrAbs);
    return fetched;
}

/*
--- ARITHMETIC OPERATIONS ---

ADC: Add with Carry
Operation: A = A + M + C
Flags Affected: N, Z, C, V
Adds a memory byte and the Carry flag to the Accumulator.

SBC: Subtract with Carry
Operation: A = A - M - (1 - C)
Flags Affected: N, Z, C, V
Subtracts a memory byte and the inverse of the Carry flag from the Accumulator.

CMP: Compare Accumulator with Memory
Operation: A - M
Flags Affected: N, Z, C
Subtracts memory from A without storing the result. Sets Z if A == M, C if A >= M, and N if negative.

CPX: Compare X Register with Memory
Operation: X - M
Flags Affected: N, Z, C
Subtracts memory from X without storing the result. Updates flags to show relative values.

CPY: Compare Y Register with Memory
Operation: Y - M
Flags Affected: N, Z, C
Subtracts memory from Y without storing the result. Updates flags to show relative values.
*/

/*
--- LOGICAL OPERATIONS ---
AND: Bitwise AND with Accumulator
Operation: A = A & M
Flags Affected: N, Z
Performs bitwise AND between Accumulator and memory. Useful for masking off bits.

ORA: Bitwise Inclusive OR with Accumulator
Operation: A = A | M
Flags Affected: N, Z
Performs bitwise OR between Accumulator and memory. Useful for setting specific bits.

EOR: Bitwise Exclusive OR with Accumulator
Operation: A = A ^ M
Flags Affected: N, Z
Performs bitwise XOR between Accumulator and memory. Useful for toggling specific bits.

BIT: Test Bits in Memory against Accumulator
Operation: Z = (A & M == 0), N = Bit 7 of M, V = Bit 6 of M
Flags Affected: N, Z, V
Tests bits in memory without modifying A. Sets Z based on AND result; copies bits 7 and 6 directly to N and V.
*/

/*
--- INCREMENT & DECREMENT OPERATIONS ---

INC: Increment Memory
Operation: M = M + 1
Flags Affected: N, Z
Adds 1 to the contents of a memory location.

DEC: Decrement Memory
Operation: M = M - 1
Flags Affected: N, Z
Subtracts 1 from the contents of a memory location.

INX: Increment X Register
Operation: X = X + 1
Flags Affected: N, Z
Adds 1 to the X register.

DEX: Decrement X Register
Operation: X = X - 1
Flags Affected: N, Z
Subtracts 1 from the X register.

INY: Increment Y Register
Operation: Y = Y + 1
Flags Affected: N, Z
Adds 1 to the Y register.

DEY: Decrement Y Register
Operation: Y = Y - 1
Flags Affected: N, Z
Subtracts 1 from the Y register.
*/

/*
--- SHIFT & ROTATE OPERATIONS ---

ASL: Arithmetic Shift Left
Operation: C <- [76543210] <- 0
Flags Affected: N, Z, C
Shifts all bits in A or memory left by 1. Bit 7 goes into Carry, and Bit 0 becomes 0.

LSR: Logical Shift Right
Operation: 0 -> [76543210] -> C
Flags Affected: N, Z, C
Shifts all bits in A or memory right by 1. Bit 0 goes into Carry, and Bit 7 becomes 0.

ROL: Rotate Left
Operation: C <- [76543210] <- C
Flags Affected: N, Z, C
Shifts all bits left by 1. Bit 7 moves into Carry, and the previous Carry bit moves into Bit 0.

ROR: Rotate Right
Operation: C -> [76543210] -> C
Flags Affected: N, Z, C
Shifts all bits right by 1. Bit 0 moves into Carry, and the previous Carry bit moves into Bit 7.
*/

/*
--- LOAD & STORE OPERATIONS ---

LDA: Load Accumulator
Operation: A = M
Flags Affected: N, Z
Reads a byte from memory and loads it into the Accumulator.

LDX: Load X Register
Operation: X = M
Flags Affected: N, Z
Reads a byte from memory and loads it into the X register.

LDY: Load Y Register
Operation: Y = M
Flags Affected: N, Z
Reads a byte from memory and loads it into the Y register.

STA: Store Accumulator
Operation: M = A
Flags Affected: None
Writes the contents of the Accumulator into memory.

STX: Store X Register
Operation: M = X
Flags Affected: None
Writes the contents of the X register into memory.

STY: Store Y Register
Operation: M = Y
Flags Affected: None
Writes the contents of the Y register into memory.
*/

/*
--- REGISTER TRANSFERS ---

TAX: Transfer Accumulator to X
Operation: X = A
Flags Affected: N, Z
Copies the current value of the Accumulator into register X.

TXA: Transfer X to Accumulator
Operation: A = X
Flags Affected: N, Z
Copies the current value of register X into the Accumulator.

TAY: Transfer Accumulator to Y
Operation: Y = A
Flags Affected: N, Z
Copies the current value of the Accumulator into register Y.

TYA: Transfer Y to Accumulator
Operation: A = Y
Flags Affected: N, Z
Copies the current value of register Y into the Accumulator.

TSX: Transfer Stack Pointer to X
Operation: X = SP
Flags Affected: N, Z
Copies the low byte of the Stack Pointer into register X.

TXS: Transfer X to Stack Pointer
Operation: SP = X
Flags Affected: None
Copies the value in register X into the Stack Pointer register.
*/

/*
--- CONDITIONAL BRANCHES ---

BCC: Branch if Carry Clear
Operation: If C == 0, PC = PC + offset
Flags Affected: None
Jumps relative to the current Program Counter if the Carry flag is 0.

BCS: Branch if Carry Set
Operation: If C == 1, PC = PC + offset
Flags Affected: None
Jumps relative to the current Program Counter if the Carry flag is 1.

BEQ: Branch if Equal (Zero Set)
Operation: If Z == 1, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Zero flag is 1 (meaning the last operation resulted in 0).

BNE: Branch if Not Equal (Zero Clear)
Operation: If Z == 0, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Zero flag is 0 (meaning the last operation was non-zero).

BMI: Branch if Minus (Negative Set)
Operation: If N == 1, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Negative flag is 1.

BPL: Branch if Plus (Negative Clear)
Operation: If N == 0, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Negative flag is 0.

BVC: Branch if Overflow Clear
Operation: If V == 0, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Overflow flag is 0.

BVS: Branch if Overflow Set
Operation: If V == 1, PC = PC + offset
Flags Affected: None
Jumps relative to PC if the Overflow flag is 1.
*/

/*
--- STACK OPERATIONS ---

PHA: Push Accumulator
Operation: Stack[SP--] = A
Flags Affected: None
Pushes the Accumulator onto the stack and decrements SP.

PLA: Pull (Pop) Accumulator
Operation: A = Stack[++SP]
Flags Affected: N, Z
Increments SP and pops the top byte of the stack into the Accumulator.

PHP: Push Processor Status
Operation: Stack[SP--] = Status | BreakFlag | UnusedFlag
Flags Affected: None
Pushes the Status Register (P) onto the stack with Break and Unused bits set.

PLP: Pull (Pop) Processor Status
Operation: Status = Stack[++SP]
Flags Affected: All
Increments SP and pops the top byte of the stack directly into the Status Register.
*/

/*
--- STATUS FLAG MANIPULATION ---

CLC: Clear Carry Flag
Operation: C = 0
Flags Affected: C
Sets the Carry flag to 0.

SEC: Set Carry Flag
Operation: C = 1
Flags Affected: C
Sets the Carry flag to 1.

CLI: Clear Interrupt Disable
Operation: I = 0
Flags Affected: I
Enables hardware interrupts by setting the Interrupt Disable flag to 0.

SEI: Set Interrupt Disable
Operation: I = 1
Flags Affected: I
Disables hardware interrupts by setting the Interrupt Disable flag to 1.

CLD: Clear Decimal Mode
Operation: D = 0
Flags Affected: D
Disables Binary Coded Decimal (BCD) math mode.

SED: Set Decimal Mode
Operation: D = 1
Flags Affected: D
Enables Binary Coded Decimal (BCD) math mode.

CLV: Clear Overflow Flag
Operation: V = 0
Flags Affected: V
Sets the Overflow flag to 0.
*/

/*
--- JUMPS, SUBROUTINES & INTERRUPTS ---

JMP: Jump to Target Address
Operation: PC = address
Flags Affected: None
Sets the Program Counter directly to the target address (unconditional jump).

JSR: Jump to Subroutine
Operation: Push (PC - 1) to Stack, PC = target address
Flags Affected: None
Pushes the return address onto the stack and sets PC to the start of a function.

RTS: Return from Subroutine
Operation: PC = Pop Address + 1
Flags Affected: None
Pops the return address off the stack and sets PC to resume execution after JSR.

BRK: Force Break / Software Interrupt
Operation: Push (PC + 2) & Status to Stack, PC = Vector ($FFFE/$FFFF)
Flags Affected: B = 1, I = 1
Generates a software interrupt, pushing PC and flags before jumping to the IRQ vector.

RTI: Return from Interrupt
Operation: Status = Pop Status, PC = Pop Address
Flags Affected: All
Restores the Status Register and PC from the stack to resume execution prior to an interrupt.
*/

/*
--- SYSTEM / NO OPERATION ---

NOP: No Operation
Operation: None
Flags Affected: None
Performs no operation other than advancing PC and taking 2 clock cycles.
*/
 
// Arithmetic Operations

//! value = accum + fetched + carry bit and then I have to worry about overflows
uint8_t olc6502::ADC() {
    fetch();

    tempVal = (uint16_t)accum + (uint16_t)fetched + (uint16_t)getFlag(C);
    setFlag(C, tempVal > 255);
    setFlag(Z, (tempVal & 0x00FF) == 0);
    setFlag(V, (~((uint16_t)accum ^ (uint16_t)fetched) & ((uint16_t)accum ^ (uint16_t)tempVal) & 0x0080));
    setFlag(N, tempVal & 0x80);

    accum = tempVal & 0x00FF;

    return 1;
}

//! value = accum - fetched - (1 - C) = accum + (-M) + 1 + C. So it's almost identical to addition.
uint8_t olc6502::SBC() {
    fetch();

    uint16_t val = (uint16_t)fetched ^ 0x00FF;
    tempVal = (uint16_t)accum + (uint16_t)val+ (uint16_t)getFlag(C);
    setFlag(C, tempVal & 0xFF00);
    setFlag(Z, (tempVal & 0x00FF) == 0);
    setFlag(V, (tempVal ^ (uint16_t)accum) & (tempVal ^ val) & 0x0080);
    setFlag(N, tempVal & 0x80);

    accum = tempVal & 0x00FF;

    return 1;
}

uint8_t olc6502::CMP() {
    fetch();

    tempVal = (uint16_t)accum - (uint16_t)fetched;
    setFlag(C, accum >= fetched);
    setFlag(Z, (tempVal & 0x00FF) == 0x0000);
    setFlag(N, tempVal & 0x0080);
    return 1;
}

uint8_t olc6502::CPX() {
    fetch();

    tempVal = (uint16_t)x - (uint16_t)fetched;
    setFlag (C, x >= fetched);
    setFlag(Z, (tempVal & 0x00FF) == 0x0000);
    setFlag(N, tempVal & 0x0080);
    return 0;
}

uint8_t olc6502::CPY() {
    fetch();

    tempVal = (uint16_t)y - (uint16_t)fetched;
    setFlag (C, y >= fetched);
    setFlag(Z, (tempVal & 0x00FF) == 0x0000);
    setFlag(N, tempVal & 0x0080);
    return 0;
}

// Logical Operations

uint8_t olc6502::AND() {
    fetch();

    accum = accum & fetched;    
    setFlag(Z, accum == 0x00);
    setFlag(N, accum & 0x80);

    return 1;
}

uint8_t olc6502::ORA() {
    fetch();

    accum = accum | fetched;    
    setFlag(Z, accum == 0x00);
    setFlag(N, accum & 0x80);

    return 1;
}

uint8_t olc6502::EOR() {
    fetch();

    accum = accum ^ fetched;    
    setFlag(Z, accum == 0x00);
    setFlag(N, accum & 0x80);

    return 1;
}

uint8_t olc6502::BIT() {
    fetch();

    tempVal = accum & fetched;
    setFlag(Z, (tempVal & 0x00FF) == 0x00);
    setFlag(N, fetched & (1 << 7));
    setFlag(V, fetched & (1 << 6));

    return 1;
}

//Increment & Decrement Operations

uint8_t olc6502::INC() {
    fetch();
    tempVal = fetched + 1;
    write(addrAbs, tempVal & 0x00FF);
    setFlag(Z, (tempVal & 0x00FF) == 0x0000);
	setFlag(N, tempVal & 0x0080);
	return 0;
}

uint8_t olc6502::DEC() {
    fetch();
    tempVal = fetched - 1;
    write(addrAbs, tempVal & 0x00FF);
    setFlag(Z, (tempVal & 0x00FF) == 0x0000);
	setFlag(N, tempVal & 0x0080);
	return 0;
}

uint8_t olc6502::INX() {
    x++;
    setFlag(Z, x == 0x0000);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t olc6502::DEX() {
    x--;
    setFlag(Z, x == 0x0000);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t olc6502::INY() {
    y++;
    setFlag(Z, y == 0x0000);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t olc6502::DEY() {
    y--;
    setFlag(Z, y == 0x0000);
	setFlag(N, y & 0x80);
	return 0;
}

// Shift & Rotate Operations

uint8_t olc6502::ASL() {
    fetch();
    tempVal = (uint16_t)fetched << 1;
    setFlag(C, (tempVal & 0xFF00) > 0);
	setFlag(Z, (tempVal & 0x00FF) == 0x00);
	setFlag(N, tempVal & 0x0080);

    if(lookup[opCode].addrMode == &olc6502::IMP)
        accum = tempVal & 0x00FF;
    else    
        write(addrAbs, tempVal & 0x00FF);
	return 0;
}

uint8_t olc6502::LSR() {
    fetch();
    tempVal = (uint16_t)fetched >> 1;
    setFlag(C, fetched & 0x0001);
	setFlag(Z, (tempVal & 0x00FF) == 0x00);
	setFlag(N, tempVal & 0x0080);

    if(lookup[opCode].addrMode == &olc6502::IMP)
        accum = tempVal & 0x00FF;
    else    
        write(addrAbs, tempVal & 0x00FF);
	return 0;
}

uint8_t olc6502::ROL() {
    fetch();
    tempVal = (uint16_t)(fetched << 1) | getFlag(C);
    setFlag(C, tempVal & 0xFF00);
	setFlag(Z, (tempVal & 0x00FF) == 0x00);
	setFlag(N, tempVal & 0x0080);

    if(lookup[opCode].addrMode == &olc6502::IMP)
        accum = tempVal & 0x00FF;
    else    
        write(addrAbs, tempVal & 0x00FF);
	return 0;
}

uint8_t olc6502::ROR() {
	fetch();
	tempVal = (uint16_t)(getFlag(C) << 7) | (fetched >> 1);
	setFlag(C, fetched & 0x01);
	setFlag(Z, (tempVal & 0x00FF) == 0x00);
	setFlag(N, tempVal & 0x0080);
	if (lookup[opCode].addrMode == &olc6502::IMP)
		accum = tempVal & 0x00FF;
	else
		write(addrAbs, tempVal & 0x00FF);
	return 0;
}

// Load & Store Operations
uint8_t olc6502::LDA() {
    fetch();
    accum = fetched;
    setFlag(Z, accum == 0x00);
    setFlag(N, accum & 0x80);
    return 1;
}

uint8_t olc6502::LDX() {
    fetch();
    x = fetched;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 1;
}

uint8_t olc6502::LDY() {
    fetch();
    y = fetched;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 1;
}

uint8_t olc6502::STA() {
    write(addrAbs, accum);
    return 0;
}

uint8_t olc6502::STX() {
    write(addrAbs, x);
    return 0;
}

uint8_t olc6502::STY() {
    write(addrAbs, y);
    return 0;
}

// Register Transfers

uint8_t olc6502::TAX() {
    x = accum;
    setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t olc6502::TXA() {
    accum = x;
    setFlag(Z, accum == 0x00);
	setFlag(N, accum & 0x80);
	return 0;
}

uint8_t olc6502::TAY() {
    y = accum;
    setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t olc6502::TYA() {
    accum = y;
    setFlag(Z, accum == 0x00);
	setFlag(N, accum & 0x80);
	return 0;
}

uint8_t olc6502::TSX() {
    x = stp;
    setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t olc6502::TXS() {
    stp = x;
	return 0;
}

// Conditional Branching   

uint8_t olc6502::BCC() {
    if(getFlag(C) == 0) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BCS() {
    if(getFlag(C) == 1) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BEQ() {
    if(getFlag(Z) == 1) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BNE() {
    if(getFlag(Z) == 0) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BMI() {
    if(getFlag(N) == 1) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BPL() {
    if(getFlag(N) == 0) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BVC() {
    if(getFlag(V) == 0) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

uint8_t olc6502::BVS() {
    if(getFlag(V) == 1) {
        cycles++;
        addrAbs = addrRel + pc;

        if((addrAbs & 0xFF00) != (pc & 0xFF00)) {
            cycles++;
        }

        pc = addrAbs;
    }

    return 0;
}

// Stack operations
uint8_t olc6502::PHA() {
    write(0x0100 + stp, accum);
    stp--;
    return 0;
}

uint8_t olc6502::PLA() {
    
    stp++;
    accum = read(0x0100 + stp);
    setFlag(N, accum & 0x80);
    setFlag(Z, accum == 0x00);
    return 0;
}

uint8_t olc6502::PHP() {
    write(0x0100 + stp, status | B | U);
    stp--;
    setFlag(B, 0);
    setFlag(U, 0);
    return 0;
}

uint8_t olc6502::PLP() {
    stp++;
    status = read(0x0100 + stp);
    setFlag(U, 1);
    return 0;
}


// Flag manipulations 
uint8_t olc6502::CLC() {
    setFlag(C, 0);
    return 0;
}

uint8_t olc6502::SEC() {
    setFlag(C, 1);
    return 0;
}

uint8_t olc6502::CLI() {
    setFlag(I, 0);
    return 0;
}

uint8_t olc6502::SEI() {
    setFlag(I, 1);
    return 0;
}

uint8_t olc6502::CLD() {
    setFlag(D, 0);
    return 0;
}

uint8_t olc6502::SED() {
    setFlag(D, 1);
    return 0;
}

uint8_t olc6502::CLV() {
    setFlag(V, 0);
    return 0;
}


//Jumps, Subroutines, System calls
uint8_t olc6502::JMP() {
    pc = addrAbs;
    return 0;
}

uint8_t olc6502::JSR() {
	pc--;

	write(0x0100 + stp, (pc >> 8) & 0x00FF);
	stp--;
	write(0x0100 + stp, pc & 0x00FF);
	stp--;

	pc = addrAbs;
	return 0;
}

uint8_t olc6502::RTS() {
	stp++;
	pc = (uint16_t)read(0x0100 + stp);
	stp++;
	pc |= (uint16_t)read(0x0100 + stp) << 8;
	
	pc++;
	return 0;
}

uint8_t olc6502::BRK() {
	pc++;
	
	setFlag(I, 1);
	write(0x0100 + stp, (pc >> 8) & 0x00FF);
	stp--;
	write(0x0100 + stp, pc & 0x00FF);
	stp--;

	setFlag(B, 1);
	write(0x0100 + stp, status);
	stp--;
	setFlag(B, 0);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

uint8_t olc6502::RTI() {
	stp++;
	status = read(0x0100 + stp);
	status &= ~B;
	status &= ~U;

	stp++;
	pc = (uint16_t)read(0x0100 + stp);
	stp++;
	pc |= (uint16_t)read(0x0100 + stp) << 8;
	return 0;
}

uint8_t olc6502::NOP() {
    // diff op codes based on game compatibility and illegal
    if (opCode == 0x1C || 
        opCode == 0x3C || 
        opCode == 0x5C || 
        opCode == 0x7C || 
        opCode == 0xDC || 
        opCode == 0xFC) {
        return 1;
    }

    return 0;
}

uint8_t olc6502::XXX() {
	return 0;
}

bool olc6502::complete()
{
	return cycles == 0;
}

std::map<uint16_t, std::string> olc6502::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->read(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookup[opcode].addrMode == &olc6502::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrMode == &olc6502::IMM)
		{
			value = bus->read(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ZP0)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ZPX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ZPY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrMode == &olc6502::IZX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrMode == &olc6502::IZY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ABS)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ABX)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrMode == &olc6502::ABY)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrMode == &olc6502::IND)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrMode == &olc6502::REL)
		{
			value = bus->read(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}