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
	NONE,
	POWERFACTOR,
	WATT,
	WATTH,
	VARH,
	AMP,
	AMPH,
	VOLT,
	OHM,
	HERTZ,
	CELSIUS,
	PERCENT,
	SECOND,
	HOURS,
	BCDTIME,
	HEXVAL,

};

extern const char* unitSuffixes[];
extern const uint8_t unitSuffixLengths[];

enum class Attr {
	ReadOnly,
	ReadWrite,
	Signed,
	HighWord,
	Virtual,

};

using Attributes = BitSet<uint8_t, Attr, 5>;

enum class Register {
	DeviceType,
	ModbusAddress,
	CommsProtocolVersion,
	SerialNumber0,
	SerialNumber1,
	SerialNumber2,
	SerialNumber3,
	SerialNumber4,
	FwVerControl,
	FwVerComms,
	SafetyType,
	RatedPowerLow,
	RatedPowerHigh,
	MpptNoAndPhases,
	RemoteLock,
	SelfCheckTime,
	SysTimeYearMon,
	SysTimeDayHour,
	SysTimeMinSec,
	InsImpedMin,
	DcVoltageMax,
	GridVoltageMax,
	GridVoltageMin,
	GridFreqMax,
	GridFreqLower,
	GridCurrentMax,
	StartingVoltageMax,
	StartingVoltageMin,
	OverFreqDeratePoint,
	OverFreqDeRate,
	InternalTempMax,
	CommsAddr,
	PowerFactorRegulation,
	ActivePowerRegulation,
	ReactivePowerRegulation,
	ApparentPowerRegulation,
	SwitchOnOffEnable,
	FactoryResetEnable,
	SelfCheckingTime,
	IslandProtectionEnable,
	RunState,
	ActiveEnergyToday,
	ReactiveEnergyToday,
	GridWorkTimeToday,
	ActiveEnergyTotal,
	ActiveEnergyTotalHigh,
	PvEnergyMonth,
	LoadEnergyMonth,
	GridEnergyMonth,
	PvEnergyYear,
	PvEnergyYearHigh,
	BatChargeToday,
	BatDischargeToday,
	BatChargeTotal,
	BatChargeTotalHigh,
	BatDischargeTotal,
	BatDischargeTotalHigh,
	GridImportToday,
	GridExportToday,
	GridImportTotal,
	GridFrequency,
	GridImportTotalHigh,
	GridExportTotal,
	GridExportTotalHigh,
	GenDailyOperatingTime,
	LoadEnergyToday,
	LoadEnergyTotal,
	LoadEnergyTotalHigh,
	LoadEnergyYear,
	LoadEnergyYearHigh,
	DcTemp,
	IgbtTemp,
	Inductance1Temp,
	PowerFactor,
	SdStatus,
	EnvironmentTemperature,
	PvEnergyTotal,
	PvEnergyTotalHigh,
	OtherTestFlags,
	Warning1,
	Warning2,
	Fault1,
	Fault2,
	Fault3,
	Fault4,
	CorrectedAh,
	PvEnergyToday,
	Pv1Voltage,
	Pv1Current,
	Pv2Voltage,
	Pv2Current,
	Pv3Voltage,
	Pv3Current,
	Pv4Voltage,
	Pv4Current,
	GridVoltage,
	InverterVoltage,
	LoadVoltage,
	GridCurrentL1,
	GridCurrentL2,
	LimiterCurrentL1,
	LimiterCurrentL2,
	InverterCurrentL1,
	InverterCurrentL2,
	AuxPower,
	GridPowerL1,
	GridPowerL2,
	GridPowerTotal,
	LimiterPowerL1,
	LimiterPowerL2,
	LimiterPowerTotal,
	InverterPowerL1,
	InverterPowerL2,
	InverterPowerTotal,
	LoadPowerL1,
	LoadPowerL2,
	LoadPowerTotal,
	LoadCurrentL1,
	LoadCurrentL2,
	Undefined181,
	BatteryTemp,
	BatteryVoltage,
	BatterySOC,
	Undefined185,
	PvPower1,
	PvPower2,
	PvPower3,
	PvPower4,
	BatteryPower,
	BatteryCurrent,
	InverterFrequency,
	GridRelayStatus,
	AuxRelayStatus,
	BatteryCapacity,
	BatteryChargeMax,
	BatteryDischargeMax,
	BatteryCapacityShutdown,
	BatteryCapacityRestart,
	BatteryCapacityLow,
	BatteryVoltageShutdown,
	BatteryVoltageRestart,
	BatteryVoltageLow,
	GenOpTimeMax,
	GenCoolingTime,
	GenChargeStartVoltage,
	GenChargeStartCapacity,
	GenChargeCurrent,
	GridChargeStartVoltage,
	GridChargeStartCapacity,
	GridChargeCurrent,
	GenChargeEnable,
	GridChargeEnable,
	SolarInputAsPsu,
	GenForceAsLoad,
	GenInputMode,
	SmartLoadOffVoltage,
	SmartLoadOffCapacity,
	SmartLoadOnVoltage,
	SmartLoadOnCapacity,
	GenStartMinSolar,
	GenGridSignalOn,
	LoadPriorityEnable,
	LimitControlFunction,
	GridPowerMax,
	CurrentSensorPhase,
	SolarSellEnable,
	TimeOfUseSelling,
	Prog1Time,
	Prog2Time,
	Prog3Time,
	Prog4Time,
	Prog5Time,
	Prog6Time,
	Prog1Power,
	Prog2Power,
	Prog3Power,
	Prog4Power,
	Prog5Power,
	Prog6Power,
	Prog1Voltage,
	Prog2Voltage,
	Prog3Voltage,
	Prog4Voltage,
	Prog5Voltage,
	Prog6Voltage,
	Prog1Capacity,
	Prog2Capacity,
	Prog3Capacity,
	Prog4Capacity,
	Prog5Capacity,
	Prog6Capacity,
	Prog1Charge,
	Prog2Charge,
	Prog3Charge,
	Prog4Charge,
	Prog5Charge,
	Prog6Charge,
	MicroinverterExportToGridCutoff,
	RestoreConnectionTime,
	ArcFaultMode,
	GridMode,
	GridFrequencySelect,
	GridType,
	GridVoltageHigh,
	GridVoltageLow,
	GridFreqHigh,
	GridFreqLow,
	GenGridInput,
	GenPeakShavingPower,
	GridPeakShavingPower,
	SmartLoadOpenDelay,
	OutputPfValue,
	Efficiency,

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
