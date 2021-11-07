#pragma once


#include "ALU.h"

constexpr Hack__size_t const
JumpGT = 0b001,
JumpEQ = 0b010,
JumpLT = 0b100,
DestinationM = 0b001000,
DestinationD = 0b010000,
DestinationA = 0b100000,
ControlMask = 0b111111000000,
UseMemory = 0b1000000000000;


inline void CPU(Hack__size_t inst, Hack__size_t& instIndex, Hack__size_t* memory) {
	static Hack__bit_t m_flags = 0;
	static Hack__size_t m_AddressRegister = 0, m_DataRegister = 0;

	if (inst < 0) {
		Hack__size_t result = ALU(
			m_DataRegister, 
			inst & UseMemory ? memory[m_AddressRegister] : m_AddressRegister, 
			inst & ControlMask, 
			m_flags);
		if (inst & DestinationA) m_AddressRegister = result;
		if (inst & DestinationD) m_DataRegister = result;
		if (inst & DestinationM) memory[m_AddressRegister] = result;
		if (
			(inst & JumpGT && result > 0) ||
			(inst & JumpEQ && result == 0) ||
			(inst & JumpLT && result < 0)
			)
			instIndex = m_AddressRegister;
		else instIndex++;
	}
	else {
		m_AddressRegister = inst;
		instIndex++;
	}
}

