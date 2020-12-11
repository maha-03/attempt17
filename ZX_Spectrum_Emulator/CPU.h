#ifndef CPU_H_
#define CPU_H_

#pragma once

#define LOBYTE(w) ((unsigned __int8)(w))
#define HIBYTE(w) ((unsigned __int8)(((unsigned __int16)(w) >> 8) & 0xFF))

 /*byte In_mem	(void* param, ushort address);
 void Out_mem (void* param, ushort address, byte data);
 byte In_io	(void* param, ushort address);
 void Out_io (void* param, ushort address, byte data);*/

class CPU
{
protected:
	unsigned __int8 *ram;
public:
	unsigned __int16 PC;
	unsigned __int16 AF;
	unsigned __int16 BC;
	unsigned __int16 DE;
	unsigned __int16 HL;
	unsigned __int16 IX;
	unsigned __int16 IY;
	unsigned __int16 SP;
	unsigned __int16 IR;
	unsigned __int16 _AF;
	unsigned __int16 _BC;
	unsigned __int16 _DE;
	unsigned __int16 _HL;
public:
	CPU(unsigned __int8 *pram);
	~CPU();
	void Step();
protected:
	void Processing_00_0F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_10_1F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_20_2F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_30_3F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_40_4F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_50_5F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_60_6F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_70_7F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_80_8F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_90_9F(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_A0_AF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_B0_BF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_C0_CF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_D0_DF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_E0_EF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
	void Processing_F0_FF(unsigned __int8 opcode, unsigned __int8 prefix = 0);
public:
	/*CPU(AddressSpace & bus): _bus(bus) {
	_context.memRead = In_mem;
	_context.memWrite = Out_mem;
	_context.ioRead = In_io;
	_context.ioWrite = Out_io;
	_context.ioParam = this;
	_context.memParam = this;
};*/
	void save_state_sna(const char * filename);
	static void LD16(unsigned __int16& reg, unsigned __int16 val);
	static void LD8LO(unsigned __int16& reg, unsigned __int8 val);
	static void LD8HI(unsigned __int16& reg, unsigned __int8 val);
	static void EX16(unsigned __int16& reg1, unsigned __int16& reg2);
	void EXX();
};
#endif /* CPU_H_ */
