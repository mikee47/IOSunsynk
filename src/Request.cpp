/**
 * Modbus/Sunsynk/Request.cpp
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

#include "include/Sunsynk/Request.h"
#include <IO/Strings.h>

namespace IO
{
namespace Modbus
{
namespace Sunsynk
{
Function Request::fillRequestData(PDU::Data& data)
{
	if(getCommand() == Command::query) {
		if(!range) {
			range.reset(new Range[6]{
				{Register::RunState, Register::GridImportTotal},
				{Register::GridFrequency, Register::PvEnergyTotalHigh},
				{Register::PvEnergyToday, Register::Pv2Current},
				{Register::GridVoltage, Register::InverterCurrentL1},
				{Register::AuxPower, Register::LoadCurrentL2},
				{Register::BatteryTemp, Register::AuxRelayStatus},
			});
			rangeCount = 6;
			rangeIndex = 0;
		}
		auto& r = range[rangeIndex];
		auto& req = data.readHoldingRegisters.request;
		req.startAddress = getRegInfo(r.first).addr;
		req.quantityOfRegisters = 1 + getRegInfo(r.last).addr - req.startAddress;
		return Function::ReadHoldingRegisters;
	}

	// Send an invalid instruction
	debug_e("fillRequestData() - UNEXPECTED");
	return Function::None;
}

ErrorCode Request::callback(PDU& pdu)
{
	switch(pdu.function()) {
	case Function::ReadHoldingRegisters: {
		auto& rsp = pdu.data.readHoldingRegisters.response;

		if(range) {
			auto& r = range[rangeIndex];
			getDevice().updateRegisters(r.first, rsp.values, rsp.getCount());

			++rangeIndex;
			if(rangeIndex < rangeCount) {
				submit();
				return Error::pending;
			}

			range.reset();
			rangeIndex = rangeCount = 0;
		}

		break;
	}

	default:
		return Error::bad_command;
	}

	return Error::success;
}

void Request::getJson(JsonObject json) const
{
	Modbus::Request::getJson(json);

	if(error()) {
		return;
	}

	auto values = json.createNestedObject(FS_value);
	getDevice().getValues(values);
}

} // namespace Sunsynk
} // namespace Modbus
} // namespace IO
