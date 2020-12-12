#ifndef CPU_H_
#define CPU_H_

#pragma once

#define LOBYTE(w) ((unsigned __int8)(w))
#define HIBYTE(w) ((unsigned __int8)(((unsigned __int16)(w) >> 8) & 0xFF))
#include "Memory.h"
#include <SDL2/SDL.h>

 byte In_mem	(void* param, ushort address);
 void Out_mem (void* param, ushort address, byte data);
 byte In_io	(void* param, ushort address);
 void Out_io (void* param, ushort address, byte data);

class CPU
{
protected:
	AddressSpace & _bus;
	unsigned __int8 *ram;
	friend byte In_mem	(void* param, ushort address);
	friend void Out_mem (void* param, ushort address, byte data);
	friend byte In_io	(void* param, ushort address);
	friend void Out_io (void* param, ushort address, byte data);
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
public:
	void save_state_sna(const char * filename);
	static void LD16(unsigned __int16& reg, unsigned __int16 val);
	static void LD8LO(unsigned __int16& reg, unsigned __int8 val);
	static void LD8HI(unsigned __int16& reg, unsigned __int8 val);
	static void EX16(unsigned __int16& reg1, unsigned __int16& reg2);
	void EXX();
};
#endif /* CPU_H_ */
