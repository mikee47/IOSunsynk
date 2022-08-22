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

#include <IO/Modbus/Device.h>
#include "Sunsynk.h"

namespace IO::Modbus::Sunsynk
{
struct Range {
	Register first;
	Register last;
};

class Device : public Modbus::Device
{
	friend class Request;

public:
	class Factory : public FactoryTemplate<Device>
	{
	public:
		const FlashString& deviceClass() const override
		{
			return FS("sunsynk");
		}
	};

	static const Factory factory;

	using Modbus::Device::Device;

	IO::Request* createRequest() override;

	int getRawValue(Register reg) const;
	float getValue(Register reg) const;
	String getValueString(Register reg) const;
	void getValues(JsonObject json) const;

	bool isAuxOutputActive() const
	{
		return getRawValue(Register::AuxRelayStatus) == 0x0011;
	}

	void updateRegisters(Register reg, const void* values, size_t count);

private:
	uint16_t regValues[registerCount]{};
};

} // namespace IO::Modbus::Sunsynk

String toString(IO::Modbus::Sunsynk::Register reg);
