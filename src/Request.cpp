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

// Inverter responds with timeout if request too large
#define MAX_REQUEST_REGCOUNT 20U

namespace IO
{
namespace Modbus
{
namespace Sunsynk
{
Function Request::fillRequestData(PDU::Data& data)
{
	if(getCommand() == Command::query) {
		if(regset.count() == 0) {
			regset.add({
				{Register::RunState, Register::GridImportTotal},
				{Register::GridFrequency, Register::PvEnergyTotalHigh},
				{Register::PvEnergyToday, Register::Pv2Current},
				{Register::GridVoltage, Register::InverterCurrentL1},
				{Register::AuxPower, Register::LoadCurrentL2},
				{Register::BatteryTemp, Register::AuxRelayStatus},
			});
		}
		if(regIndex == 0) {
			regset.sort([](auto& a, auto& b) { return a.key() < b.key(); });
		}

		auto& req = data.readHoldingRegisters.request;
		auto startReg = regset.keyAt(regIndex);
		req.startAddress = getRegInfo(startReg).addr;
		auto endAddress = req.startAddress;
		unsigned i = regIndex + 1;
		for(; i < regset.count(); ++i) {
			auto info = regset.regInfoAt(i);
			if(info.getAttr(Attr::Virtual)) {
				// Virtual registers are defined *after* physical registers
				break;
			}
			if(info.addr >= req.startAddress + MAX_REQUEST_REGCOUNT) {
				break;
			}
			endAddress = info.addr;
		}
		auto n = 1 + endAddress - req.startAddress;
		req.quantityOfRegisters = n;

		debug_d("[SS] read %s -> %s (%u registers)", toString(startReg).c_str(), toString(regset.keyAt(i - 1)).c_str(),
				n);

		return Function::ReadHoldingRegisters;
	}

	if(getCommand() == Command::set) {
		if(regIndex == 0) {
			regset.sort([](auto& a, auto& b) { return a.key() < b.key(); });
		}
		auto& req = data.writeMultipleRegisters.request;
		auto startReg = regset.keyAt(regIndex);
		req.startAddress = getRegInfo(startReg).addr;
		req.values[0] = regset.valueAt(regIndex);
		size_t n{1};
		auto addr = req.startAddress + 1;
		for(unsigned i = regIndex + 1; i < regset.count() && n < MAX_REQUEST_REGCOUNT; ++i, ++addr, ++n) {
			auto info = regset.regInfoAt(i);
			if(info.getAttr(Attr::Virtual)) {
				// Virtual registers are defined *after* physical registers
				break;
			}
			if(info.addr != addr) {
				break;
			}
			req.values[n] = regset.valueAt(i);
		}
		req.setCount(n);

		debug_d("[SS] write %s -> %s (%u registers)", toString(startReg).c_str(),
				toString(Register(unsigned(startReg) + n - 1)).c_str(), n);

		return Function::WriteMultipleRegisters;
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

		if(regIndex >= regset.count()) {
			break;
		}

		auto addr = regset.regInfoAt(regIndex).addr;
		auto regAddr = addr;
		for(unsigned i = 0; i < rsp.getCount(); ++i, ++addr) {
			if(regAddr != addr) {
				continue;
			}

			regset.valueAt(regIndex++) = rsp.values[i];
			if(regIndex == regset.count()) {
				break;
			}
			regAddr = regset.regInfoAt(regIndex).addr;
		}

		if(regIndex >= regset.count() || regset.regInfoAt(regIndex).getAttr(Attr::Virtual)) {
			break;
		}

		submit();
		return Error::pending;
	}

	case Function::WriteMultipleRegisters: {
		auto& rsp = pdu.data.writeMultipleRegisters.response;
		regIndex += rsp.quantityOfRegisters;
		if(regIndex < regset.count() && !regset.regInfoAt(regIndex).getAttr(Attr::Virtual)) {
			submit();
			return Error::pending;
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
	regset.getValues(values);
}

} // namespace Sunsynk
} // namespace Modbus
} // namespace IO
