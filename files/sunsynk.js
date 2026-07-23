/*
 * sunsynk.js
 *
 * GENERATED FILE: DO NOT EDIT
 *
 */
"use strict";

// Unit enumeration
const Unit = Object.freeze({
	NONE: 0,
	POWERFACTOR: 1,
	WATT: 2,
	WATTH: 3,
	VARH: 4,
	AMP: 5,
	AMPH: 6,
	VOLT: 7,
	OHM: 8,
	HERTZ: 9,
	CELSIUS: 10,
	PERCENT: 11,
	SECOND: 12,
	HOURS: 13,
	BCDTIME: 14,
	HEXVAL: 15,
	ASCII: 16,
	YEARMON: 17,
	DAYHOUR: 18,
	MINSEC: 19,
});

const unitSuffixes = Object.freeze(["", "", "W", "Wh", "VARh", "A", "Ah", "V", "R", "Hz", "°C", "%", "s", "h", "", "", "", "", "", ""]);
const unitSuffixLengths = Object.freeze([0, 0, 1, 2, 4, 1, 2, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0]);

const Attr = Object.freeze({
	ReadOnly: 0,
	ReadWrite: 1,
	Signed: 2,
	LowWord: 3,
	HighWord: 4,
	Virtual: 5,
});

const SCALE_0_0001 = -4;
const SCALE_0_001 = -3;
const SCALE_0_01 = -2;
const SCALE_0_1 = -1;
const SCALE_NONE = 0;
const SCALE_10 = 1;
const SCALE_100 = 2;
const SCALE_1000 = 3;

class RegDef {
	constructor(name, addr, unit, scale = SCALE_NONE, attr = [Attr.ReadOnly]) {
		this.name = name;
		this.addr = addr;
		this.unit = unit;
		this.scale = scale;
		this.attr = new Set(attr);
	}

	getIntValue(data) {
		let value = data[this.addr];
		if (this.attr.has(Attr.LowWord)) {
			let highWord = data[this.reg2.addr];
			return (highWord << 16) | value;
		}
		if (this.attr.has(Attr.HighWord)) {
			let lowWord = data[this.reg2.addr];
			return (value << 16) | lowWord;
		}
		if (this.attr.has(Attr.Signed) && value >= 0x8000) {
			value -= 0x10000;
		}
		return value;
	}

	intToFloat(value) {
		value *= Math.pow(10, this.scale);
		if (this.unit == Unit.CELSIUS) {
			value -= 100;
		}
		if (this.scale < 0) {
			value = +(value.toFixed(-this.scale));
		}
		return value;
	}

	intToString(value) {
		const num2 = function (v) {
			return v.toString().padStart(2, '0');
		};
		const chr = function (v) {
			return String.fromCharCode(v);
		};

		switch (this.unit) {
			case Unit.BCDTIME: {
				let hour = Math.trunc(value / 100);
				let min = value % 100;
				return num2(hour) + ':' + num2(min);
			}
			case Unit.HEXVAL:
				return `0x${hex(value)}`;
			case Unit.ASCII:
				return chr(value >> 8) + chr(value & 0xff);
			case Unit.YEARMON:
				let year = 2000 + (value >> 8)
				let month = value & 0xff
				return year + ', ' + num2(month);
			case Unit.DAYHOUR: {
				let day = value >> 8;
				let hour = value & 0xff;
				return day + ', ' + num2(hour);
			}
			case Unit.MINSEC: {
				let min = value >> 8;
				let sec = value & 0xff;
				return num2(min) + ', ' + num2(sec);
			}
		}

		let s = this.intToFloat(value).toString();
		let suffix = unitSuffixes[this.unit];
		if (suffix) {
			s += ' ' + suffix;
		}
		return s;
	}
};

