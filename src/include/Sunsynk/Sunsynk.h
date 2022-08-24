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
	NONE = 0,
	POWERFACTOR = 1,
	WATT = 2,
	WATTH = 3,
	VARH = 4,
	AMP = 5,
	AMPH = 6,
	VOLT = 7,
	OHM = 8,
	HERTZ = 9,
	CELSIUS = 10,
	PERCENT = 11,
	SECOND = 12,
	HOURS = 13,
	BCDTIME = 14,
	HEXVAL = 15,
};

extern const char* unitSuffixes[];
extern const uint8_t unitSuffixLengths[];

enum class Attr {
	ReadOnly = 0,
	ReadWrite = 1,
	Signed = 2,
	HighWord = 3,
	Virtual = 4,
};

using Attributes = BitSet<uint8_t, Attr, 5>;

enum class Register {
	DeviceType = 0,
	ModbusAddress = 1,
	CommsProtocolVersion = 2,
	SerialNumber0 = 3,
	SerialNumber1 = 4,
	SerialNumber2 = 5,
	SerialNumber3 = 6,
	SerialNumber4 = 7,
	FwVerControl = 8,
	FwVerComms = 9,
	SafetyType = 10,
	RatedPowerLow = 11,
	RatedPowerHigh = 12,
	MpptNoAndPhases = 13,
	RemoteLock = 14,
	SelfCheckTime = 15,
	SysTimeYearMon = 16,
	SysTimeDayHour = 17,
	SysTimeMinSec = 18,
	InsImpedMin = 19,
	DcVoltageMax = 20,
	GridVoltageMax = 21,
	GridVoltageMin = 22,
	GridFreqMax = 23,
	GridFreqLower = 24,
	GridCurrentMax = 25,
	StartingVoltageMax = 26,
	StartingVoltageMin = 27,
	OverFreqDeratePoint = 28,
	OverFreqDeRate = 29,
	InternalTempMax = 30,
	CommsAddr = 31,
	PowerFactorRegulation = 32,
	ActivePowerRegulation = 33,
	ReactivePowerRegulation = 34,
	ApparentPowerRegulation = 35,
	SwitchOnOffEnable = 36,
	FactoryResetEnable = 37,
	SelfCheckingTime = 38,
	IslandProtectionEnable = 39,
	RunState = 40,
	ActiveEnergyToday = 41,
	ReactiveEnergyToday = 42,
	GridWorkTimeToday = 43,
	ActiveEnergyTotal = 44,
	ActiveEnergyTotalHigh = 45,
	PvEnergyMonth = 46,
	LoadEnergyMonth = 47,
	GridEnergyMonth = 48,
	PvEnergyYear = 49,
	PvEnergyYearHigh = 50,
	BatChargeToday = 51,
	BatDischargeToday = 52,
	BatChargeTotal = 53,
	BatChargeTotalHigh = 54,
	BatDischargeTotal = 55,
	BatDischargeTotalHigh = 56,
	GridImportToday = 57,
	GridExportToday = 58,
	GridImportTotal = 59,
	GridFrequency = 60,
	GridImportTotalHigh = 61,
	GridExportTotal = 62,
	GridExportTotalHigh = 63,
	GenDailyOperatingTime = 64,
	LoadEnergyToday = 65,
	LoadEnergyTotal = 66,
	LoadEnergyTotalHigh = 67,
	LoadEnergyYear = 68,
	LoadEnergyYearHigh = 69,
	DcTemp = 70,
	IgbtTemp = 71,
	Inductance1Temp = 72,
	PowerFactor = 73,
	SdStatus = 74,
	EnvironmentTemperature = 75,
	PvEnergyTotal = 76,
	PvEnergyTotalHigh = 77,
	OtherTestFlags = 78,
	Warning1 = 79,
	Warning2 = 80,
	Fault1 = 81,
	Fault2 = 82,
	Fault3 = 83,
	Fault4 = 84,
	CorrectedAh = 85,
	PvEnergyToday = 86,
	Pv1Voltage = 87,
	Pv1Current = 88,
	Pv2Voltage = 89,
	Pv2Current = 90,
	Pv3Voltage = 91,
	Pv3Current = 92,
	Pv4Voltage = 93,
	Pv4Current = 94,
	GridVoltage = 95,
	InverterVoltage = 96,
	LoadVoltage = 97,
	GridCurrentL1 = 98,
	GridCurrentL2 = 99,
	LimiterCurrentL1 = 100,
	LimiterCurrentL2 = 101,
	InverterCurrentL1 = 102,
	InverterCurrentL2 = 103,
	AuxPower = 104,
	GridPowerL1 = 105,
	GridPowerL2 = 106,
	GridPowerTotal = 107,
	LimiterPowerL1 = 108,
	LimiterPowerL2 = 109,
	LimiterPowerTotal = 110,
	InverterPowerL1 = 111,
	InverterPowerL2 = 112,
	InverterPowerTotal = 113,
	LoadPowerL1 = 114,
	LoadPowerL2 = 115,
	LoadPowerTotal = 116,
	LoadCurrentL1 = 117,
	LoadCurrentL2 = 118,
	Undefined181 = 119,
	BatteryTemp = 120,
	BatteryVoltage = 121,
	BatterySOC = 122,
	Undefined185 = 123,
	Pv1Power = 124,
	Pv2Power = 125,
	Pv3Power = 126,
	Pv4Power = 127,
	BatteryPower = 128,
	BatteryCurrent = 129,
	InverterFrequency = 130,
	GridRelayStatus = 131,
	AuxRelayStatus = 132,
	BatteryCapacity = 133,
	BatteryChargeMax = 134,
	BatteryDischargeMax = 135,
	BatteryCapacityShutdown = 136,
	BatteryCapacityRestart = 137,
	BatteryCapacityLow = 138,
	BatteryVoltageShutdown = 139,
	BatteryVoltageRestart = 140,
	BatteryVoltageLow = 141,
	GenOpTimeMax = 142,
	GenCoolingTime = 143,
	GenChargeStartVoltage = 144,
	GenChargeStartCapacity = 145,
	GenChargeCurrent = 146,
	GridChargeStartVoltage = 147,
	GridChargeStartCapacity = 148,
	GridChargeCurrent = 149,
	GenChargeEnable = 150,
	GridChargeEnable = 151,
	SolarInputAsPsu = 152,
	GenForceAsLoad = 153,
	GenInputMode = 154,
	SmartLoadOffVoltage = 155,
	SmartLoadOffCapacity = 156,
	SmartLoadOnVoltage = 157,
	SmartLoadOnCapacity = 158,
	GenStartMinSolar = 159,
	GenGridSignalOn = 160,
	LoadPriorityEnable = 161,
	LimitControlFunction = 162,
	GridPowerMax = 163,
	CurrentSensorPhase = 164,
	SolarSellEnable = 165,
	TimeOfUseSelling = 166,
	Prog1Time = 167,
	Prog2Time = 168,
	Prog3Time = 169,
	Prog4Time = 170,
	Prog5Time = 171,
	Prog6Time = 172,
	Prog1Power = 173,
	Prog2Power = 174,
	Prog3Power = 175,
	Prog4Power = 176,
	Prog5Power = 177,
	Prog6Power = 178,
	Prog1Voltage = 179,
	Prog2Voltage = 180,
	Prog3Voltage = 181,
	Prog4Voltage = 182,
	Prog5Voltage = 183,
	Prog6Voltage = 184,
	Prog1Capacity = 185,
	Prog2Capacity = 186,
	Prog3Capacity = 187,
	Prog4Capacity = 188,
	Prog5Capacity = 189,
	Prog6Capacity = 190,
	Prog1Charge = 191,
	Prog2Charge = 192,
	Prog3Charge = 193,
	Prog4Charge = 194,
	Prog5Charge = 195,
	Prog6Charge = 196,
	MicroinverterExportToGridCutoff = 197,
	RestoreConnectionTime = 198,
	ArcFaultMode = 199,
	GridMode = 200,
	GridFrequencySelect = 201,
	GridType = 202,
	GridVoltageHigh = 203,
	GridVoltageLow = 204,
	GridFreqHigh = 205,
	GridFreqLow = 206,
	GenGridInput = 207,
	GenPeakShavingPower = 208,
	GridPeakShavingPower = 209,
	SmartLoadOpenDelay = 210,
	OutputPfValue = 211,
	Efficiency = 212,
};

constexpr size_t registerCount = 213;

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
