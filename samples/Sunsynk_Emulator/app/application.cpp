#include <SmingCore.h>
#include <IO/Modbus/Debug.h>
#include <IO/Modbus/Slave.h>
#include <Sunsynk/Sunsynk.h>
#include <Data/Range.h>

namespace
{
struct Config {
	uint8_t slaveId{1};
};

IO::Serial serial0;
IO::RS485::Controller rs485_0(serial0, 0);
Config config;

enum Constants {
	COM_PORT_RS485 = 0,
	COM_PORT_DEBUG = 1,
	PIN_MBTX = 1,
	PIN_MBRX = 3,
	PIN_MAX1_DIR = 4,
	PIN_MAX2_DIR = 5,
};

using namespace IO::Modbus::Sunsynk;

uint16_t registers[registerCount];

void IRAM_ATTR setSerialDirection(uint8_t segment, IO::Direction direction)
{
	switch(direction) {
	case IO::Direction::Incoming:
		// First set other segment to output to avoid wire conflict
		if(segment == 1) {
			digitalWrite(PIN_MAX1_DIR, 1);
			digitalWrite(PIN_MAX2_DIR, 0);
		} else {
			digitalWrite(PIN_MAX2_DIR, 1);
			digitalWrite(PIN_MAX1_DIR, 0);
		}
		break;
	case IO::Direction::Outgoing:
		digitalWrite(PIN_MAX1_DIR, 1);
		digitalWrite(PIN_MAX2_DIR, 1);
		break;
	case IO::Direction::Idle:
		// Default to receive on segment #0
		digitalWrite(PIN_MAX2_DIR, 1);
		digitalWrite(PIN_MAX1_DIR, 0);
		break;
	}
}

void handleRS485Request(IO::RS485::Controller& controller)
{
	using namespace IO::Modbus;

	ADU adu;
	auto err = readRequest(controller, adu);
	if(err) {
		return;
	}

#ifndef SMING_RELEASE
	printRequest(Serial, adu);
#endif
	if(adu.slaveAddress != config.slaveId) {
		return;
	}

	auto func = adu.pdu.function();
	switch(func) {
	case Function::WriteSingleRegister: {
		auto& data = adu.pdu.data.writeSingleRegister;
		auto& req{data.request};
		auto& rsp{data.response};

		if(req.address >= registerCount) {
			adu.pdu.setException(Exception::IllegalDataAddress);
			break;
		}

		registers[req.address] = req.value;
		rsp.value = req.value;

		break;
	}

	case Function::WriteMultipleRegisters: {
		auto& data = adu.pdu.data.writeMultipleRegisters;
		auto& req{data.request};
		auto& rsp{data.response};
		auto addr = req.startAddress;

		if(addr > registerCount) {
			adu.pdu.setException(Exception::IllegalDataAddress);
			break;
		}
		auto n = std::min(size_t(req.quantityOfRegisters), registerCount - addr);
		for(unsigned i = 0; i < n; ++i) {
			registers[addr + i] = req.values[i];
		}
		rsp.quantityOfRegisters = n;
		break;
	}

	case Function::ReadHoldingRegisters: {
		auto& data = adu.pdu.data.readHoldingRegisters;
		auto& req{data.request};
		auto& rsp{data.response};
		auto addr = req.startAddress;

		if(addr > registerCount) {
			adu.pdu.setException(Exception::IllegalDataAddress);
			break;
		}

		auto n = std::min(size_t(req.quantityOfRegisters), registerCount - addr);
		rsp.setCount(n);
		for(unsigned i = 0; i < n; ++i) {
			rsp.values[i] = registers[addr + i];
		}
		break;
	}

	default:
		adu.pdu.setException(Exception::IllegalFunction);
	}

#ifndef SMING_RELEASE
	printResponse(Serial, adu);
#endif
	sendResponse(controller, adu);
}

// Set up MAX485 direction control pins and enable serial port for RS485
bool initModbus()
{
	auto err = serial0.open(COM_PORT_RS485, PIN_MBTX, PIN_MBRX);
	if(err) {
		debug_e("Error opening serial port: %s", toString(err).c_str());
		return false;
	}

	// Set up the transmit enable GPIO which toggles MAX485 direction
	pinMode(PIN_MAX1_DIR, OUTPUT);
	pinMode(PIN_MAX2_DIR, OUTPUT);
	setSerialDirection(0, IO::Direction::Incoming);
	rs485_0.onSetDirection(setSerialDirection);
	rs485_0.onRequest(handleRS485Request);
	rs485_0.start();

	debug_i("Modbus init OK");

	return true;
}

void initRegisters()
{
	auto set = [&](Register reg, uint16_t value) {
		auto info = getRegInfo(reg);
		registers[info.addr] = value;
	};

	set(Register::RunState, 0x0002);			   // 2
	set(Register::ActiveEnergyToday, 0x0019);	  // 2500 Wh
	set(Register::ReactiveEnergyToday, 0x00fa);	// 25000 VARh
	set(Register::GenEnergyToday, 0x0000);		   // 0 Wh
	set(Register::ActiveEnergyTotal, 0x1a75);	  // 7230900 Wh
	set(Register::PvEnergyMonth, 0x050a);		   // 1290000 Wh
	set(Register::LoadEnergyMonth, 0x0415);		   // 1045000 Wh
	set(Register::GridEnergyMonth, 0x0415);		   // 1045000 Wh
	set(Register::PvEnergyYear, 0x1e00);		   // 768000 Wh
	set(Register::BatChargeToday, 0x0000);		   // 0 Wh
	set(Register::BatDischargeToday, 0x001b);	  // 2700 Wh
	set(Register::BatChargeTotal, 0x0838);		   // 6764000 Wh
	set(Register::BatDischargeTotal, 0xe402);	  // 5837000 Wh
	set(Register::GridImportToday, 0x0000);		   // 0 Wh
	set(Register::GridExportToday, 0x0000);		   // 0 Wh
	set(Register::GridImportTotal, 0xec1a);		   // 6044200 Wh
	set(Register::GridFrequency, 0x0000);		   // 0 Hz
	set(Register::GridExportTotal, 0x0008);		   // 800 Wh
	set(Register::GenDailyOperatingTime, 0x0000);  // 0 s
	set(Register::LoadEnergyToday, 0x0019);		   // 2500 Wh
	set(Register::LoadEnergyTotal, 0x0791);		   // 13300900 Wh
	set(Register::LoadEnergyYear, 0x10f9);		   // 434500 Wh
	set(Register::DcTemp, 0x0580);				   // 40.8 °C
	set(Register::IgbtTemp, 0x04e6);			   // 25.4 °C
	set(Register::Inductance1Temp, 0x8d77);		   // -3032.1 °C
	set(Register::PowerFactor, 0x0001);			   // 0.001
	set(Register::SdStatus, 0x07d0);			   // 2000
	set(Register::EnvironmentTemperature, 0x0000); // -100 °C
	set(Register::PvEnergyTotal, 0x9e4c);		   // 10606000 Wh
	set(Register::PvEnergyToday, 0x0000);		   // 0 Wh
	set(Register::Pv1Voltage, 0x0842);			   // 211.4 V
	set(Register::Pv1Current, 0x0003);			   // 0.3 A
	set(Register::Pv2Voltage, 0x080a);			   // 205.8 V
	set(Register::Pv2Current, 0x0004);			   // 0.4 A
	set(Register::GridVoltage, 0x011d);			   // 28.5 V
	set(Register::InverterVoltage, 0x08fc);		   // 230 V
	set(Register::LoadVoltage, 0x0917);			   // 232.7 V
	set(Register::GridCurrentL1, 0x0038);		   // 0.56 A
	set(Register::GridCurrentL2, 0x0000);		   // 0 A
	set(Register::LimiterCurrentL1, 0x0000);	   // 0 A
	set(Register::LimiterCurrentL2, 0x0000);	   // 0 A
	set(Register::InverterCurrentL1, 0x015e);	  // 3.5 A
	set(Register::AuxPower, 0x0003);			   // 3 W
	set(Register::GridPowerL1, 0x0000);			   // 0 W
	set(Register::GridPowerL2, 0x0000);			   // 0 W
	set(Register::GridPowerTotal, 0x0000);		   // 0 W
	set(Register::LimiterPowerL1, 0x0000);		   // 0 W
	set(Register::LimiterPowerL2, 0x0000);		   // 0 W
	set(Register::LimiterPowerTotal, 0x0000);	  // 0 W
	set(Register::InverterPowerL1, 0x0323);		   // 803 W
	set(Register::InverterPowerL2, 0x0000);		   // 0 W
	set(Register::InverterPowerTotal, 0x0323);	 // 803 W
	set(Register::LoadPowerL1, 0x0323);			   // 803 W
	set(Register::LoadPowerL2, 0x0000);			   // 0 W
	set(Register::LoadPowerTotal, 0x0323);		   // 803 W
	set(Register::LoadCurrentL1, 0x0323);		   // 8.03 A
	set(Register::LoadCurrentL2, 0x0000);		   // 0 A
	set(Register::BatteryTemp, 0x046a);			   // 13 °C
	set(Register::BatteryVoltage, 0x1333);		   // 49.15 V
	set(Register::BatterySOC, 0x0041);			   // 65 %
	set(Register::Pv1Power, 0x0050);			   // 80 W
	set(Register::Pv2Power, 0x0055);			   // 85 W
	set(Register::Pv3Power, 0x0000);			   // 0 W
	set(Register::Pv4Power, 0x0000);			   // 0 W
	set(Register::BatteryPower, 0x0321);		   // 801 W
	set(Register::BatteryCurrent, 0x065e);		   // 16.3 A
	set(Register::LoadFrequency, 0x1388);		   // 50 Hz
	set(Register::InverterFrequency, 0x1388);	  // 50 Hz
	set(Register::GridRelayStatus, 0x0000);		   // 0
	set(Register::AuxRelayStatus, 0x0011);		   // 0x0011
};

} // namespace

void init()
{
	Serial.setPort(COM_PORT_DEBUG);
	Serial.begin(COM_SPEED_SERIAL);
	Serial.systemDebugOutput(true);

	initRegisters();
	initModbus();
}