const SunsynkRegister = Object.freeze({
	DeviceType: new RegDef("DeviceType", 0, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	ModbusAddress: new RegDef("ModbusAddress", 1, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	CommsProtocolVersion: new RegDef("CommsProtocolVersion", 2, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	SerialNumber0: new RegDef("SerialNumber0", 3, Unit.ASCII, 0, [Attr.ReadOnly]),
	SerialNumber1: new RegDef("SerialNumber1", 4, Unit.ASCII, 0, [Attr.ReadOnly]),
	SerialNumber2: new RegDef("SerialNumber2", 5, Unit.ASCII, 0, [Attr.ReadOnly]),
	SerialNumber3: new RegDef("SerialNumber3", 6, Unit.ASCII, 0, [Attr.ReadOnly]),
	SerialNumber4: new RegDef("SerialNumber4", 7, Unit.ASCII, 0, [Attr.ReadOnly]),
	FwVerControl: new RegDef("FwVerControl", 13, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	FwVerComms: new RegDef("FwVerComms", 14, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	SafetyType: new RegDef("SafetyType", 15, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	RatedPower: new RegDef("RatedPower", 16, Unit.WATT, -1, [Attr.ReadOnly, Attr.LowWord]),
	RatedPowerHigh: new RegDef("RatedPowerHigh", 17, Unit.WATT, -1, [Attr.ReadOnly, Attr.HighWord]),
	MpptNoAndPhases: new RegDef("MpptNoAndPhases", 18, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	RemoteLock: new RegDef("RemoteLock", 20, Unit.HEXVAL, 0, [Attr.ReadWrite]),
	SelfCheckTime: new RegDef("SelfCheckTime", 21, Unit.SECOND, 0, [Attr.ReadWrite]),
	SysTimeYearMon: new RegDef("SysTimeYearMon", 22, Unit.YEARMON, 0, [Attr.ReadWrite]),
	SysTimeDayHour: new RegDef("SysTimeDayHour", 23, Unit.DAYHOUR, 0, [Attr.ReadWrite]),
	SysTimeMinSec: new RegDef("SysTimeMinSec", 24, Unit.MINSEC, 0, [Attr.ReadWrite]),
	InsImpedMin: new RegDef("InsImpedMin", 25, Unit.OHM, 2, [Attr.ReadWrite]),
	DcVoltageMax: new RegDef("DcVoltageMax", 26, Unit.VOLT, -1, [Attr.ReadWrite]),
	GridVoltageMax: new RegDef("GridVoltageMax", 27, Unit.VOLT, -1, [Attr.ReadWrite]),
	GridVoltageMin: new RegDef("GridVoltageMin", 28, Unit.VOLT, -1, [Attr.ReadWrite]),
	GridFreqMax: new RegDef("GridFreqMax", 29, Unit.HERTZ, -2, [Attr.ReadWrite]),
	GridFreqLower: new RegDef("GridFreqLower", 30, Unit.HERTZ, -2, [Attr.ReadWrite]),
	GridCurrentMax: new RegDef("GridCurrentMax", 31, Unit.AMP, -1, [Attr.ReadWrite]),
	StartingVoltageMax: new RegDef("StartingVoltageMax", 32, Unit.VOLT, -1, [Attr.ReadWrite]),
	StartingVoltageMin: new RegDef("StartingVoltageMin", 33, Unit.VOLT, -1, [Attr.ReadWrite]),
	OverFreqDeratePoint: new RegDef("OverFreqDeratePoint", 34, Unit.HERTZ, -2, [Attr.ReadWrite]),
	OverFreqDeRate: new RegDef("OverFreqDeRate", 35, Unit.NONE, 0, [Attr.ReadWrite]),
	InternalTempMax: new RegDef("InternalTempMax", 36, Unit.NONE, -1, [Attr.ReadWrite, Attr.Signed]),
	CommsAddr: new RegDef("CommsAddr", 37, Unit.NONE, 0, [Attr.ReadOnly]),
	PowerFactorRegulation: new RegDef("PowerFactorRegulation", 39, Unit.POWERFACTOR, -3, [Attr.ReadWrite]),
	ActivePowerRegulation: new RegDef("ActivePowerRegulation", 40, Unit.PERCENT, -1, [Attr.ReadWrite]),
	ReactivePowerRegulation: new RegDef("ReactivePowerRegulation", 41, Unit.PERCENT, -1, [Attr.ReadWrite]),
	ApparentPowerRegulation: new RegDef("ApparentPowerRegulation", 42, Unit.PERCENT, -1, [Attr.ReadWrite]),
	SwitchOnOffEnable: new RegDef("SwitchOnOffEnable", 43, Unit.NONE, 0, [Attr.ReadWrite]),
	FactoryResetEnable: new RegDef("FactoryResetEnable", 44, Unit.NONE, 0, [Attr.ReadWrite]),
	SelfCheckingTime: new RegDef("SelfCheckingTime", 45, Unit.NONE, 0, [Attr.ReadWrite]),
	IslandProtectionEnable: new RegDef("IslandProtectionEnable", 46, Unit.NONE, 0, [Attr.ReadWrite]),
	MaxSolarPower: new RegDef("MaxSolarPower", 53, Unit.WATT, 0, [Attr.ReadOnly]),
	RunState: new RegDef("RunState", 59, Unit.NONE, 0, [Attr.ReadWrite]),
	ActiveEnergyToday: new RegDef("ActiveEnergyToday", 60, Unit.WATTH, 2, [Attr.ReadOnly, Attr.Signed]),
	ReactiveEnergyToday: new RegDef("ReactiveEnergyToday", 61, Unit.VARH, 2, [Attr.ReadOnly, Attr.Signed]),
	GenEnergyToday: new RegDef("GenEnergyToday", 62, Unit.WATTH, 2, [Attr.ReadOnly]),
	ActiveEnergyTotal: new RegDef("ActiveEnergyTotal", 63, Unit.WATTH, 2, [Attr.ReadOnly, Attr.Signed, Attr.LowWord]),
	ActiveEnergyTotalHigh: new RegDef("ActiveEnergyTotalHigh", 64, Unit.WATTH, 2, [Attr.ReadOnly, Attr.Signed, Attr.HighWord]),
	PvEnergyMonth: new RegDef("PvEnergyMonth", 65, Unit.WATTH, 3, [Attr.ReadOnly]),
	LoadEnergyMonth: new RegDef("LoadEnergyMonth", 66, Unit.WATTH, 3, [Attr.ReadOnly]),
	GridEnergyMonth: new RegDef("GridEnergyMonth", 67, Unit.WATTH, 3, [Attr.ReadOnly]),
	PvEnergyYear: new RegDef("PvEnergyYear", 68, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	PvEnergyYearHigh: new RegDef("PvEnergyYearHigh", 69, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	BatChargeToday: new RegDef("BatChargeToday", 70, Unit.WATTH, 2, [Attr.ReadOnly]),
	BatDischargeToday: new RegDef("BatDischargeToday", 71, Unit.WATTH, 2, [Attr.ReadOnly]),
	BatChargeTotal: new RegDef("BatChargeTotal", 72, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	BatChargeTotalHigh: new RegDef("BatChargeTotalHigh", 73, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	BatDischargeTotal: new RegDef("BatDischargeTotal", 74, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	BatDischargeTotalHigh: new RegDef("BatDischargeTotalHigh", 75, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	GridImportToday: new RegDef("GridImportToday", 76, Unit.WATTH, 2, [Attr.ReadOnly]),
	GridExportToday: new RegDef("GridExportToday", 77, Unit.WATTH, 2, [Attr.ReadOnly]),
	GridImportTotal: new RegDef("GridImportTotal", 78, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	GridFrequency: new RegDef("GridFrequency", 79, Unit.HERTZ, -2, [Attr.ReadOnly]),
	GridImportTotalHigh: new RegDef("GridImportTotalHigh", 80, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	GridExportTotal: new RegDef("GridExportTotal", 81, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	GridExportTotalHigh: new RegDef("GridExportTotalHigh", 82, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	GenDailyOperatingTime: new RegDef("GenDailyOperatingTime", 83, Unit.SECOND, -1, [Attr.ReadOnly]),
	LoadEnergyToday: new RegDef("LoadEnergyToday", 84, Unit.WATTH, 2, [Attr.ReadOnly]),
	LoadEnergyTotal: new RegDef("LoadEnergyTotal", 85, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	LoadEnergyTotalHigh: new RegDef("LoadEnergyTotalHigh", 86, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	LoadEnergyYear: new RegDef("LoadEnergyYear", 87, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	LoadEnergyYearHigh: new RegDef("LoadEnergyYearHigh", 88, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	DcTemp: new RegDef("DcTemp", 90, Unit.CELSIUS, -1, [Attr.ReadOnly, Attr.Signed]),
	IgbtTemp: new RegDef("IgbtTemp", 91, Unit.CELSIUS, -1, [Attr.ReadOnly, Attr.Signed]),
	Inductance1Temp: new RegDef("Inductance1Temp", 92, Unit.CELSIUS, -1, [Attr.ReadOnly, Attr.Signed]),
	PowerFactor: new RegDef("PowerFactor", 93, Unit.POWERFACTOR, -3, [Attr.ReadOnly]),
	SdStatus: new RegDef("SdStatus", 94, Unit.NONE, 0, [Attr.ReadOnly]),
	EnvironmentTemperature: new RegDef("EnvironmentTemperature", 95, Unit.CELSIUS, -1, [Attr.ReadOnly, Attr.Signed]),
	PvEnergyTotal: new RegDef("PvEnergyTotal", 96, Unit.WATTH, 2, [Attr.ReadOnly, Attr.LowWord]),
	PvEnergyTotalHigh: new RegDef("PvEnergyTotalHigh", 97, Unit.WATTH, 2, [Attr.ReadOnly, Attr.HighWord]),
	OtherTestFlags: new RegDef("OtherTestFlags", 100, Unit.NONE, 0, [Attr.ReadOnly]),
	Warning1: new RegDef("Warning1", 101, Unit.NONE, 0, [Attr.ReadOnly]),
	Warning2: new RegDef("Warning2", 102, Unit.NONE, 0, [Attr.ReadOnly]),
	Fault1: new RegDef("Fault1", 103, Unit.NONE, 0, [Attr.ReadOnly]),
	Fault2: new RegDef("Fault2", 104, Unit.NONE, 0, [Attr.ReadOnly]),
	Fault3: new RegDef("Fault3", 105, Unit.NONE, 0, [Attr.ReadOnly]),
	Fault4: new RegDef("Fault4", 106, Unit.NONE, 0, [Attr.ReadOnly]),
	CorrectedAh: new RegDef("CorrectedAh", 107, Unit.AMPH, 0, [Attr.ReadOnly]),
	PvEnergyToday: new RegDef("PvEnergyToday", 108, Unit.WATTH, 2, [Attr.ReadOnly]),
	Pv1Voltage: new RegDef("Pv1Voltage", 109, Unit.VOLT, -1, [Attr.ReadOnly]),
	Pv1Current: new RegDef("Pv1Current", 110, Unit.AMP, -1, [Attr.ReadOnly]),
	Pv2Voltage: new RegDef("Pv2Voltage", 111, Unit.VOLT, -1, [Attr.ReadOnly]),
	Pv2Current: new RegDef("Pv2Current", 112, Unit.AMP, -1, [Attr.ReadOnly]),
	Pv3Voltage: new RegDef("Pv3Voltage", 113, Unit.VOLT, -1, [Attr.ReadOnly]),
	Pv3Current: new RegDef("Pv3Current", 114, Unit.AMP, -1, [Attr.ReadOnly]),
	Pv4Voltage: new RegDef("Pv4Voltage", 115, Unit.VOLT, -1, [Attr.ReadOnly]),
	Pv4Current: new RegDef("Pv4Current", 116, Unit.AMP, -1, [Attr.ReadOnly]),
	GridVoltage: new RegDef("GridVoltage", 150, Unit.VOLT, -1, [Attr.ReadOnly]),
	InverterVoltage: new RegDef("InverterVoltage", 154, Unit.VOLT, -1, [Attr.ReadOnly]),
	LoadVoltage: new RegDef("LoadVoltage", 157, Unit.VOLT, -1, [Attr.ReadOnly]),
	GridCurrentL1: new RegDef("GridCurrentL1", 160, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	GridCurrentL2: new RegDef("GridCurrentL2", 161, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	LimiterCurrentL1: new RegDef("LimiterCurrentL1", 162, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	LimiterCurrentL2: new RegDef("LimiterCurrentL2", 163, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	InverterCurrentL1: new RegDef("InverterCurrentL1", 164, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	InverterCurrentL2: new RegDef("InverterCurrentL2", 165, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	AuxPower: new RegDef("AuxPower", 166, Unit.WATT, 0, [Attr.ReadOnly]),
	GridPowerL1: new RegDef("GridPowerL1", 167, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	GridPowerL2: new RegDef("GridPowerL2", 168, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	GridPowerTotal: new RegDef("GridPowerTotal", 169, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LimiterPowerL1: new RegDef("LimiterPowerL1", 170, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LimiterPowerL2: new RegDef("LimiterPowerL2", 171, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LimiterPowerTotal: new RegDef("LimiterPowerTotal", 172, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	InverterPowerL1: new RegDef("InverterPowerL1", 173, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	InverterPowerL2: new RegDef("InverterPowerL2", 174, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	InverterPowerTotal: new RegDef("InverterPowerTotal", 175, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LoadPowerL1: new RegDef("LoadPowerL1", 176, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LoadPowerL2: new RegDef("LoadPowerL2", 177, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LoadPowerTotal: new RegDef("LoadPowerTotal", 178, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	LoadCurrentL1: new RegDef("LoadCurrentL1", 179, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	LoadCurrentL2: new RegDef("LoadCurrentL2", 180, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	Undefined181: new RegDef("Undefined181", 181, Unit.NONE, 0, [Attr.ReadOnly]),
	BatteryTemp: new RegDef("BatteryTemp", 182, Unit.CELSIUS, -1, [Attr.ReadOnly, Attr.Signed]),
	BatteryVoltage: new RegDef("BatteryVoltage", 183, Unit.VOLT, -2, [Attr.ReadOnly]),
	BatterySOC: new RegDef("BatterySOC", 184, Unit.PERCENT, 0, [Attr.ReadOnly]),
	Pv1Power: new RegDef("Pv1Power", 186, Unit.WATT, 0, [Attr.ReadOnly]),
	Pv2Power: new RegDef("Pv2Power", 187, Unit.WATT, 0, [Attr.ReadOnly]),
	Pv3Power: new RegDef("Pv3Power", 188, Unit.WATT, 0, [Attr.ReadOnly]),
	Pv4Power: new RegDef("Pv4Power", 189, Unit.WATT, 0, [Attr.ReadOnly]),
	BatteryPower: new RegDef("BatteryPower", 190, Unit.WATT, 0, [Attr.ReadOnly, Attr.Signed]),
	BatteryCurrent: new RegDef("BatteryCurrent", 191, Unit.AMP, -2, [Attr.ReadOnly, Attr.Signed]),
	LoadFrequency: new RegDef("LoadFrequency", 192, Unit.HERTZ, -2, [Attr.ReadOnly]),
	InverterFrequency: new RegDef("InverterFrequency", 193, Unit.HERTZ, -2, [Attr.ReadOnly]),
	GridRelayStatus: new RegDef("GridRelayStatus", 194, Unit.NONE, 0, [Attr.ReadOnly]),
	AuxRelayStatus: new RegDef("AuxRelayStatus", 195, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	GeneratorFrequency: new RegDef("GeneratorFrequency", 196, Unit.HERTZ, -2, [Attr.ReadOnly]),
	BatteryControlMode: new RegDef("BatteryControlMode", 200, Unit.NONE, 0, [Attr.ReadOnly]),
	BatteryEqualizationVoltage: new RegDef("BatteryEqualizationVoltage", 201, Unit.VOLT, -2, [Attr.ReadWrite]),
	BatteryAbsorptionVoltage: new RegDef("BatteryAbsorptionVoltage", 202, Unit.VOLT, -2, [Attr.ReadWrite]),
	BatteryFloatVoltage: new RegDef("BatteryFloatVoltage", 203, Unit.VOLT, -2, [Attr.ReadWrite]),
	BatteryCapacity: new RegDef("BatteryCapacity", 204, Unit.AMPH, 0, [Attr.ReadWrite]),
	BatteryEmptyVoltage: new RegDef("BatteryEmptyVoltage", 205, Unit.VOLT, -2, [Attr.ReadWrite]),
	ZeroExportPowerLimit: new RegDef("ZeroExportPowerLimit", 206, Unit.WATT, 0, [Attr.ReadWrite]),
	BatteryEqualizationDayCycle: new RegDef("BatteryEqualizationDayCycle", 207, Unit.NONE, 0, [Attr.ReadWrite]),
	BatteryEqualizationTime: new RegDef("BatteryEqualizationTime", 208, Unit.NONE, 0, [Attr.ReadWrite]),
	BatteryTempCo: new RegDef("BatteryTempCo", 209, Unit.NONE, 0, [Attr.ReadWrite, Attr.Signed]),
	BatteryChargeMax: new RegDef("BatteryChargeMax", 210, Unit.AMP, 0, [Attr.ReadWrite]),
	BatteryDischargeMax: new RegDef("BatteryDischargeMax", 211, Unit.AMP, 0, [Attr.ReadWrite]),
	BatteryVoltOrCapacity: new RegDef("BatteryVoltOrCapacity", 213, Unit.NONE, 0, [Attr.ReadWrite]),
	BatteryLithiumWakeupSignBit: new RegDef("BatteryLithiumWakeupSignBit", 214, Unit.NONE, 0, [Attr.ReadWrite]),
	BatteryResistance: new RegDef("BatteryResistance", 215, Unit.OHM, -4, [Attr.ReadWrite]),
	BatteryChargingEfficiency: new RegDef("BatteryChargingEfficiency", 216, Unit.PERCENT, -1, [Attr.ReadWrite]),
	BatteryCapacityShutdown: new RegDef("BatteryCapacityShutdown", 217, Unit.PERCENT, 0, [Attr.ReadWrite]),
	BatteryCapacityRestart: new RegDef("BatteryCapacityRestart", 218, Unit.PERCENT, 0, [Attr.ReadWrite]),
	BatteryCapacityLow: new RegDef("BatteryCapacityLow", 219, Unit.PERCENT, 0, [Attr.ReadWrite]),
	BatteryVoltageShutdown: new RegDef("BatteryVoltageShutdown", 220, Unit.VOLT, -2, [Attr.ReadWrite]),
	BatteryVoltageRestart: new RegDef("BatteryVoltageRestart", 221, Unit.VOLT, -2, [Attr.ReadWrite]),
	BatteryVoltageLow: new RegDef("BatteryVoltageLow", 222, Unit.VOLT, -2, [Attr.ReadWrite]),
	GenOpTimeMax: new RegDef("GenOpTimeMax", 223, Unit.HOURS, -1, [Attr.ReadWrite]),
	GenCoolingTime: new RegDef("GenCoolingTime", 224, Unit.HOURS, -1, [Attr.ReadWrite]),
	GenChargeStartVoltage: new RegDef("GenChargeStartVoltage", 225, Unit.VOLT, -2, [Attr.ReadWrite]),
	GenChargeStartCapacity: new RegDef("GenChargeStartCapacity", 226, Unit.PERCENT, 0, [Attr.ReadWrite]),
	GenChargeCurrent: new RegDef("GenChargeCurrent", 227, Unit.AMP, 0, [Attr.ReadWrite]),
	GridChargeStartVoltage: new RegDef("GridChargeStartVoltage", 228, Unit.VOLT, -2, [Attr.ReadWrite]),
	GridChargeStartCapacity: new RegDef("GridChargeStartCapacity", 229, Unit.PERCENT, 0, [Attr.ReadWrite]),
	GridChargeCurrent: new RegDef("GridChargeCurrent", 230, Unit.AMP, 0, [Attr.ReadWrite]),
	GenChargeEnable: new RegDef("GenChargeEnable", 231, Unit.NONE, 0, [Attr.ReadWrite]),
	GridChargeEnable: new RegDef("GridChargeEnable", 232, Unit.NONE, 0, [Attr.ReadWrite]),
	SolarInputAsPsu: new RegDef("SolarInputAsPsu", 233, Unit.NONE, 0, [Attr.ReadWrite]),
	GenForceAsLoad: new RegDef("GenForceAsLoad", 234, Unit.NONE, 0, [Attr.ReadWrite]),
	GenInputMode: new RegDef("GenInputMode", 235, Unit.NONE, 0, [Attr.ReadWrite]),
	SmartLoadOffVoltage: new RegDef("SmartLoadOffVoltage", 236, Unit.VOLT, -2, [Attr.ReadWrite]),
	SmartLoadOffCapacity: new RegDef("SmartLoadOffCapacity", 237, Unit.PERCENT, 0, [Attr.ReadWrite]),
	SmartLoadOnVoltage: new RegDef("SmartLoadOnVoltage", 238, Unit.VOLT, -2, [Attr.ReadWrite]),
	SmartLoadOnCapacity: new RegDef("SmartLoadOnCapacity", 239, Unit.PERCENT, 0, [Attr.ReadWrite]),
	GenStartMinSolar: new RegDef("GenStartMinSolar", 241, Unit.WATT, 0, [Attr.ReadWrite]),
	GenGridSignalOn: new RegDef("GenGridSignalOn", 242, Unit.NONE, 0, [Attr.ReadWrite]),
	LoadPriorityEnable: new RegDef("LoadPriorityEnable", 243, Unit.NONE, 0, [Attr.ReadWrite]),
	LimitControlFunction: new RegDef("LimitControlFunction", 244, Unit.NONE, 0, [Attr.ReadWrite]),
	GridPowerMax: new RegDef("GridPowerMax", 245, Unit.WATT, 0, [Attr.ReadWrite]),
	CurrentSensorPhase: new RegDef("CurrentSensorPhase", 246, Unit.NONE, 0, [Attr.ReadWrite]),
	SolarSellEnable: new RegDef("SolarSellEnable", 247, Unit.NONE, 0, [Attr.ReadWrite]),
	TimeOfUseSelling: new RegDef("TimeOfUseSelling", 248, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog1Time: new RegDef("Prog1Time", 250, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog2Time: new RegDef("Prog2Time", 251, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog3Time: new RegDef("Prog3Time", 252, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog4Time: new RegDef("Prog4Time", 253, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog5Time: new RegDef("Prog5Time", 254, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog6Time: new RegDef("Prog6Time", 255, Unit.BCDTIME, 0, [Attr.ReadWrite]),
	Prog1Power: new RegDef("Prog1Power", 256, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog2Power: new RegDef("Prog2Power", 257, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog3Power: new RegDef("Prog3Power", 258, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog4Power: new RegDef("Prog4Power", 259, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog5Power: new RegDef("Prog5Power", 260, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog6Power: new RegDef("Prog6Power", 261, Unit.WATT, 0, [Attr.ReadWrite]),
	Prog1Voltage: new RegDef("Prog1Voltage", 262, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog2Voltage: new RegDef("Prog2Voltage", 263, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog3Voltage: new RegDef("Prog3Voltage", 264, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog4Voltage: new RegDef("Prog4Voltage", 265, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog5Voltage: new RegDef("Prog5Voltage", 266, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog6Voltage: new RegDef("Prog6Voltage", 267, Unit.VOLT, -2, [Attr.ReadWrite]),
	Prog1Capacity: new RegDef("Prog1Capacity", 268, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog2Capacity: new RegDef("Prog2Capacity", 269, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog3Capacity: new RegDef("Prog3Capacity", 270, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog4Capacity: new RegDef("Prog4Capacity", 271, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog5Capacity: new RegDef("Prog5Capacity", 272, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog6Capacity: new RegDef("Prog6Capacity", 273, Unit.PERCENT, 0, [Attr.ReadWrite]),
	Prog1Charge: new RegDef("Prog1Charge", 274, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog2Charge: new RegDef("Prog2Charge", 275, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog3Charge: new RegDef("Prog3Charge", 276, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog4Charge: new RegDef("Prog4Charge", 277, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog5Charge: new RegDef("Prog5Charge", 278, Unit.NONE, 0, [Attr.ReadWrite]),
	Prog6Charge: new RegDef("Prog6Charge", 279, Unit.NONE, 0, [Attr.ReadWrite]),
	MicroinverterExportToGridCutoff: new RegDef("MicroinverterExportToGridCutoff", 280, Unit.HEXVAL, 0, [Attr.ReadWrite]),
	RestoreConnectionTime: new RegDef("RestoreConnectionTime", 282, Unit.SECOND, 0, [Attr.ReadWrite]),
	ArcFaultMode: new RegDef("ArcFaultMode", 283, Unit.NONE, 0, [Attr.ReadWrite]),
	GridMode: new RegDef("GridMode", 284, Unit.NONE, 0, [Attr.ReadWrite]),
	GridFrequencySelect: new RegDef("GridFrequencySelect", 285, Unit.NONE, 0, [Attr.ReadWrite]),
	GridType: new RegDef("GridType", 286, Unit.NONE, 0, [Attr.ReadWrite]),
	GridVoltageHigh: new RegDef("GridVoltageHigh", 287, Unit.VOLT, -1, [Attr.ReadWrite]),
	GridVoltageLow: new RegDef("GridVoltageLow", 288, Unit.VOLT, -1, [Attr.ReadWrite]),
	GridFreqHigh: new RegDef("GridFreqHigh", 289, Unit.HERTZ, -2, [Attr.ReadWrite]),
	GridFreqLow: new RegDef("GridFreqLow", 290, Unit.HERTZ, -2, [Attr.ReadWrite]),
	GenGridInput: new RegDef("GenGridInput", 291, Unit.NONE, 0, [Attr.ReadWrite]),
	GenPeakShavingPower: new RegDef("GenPeakShavingPower", 292, Unit.WATT, 0, [Attr.ReadWrite]),
	GridPeakShavingPower: new RegDef("GridPeakShavingPower", 293, Unit.WATT, 0, [Attr.ReadWrite]),
	SmartLoadOpenDelay: new RegDef("SmartLoadOpenDelay", 294, Unit.SECOND, 0, [Attr.ReadWrite]),
	OutputPfValue: new RegDef("OutputPfValue", 295, Unit.PERCENT, -1, [Attr.ReadWrite]),
	ExtRelayBit: new RegDef("ExtRelayBit", 296, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	ChargingVoltage: new RegDef("ChargingVoltage", 312, Unit.VOLT, -2, [Attr.ReadOnly]),
	DischargeVoltage: new RegDef("DischargeVoltage", 313, Unit.VOLT, -2, [Attr.ReadOnly]),
	ChargingCurrentLimiting: new RegDef("ChargingCurrentLimiting", 314, Unit.AMP, 0, [Attr.ReadOnly]),
	DischargeCurrentLimiting: new RegDef("DischargeCurrentLimiting", 315, Unit.AMP, 0, [Attr.ReadOnly]),
	RealTimeCapacity: new RegDef("RealTimeCapacity", 316, Unit.PERCENT, 0, [Attr.ReadOnly]),
	RealTimeVoltage: new RegDef("RealTimeVoltage", 317, Unit.VOLT, -2, [Attr.ReadOnly]),
	RealTimeCurrent: new RegDef("RealTimeCurrent", 318, Unit.AMP, 0, [Attr.ReadOnly, Attr.Signed]),
	RealTimeTemp: new RegDef("RealTimeTemp", 319, Unit.CELSIUS, -1, [Attr.ReadOnly]),
	MaxChargeCurrentLimit: new RegDef("MaxChargeCurrentLimit", 320, Unit.AMP, 0, [Attr.ReadOnly]),
	MaxDischargeCurrentLimit: new RegDef("MaxDischargeCurrentLimit", 321, Unit.AMP, 0, [Attr.ReadOnly]),
	LithiumBatteryAlarm: new RegDef("LithiumBatteryAlarm", 322, Unit.NONE, 0, [Attr.ReadOnly]),
	LithiumBatteryFaultLocation: new RegDef("LithiumBatteryFaultLocation", 323, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	LithiumBatterySymbol2: new RegDef("LithiumBatterySymbol2", 324, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	LithiumBatteryType: new RegDef("LithiumBatteryType", 325, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	Ex_MeterCT: new RegDef("Ex_MeterCT", 326, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	CT_Ratio: new RegDef("CT_Ratio", 327, Unit.NONE, 0, [Attr.ReadOnly]),
	SpecialFunctionBits: new RegDef("SpecialFunctionBits", 328, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	AC_CoupleFrequencyUpperLimit: new RegDef("AC_CoupleFrequencyUpperLimit", 329, Unit.HERTZ, -2, [Attr.ReadOnly]),
	CommBoardSettingFunction: new RegDef("CommBoardSettingFunction", 330, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	Solar1WindEnable: new RegDef("Solar1WindEnable", 390, Unit.NONE, 0, [Attr.ReadWrite]),
	Solar2WindEnable: new RegDef("Solar2WindEnable", 391, Unit.NONE, 0, [Attr.ReadWrite]),
	WindVoltage1: new RegDef("WindVoltage1", 392, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage2: new RegDef("WindVoltage2", 393, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage3: new RegDef("WindVoltage3", 394, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage4: new RegDef("WindVoltage4", 395, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage5: new RegDef("WindVoltage5", 396, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage6: new RegDef("WindVoltage6", 397, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage7: new RegDef("WindVoltage7", 398, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage8: new RegDef("WindVoltage8", 399, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage9: new RegDef("WindVoltage9", 400, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage10: new RegDef("WindVoltage10", 401, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage11: new RegDef("WindVoltage11", 402, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindVoltage12: new RegDef("WindVoltage12", 403, Unit.VOLT, -1, [Attr.ReadWrite]),
	WindCurrent1: new RegDef("WindCurrent1", 404, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent2: new RegDef("WindCurrent2", 405, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent3: new RegDef("WindCurrent3", 406, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent4: new RegDef("WindCurrent4", 407, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent5: new RegDef("WindCurrent5", 408, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent6: new RegDef("WindCurrent6", 409, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent7: new RegDef("WindCurrent7", 410, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent8: new RegDef("WindCurrent8", 411, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent9: new RegDef("WindCurrent9", 412, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent10: new RegDef("WindCurrent10", 413, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent11: new RegDef("WindCurrent11", 414, Unit.AMP, -1, [Attr.ReadWrite]),
	WindCurrent12: new RegDef("WindCurrent12", 415, Unit.AMP, -1, [Attr.ReadWrite]),
	ForcedOffGridOperation: new RegDef("ForcedOffGridOperation", 416, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	ParallelRegister1: new RegDef("ParallelRegister1", 417, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	ParallelRegister2: new RegDef("ParallelRegister2", 418, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	LithiumBatteryVersionLow: new RegDef("LithiumBatteryVersionLow", 419, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	LithiumBatteryVersionHigh: new RegDef("LithiumBatteryVersionHigh", 420, Unit.HEXVAL, 0, [Attr.ReadOnly]),
	SyncTimeYearMon: new RegDef("SyncTimeYearMon", 421, Unit.YEARMON, 0, [Attr.ReadWrite]),
	SyncTimeDayHour: new RegDef("SyncTimeDayHour", 422, Unit.DAYHOUR, 0, [Attr.ReadWrite]),
	SyncTimeMinSec: new RegDef("SyncTimeMinSec", 423, Unit.MINSEC, 0, [Attr.ReadWrite]),
	Efficiency: new RegDef("Efficiency", 65535, Unit.PERCENT, -1, [Attr.ReadOnly, Attr.Virtual]),
	PvPowerTotal: new RegDef("PvPowerTotal", 65535, Unit.WATT, 0, [Attr.ReadOnly, Attr.Virtual]),
	AuxEnergyToday: new RegDef("AuxEnergyToday", 65535, Unit.WATTH, 2, [Attr.ReadOnly, Attr.Virtual]),

});

class SunsynkRegisterMap {
	constructor() {
		for (let r of Object.values(SunsynkRegister)) {
			if (r.attr.has(Attr.LowWord)) {
				r.reg2 = SunsynkRegister[r.name + 'High'];
			} else if (r.attr.has(Attr.HighWord)) {
				r.reg2 = SunsynkRegister[r.name.slice(0, -4)];
			}
			this[r.addr] = r;
		}
	}
};

const sunsynkRegisterMap = new SunsynkRegisterMap();
