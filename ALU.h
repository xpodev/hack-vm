#pragma once

#include <tuple>

#include "HackVM.h"


constexpr size_t const
NotResult	= 0b000001000000,
Function	= 0b000010000000,
NotY		= 0b000100000000,
ZeroY		= 0b001000000000,
NotX		= 0b010000000000,
ZeroX		= 0b100000000000;


enum class Hack__ALU_flags : Hack__bit_t {
	None = 0,
	ZeroFlag = 1 << 0,
	NegativeFlag = 1 << 1
};


inline Hack__size_t ALU(Hack__size_t x, Hack__size_t y, Hack__size_t op, Hack__bit_t& flags) {
	if (op & ZeroX) x = 0;
	if (op & ZeroY) y = 0;
	if (op & NotX) x = ~x;
	if (op & NotY) y = ~y;
	Hack__size_t result = op & Function ? x + y : x & y;
	if (op & NotResult) result = ~result;
	flags = static_cast<Hack__bit_t>(
		result == 0 ? Hack__ALU_flags::ZeroFlag : (result < 0 ? Hack__ALU_flags::NegativeFlag : Hack__ALU_flags::None
			));
	return result;
}
