#include <fstream>
#include <cstdint>
#include <vector>
#include "CPU.h"
#include <SDL2/SDL.h>
#pragma pack(push, 1)
struct SNA_Header
{
	uint8_t I;
	uint16_t HL1;
	uint16_t DE1;
	uint16_t BC1;
	uint16_t AF1;
	uint16_t HL;
	uint16_t DE;
	uint16_t BC;
	uint16_t IY;
	uint16_t IX;
	uint8_t IFF2;
	uint8_t R;
	uint16_t AF;
	uint16_t SP;
	uint8_t IM;
	uint8_t FE;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Z80_Header_1
{
	uint8_t A, F;
	uint8_t C, B;
	uint8_t L, H;
	uint16_t PC;
	uint16_t SP;
	uint8_t I, R;
	uint8_t stuffs1;
	uint8_t E, D;
	uint8_t C1, B1;
	uint8_t E1, D1;
	uint8_t L1, H1;
	uint8_t A1, F1;
	uint8_t IYL, IYH;
	uint8_t IXL, IXH;
	uint8_t IFF1, IFF2;
	uint8_t stuffs2;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Z80_Header_2
{
//	uint16_t hdrlen;
	uint16_t PC;
	uint8_t hw;
	uint8_t ext0;
	uint8_t ext1;
	uint8_t ext2;
	uint8_t ay_last_write;
	uint8_t ay_state[16];
	uint16_t tsc_lo;
	uint8_t tsc_hi;
	uint8_t zero;
	uint8_t whatever[4];
	uint8_t joy[10];
	uint8_t joy2[10];
	uint8_t fsck_those_bytes[4];
};
#pragma pack(pop)
byte In_mem(void* param, ushort address)
{
	return reinterpret_cast<CPU*>(param)->_bus.read(address);
}
void Out_mem(void* param, ushort address,byte data)
{
	reinterpret_cast<CPU*>(param)->_bus.write(address, data);
}
byte In_io(void* param, ushort address)
{
	return reinterpret_cast<CPU*>(param)->_bus.read(address,true);
}
void Out_io(void* param, ushort address,byte data)
{
	reinterpret_cast<CPU*>(param)->_bus.write(address, data,true);
}
CPU::CPU(unsigned __int8 *pram)
{
	ram = pram;
	PC = SP = IX = IY = AF = BC = DE = HL = 0x0000;}
CPU::~CPU()
{}
void CPU::LD16(unsigned __int16& reg, unsigned __int16 val)
{
	reg = val;}
void CPU::LD8LO(unsigned __int16& reg, unsigned __int8 val)
{
	reg = (reg & 0xFF00) + val;}

void CPU::LD8HI(unsigned __int16& reg, unsigned __int8 val)
{
	reg = (val << 8) | LOBYTE(reg);}
void CPU::EX16(unsigned __int16& reg1, unsigned __int16& reg2)
{
	auto tmp = reg1;
	reg1 = reg2;
	reg2 = tmp;}
void CPU::EXX()
{
	EX16(AF, _AF);
	EX16(BC, _BC);
	EX16(DE, _DE);
	EX16(HL, _HL);}
void CPU::save_state_sna(const char *filename)
{
	SNA_Header hdr;
	std::vector<uint8_t> data;
	data.resize(16384 * 3);
	/*for (unsigned memptr = 16384; memptr < 65536; memptr++)
		data[memptr - 16384] = _bus.read(memptr);
	hdr.I = _context.I;
	hdr.HL1 = _context.R2.wr.HL;
	hdr.DE1 = _context.R2.wr.DE;
	hdr.BC1 = _context.R2.wr.BC;
	hdr.AF1 = _context.R2.wr.AF;
	hdr.HL = _context.R1.wr.HL;
	hdr.DE = _context.R1.wr.DE;
	hdr.BC = _context.R1.wr.BC;
	hdr.IY = _context.R1.wr.IY;
	hdr.IX = _context.R1.wr.IX;
	hdr.IFF2 = _context.IFF2;
	hdr.R = _context.R;
	hdr.AF = _context.R1.wr.AF;
	hdr.SP = _context.R1.wr.SP;
	hdr.IM = _context.IM;
	hdr.FE = 0;
	hdr.SP -= 2;
	data[hdr.SP - 16384] = _context.PC & 0x00ff;
	data[hdr.SP - 16384 + 1] = _context.PC >> 8;*/
	std::fstream sna;
	sna.open(filename, std::ios::out | std::ios::binary);
	sna.write(reinterpret_cast<const char *>(&hdr), sizeof(hdr));
	sna.write(reinterpret_cast<const char *>(&data[0]), data.size());
	sna.close();
}
void CPU::Step()
{
	unsigned __int8 prefix = 0;
	auto opcode = ram[PC++];
	if (opcode == 0xDD || opcode == 0xFD || opcode == 0xED)
	{
		prefix = opcode;
		opcode = ram[PC++];}
	if (opcode >= 0x00 && opcode <= 0x0F) Processing_00_0F(opcode, prefix);
}
void CPU::Processing_00_0F(unsigned __int8 opcode, unsigned __int8 prefix)
{
	switch (opcode)
	{
	case 0x00:
		break;
	case 0x01:	 LD16(BC, ram[PC + 1] * 256 + ram[PC]);
		PC += 2;
		break;
	case 0x02:
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x05:
		break;
	case 0x06: LD8HI(BC, ram[PC]);
		PC += 1;
		break;
	case 0x07:
		break;
	case 0x08: EX16(AF, _AF);
		break;
	case 0x09:
		break;
	case 0x0A: LD8HI(AF, ram[BC]);
		break;
	case 0x0B:
		break;
	case 0x0C:
		break;
	case 0x0D:
		break;
	case 0x0E: LD8LO(BC, ram[PC]); PC += 1;
		break;
	case 0x0F:
		break;
	default:
		break;}}


