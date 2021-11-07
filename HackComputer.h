#pragma once

#include <memory>

#include "CPU.h"


class HackComputer
{
public:
	inline HackComputer(Hack__size_t memory_size)
		: HackComputer(new Hack__size_t[memory_size]{ 0 })
	{

	}

private:
	inline HackComputer(Hack__size_t* memoryPtr)
		: m_memoryPtr(memoryPtr)
	{

	}

public:
	inline ~HackComputer() {
		delete[] m_memoryPtr;
	}


public:
	inline Hack__size_t* memory() {
		return m_memoryPtr;
	}

	inline Hack__size_t const* memory() const {
		return m_memoryPtr;
	}

	inline void run(Hack__size_t* program) {
		Hack__size_t programCounter = 0;
		while (true)
		{
			run(program, programCounter);
		}
	}

	inline void run(Hack__size_t* program, Hack__size_t& programCounter) {
		run(program[programCounter], programCounter);
	}

	inline void run(Hack__size_t instruction, Hack__size_t& programCounter) {
		CPU(instruction, programCounter, m_memoryPtr);
	}

private:
	Hack__size_t* m_memoryPtr;
};

