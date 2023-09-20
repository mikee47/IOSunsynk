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
enum class Unit: uint8_t {
$enum_Unit
};

extern const char* unitSuffixes[];
extern const uint8_t unitSuffixLengths[];

enum class Attr: uint8_t {
$enum_Attr
};

using Attributes = BitSet<uint8_t, Attr, $enum_Attr_len>;

enum class Register: uint8_t {
$enum_Register
};

constexpr size_t registerCount = $enum_Register_len;

struct RegInfo {
	const FlashString* name;
	uint16_t addr;
	Unit unit;
	int8_t scale;
	uint8_t attr; // Attributes
	Register reg2; // Complementary register (low or high)

	bool getAttr(Attr a) const
	{
		return Attributes(attr)[a];
	}
};

static_assert(sizeof(RegInfo) == 12);

RegInfo getRegInfo(Register reg);

} // namespace IO::Modbus::Sunsynk

inline String toString(::IO::Modbus::Sunsynk::Register reg)
{
	return *getRegInfo(reg).name;
}
