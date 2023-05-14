/**
 * Modbus/Sunsynk/Device.cpp
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
 ****/

#include "include/Sunsynk/Register.h"

namespace IO
{
namespace Modbus
{
namespace Sunsynk
{
namespace
{
enum {
	SCALE_0_001 = -3,
	SCALE_0_01 = -2,
	SCALE_0_1 = -1,
	SCALE_NONE = 0,
	SCALE_10 = 1,
	SCALE_100 = 2,
	SCALE_1000 = 3,
};

float valueToFloat(int value, Unit unit, int scale)
{
	switch(unit) {
	case Unit::CELSIUS:
	case Unit::POWERFACTOR:
		value -= 1000;
		break;
	case Unit::BCDTIME:
		// e.g. 1735 = 17:35, convert to seconds
		value = (SECS_PER_HOUR * (value / 100)) + (value % 100);
		break;

	default:;
	}

	switch(scale) {
	case SCALE_0_001:
		return value * 0.001;
	case SCALE_0_01:
		return value * 0.01;
	case SCALE_0_1:
		return value * 0.1;
	case SCALE_10:
		return value * 10;
	case SCALE_100:
		return value * 100;
	case SCALE_1000:
		return value * 1000;
	case SCALE_NONE:
	default:
		return value;
	}
}

String valueToString(int value, Unit unit, int scale)
{
	char buffer[32];
	unsigned len{0};

	switch(unit) {
	case Unit::CELSIUS:
	case Unit::POWERFACTOR:
		value -= 1000;
		break;
	case Unit::HEXVAL:
		buffer[0] = '0';
		buffer[1] = 'x';
		ultoa_wp(value, buffer + 2, 16, 4, '0');
		return String(buffer, 6);
	case Unit::BCDTIME:
		ultoa_wp(value, buffer, 10, 4, '0');
		memmove(buffer + 3, buffer + 2, 2);
		buffer[2] = ':';
		return String(buffer, 5);
	default:;
	}

	// Convert to string without using floating point

	char dp = (unit == Unit::OHM) ? 'R' : '.';

	if(value == 0 || scale == 0) {
		// No DP
		ltoa(value, buffer, 10);
		len = strlen(buffer);
	} else if(scale < 0) {
		bool neg = (value < 0);
		char* bufptr = buffer;
		if(neg) {
			value = -value;
			*bufptr++ = '-';
		}
		ultoa(value, bufptr, 10);
		len = strlen(bufptr);
		scale = -scale;
		if(unsigned(scale) >= len) {
			unsigned zeroes = 1 + scale - len;
			memmove(bufptr + zeroes, bufptr, len);
			memset(bufptr, '0', zeroes);
			len += zeroes;
		}
		unsigned dpOffset = len - scale;
		memmove(bufptr + dpOffset + 1, bufptr + dpOffset, len - dpOffset);
		bufptr[dpOffset] = dp;
		++len;
		len += neg;
	} else {
		// r.scale > 0
		ultoa(value, buffer, 10);
		len = strlen(buffer);
		while(scale-- != 0) {
			buffer[len++] = '0';
		}
	}

	auto suffixLen = unitSuffixLengths[unsigned(unit)];
	if(suffixLen != 0) {
		memcpy(buffer + len, unitSuffixes[unsigned(unit)], suffixLen);
		len += suffixLen;
	}
	return String(buffer, len);
}

} // namespace

int RegisterSet::getRawValue(Register reg) const
{
	auto info = getRegInfo(reg);
	if(info.getAttr(Attr::Virtual)) {
		auto getPvPowerTotal = [this]() { return getRawValue(Register::Pv1Power) + getRawValue(Register::Pv2Power); };
		switch(reg) {
		case Register::Efficiency: {
			unsigned powerIn = getPvPowerTotal();
			unsigned powerOut = getRawValue(Register::LoadPowerTotal);
			int batteryPower = getRawValue(Register::BatteryPower);
			if(batteryPower < 0) {
				powerOut += -batteryPower;
			} else {
				powerIn += batteryPower;
			}
			int gridPower = getRawValue(Register::GridPowerTotal);
			if(gridPower < 0) {
				powerOut += -gridPower;
			} else {
				powerIn += gridPower;
			}

			return powerIn ? ((10000U * powerOut / powerIn) + 5) / 10U : 0;
		}

		case Register::PvPowerTotal:
			return getPvPowerTotal();

		default:
			return 0;
		}
	}

	uint16_t value = (*this)[reg];
	return info.getAttr(Attr::Signed) ? int16_t(value) : value;
}

float RegisterSet::getValue(Register reg) const
{
	auto r = getRegInfo(reg);
	return valueToFloat(getRawValue(reg), r.unit, r.scale);
}

String RegisterSet::getValueString(Register reg) const
{
	auto r = getRegInfo(reg);
	return valueToString(getRawValue(reg), r.unit, r.scale);
}

void RegisterSet::getValues(JsonObject json) const
{
	for(auto r : *this) {
		auto info = getRegInfo(r.key());
		json[*info.name] = getValueString(r.key());
	}
}

} // namespace Sunsynk
} // namespace Modbus
} // namespace IO
