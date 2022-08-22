/*
 * Sunsynk.h
 *
 * GENERATED FILE: DO NOT EDIT
 *
 */

#pragma once

#include <Data/BitSet.h>

// clang-format off

namespace IO::Modbus::Sunsynk
{
enum class Unit {
$enum_Unit
};

extern const char* unitSuffixes[];
extern const uint8_t unitSuffixLengths[];

enum class Attr {
$enum_Attr
};

using Attributes = BitSet<uint8_t, Attr, $enum_Attr_len>;

enum class Register {
$enum_Register
};

constexpr size_t registerCount = $enum_Register_len;

struct RegInfo {
	const FlashString* name;
	uint16_t addr;
	Unit unit;
	int8_t scale;
	uint8_t attr; // Attributes

	bool getAttr(Attr a) const
	{
		return Attributes(attr)[a];
	}
};

RegInfo getRegInfo(Register reg);

} // namespace IO::Modbus::Sunsynk
