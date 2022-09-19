/**
 * Modbus/Synsynk/Device.h
 *
 * Copyright 2022 mikee47 <mike@sillyhouse.net>
 *
 * This file is part of the IOControl Library
 *
 * This library is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, version 3 or later.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this library.
 * If not, see <https://www.gnu.org/licenses/>.
 *
 *
 ****/

#pragma once

#include "Sunsynk.h"
#include <WHashMap.h>
#include <ArduinoJson.h>

namespace IO::Modbus::Sunsynk
{
struct Range {
	Register first;
	Register last;
};

class RegisterSet : public HashMap<Register, uint16_t>
{
public:
	void add(Range range, uint16_t value = 0)
	{
		for(unsigned i = unsigned(range.first); i <= unsigned(range.last); ++i) {
			(*this)[Register(i)] = value;
		}
	}

	void add(std::initializer_list<Range> ranges, uint16_t value = 0)
	{
		for(auto& r : ranges) {
			add(r, value);
		}
	}

	void add(std::initializer_list<Register> registers, uint16_t value = 0)
	{
		for(auto r : registers) {
			(*this)[r] = value;
		}
	}

	RegInfo regInfoAt(unsigned index) const
	{
		return getRegInfo(keyAt(index));
	}

	int getRawValue(Register reg) const;
	float getValue(Register reg) const;
	String getValueString(Register reg) const;
	void getValues(JsonObject json) const;

	bool isAuxOutputActive() const
	{
		return getRawValue(Register::AuxRelayStatus) == 0x0011;
	}
};

} // namespace IO::Modbus::Sunsynk

String toString(IO::Modbus::Sunsynk::Register reg);
