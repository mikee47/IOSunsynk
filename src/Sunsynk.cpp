
/*
 * Sunsynk code
 *
 * GENERATED FILE: DO NOT EDIT
 *
 */

#include "include/Sunsynk/Sunsynk.h"
#include <FlashString/Array.hpp>

// clang-format off

namespace IO::Modbus::Sunsynk
{
const char* unitSuffixes[]{"", "", "W", "Wh", "VARh", "A", "Ah", "V", "R", "Hz", "°C", "%", "s", "h", "", ""};

const uint8_t unitSuffixLengths[]{0, 0, 1, 2, 4, 1, 2, 1, 1, 2, 2, 1, 1, 1, 0, 0};

namespace RegName
{
DEFINE_FSTR(DeviceType, "DeviceType")
DEFINE_FSTR(ModbusAddress, "ModbusAddress")
DEFINE_FSTR(CommsProtocolVersion, "CommsProtocolVersion")
DEFINE_FSTR(SerialNumber0, "SerialNumber0")
DEFINE_FSTR(SerialNumber1, "SerialNumber1")
DEFINE_FSTR(SerialNumber2, "SerialNumber2")
DEFINE_FSTR(SerialNumber3, "SerialNumber3")
DEFINE_FSTR(SerialNumber4, "SerialNumber4")
DEFINE_FSTR(FwVerControl, "FwVerControl")
DEFINE_FSTR(FwVerComms, "FwVerComms")
DEFINE_FSTR(SafetyType, "SafetyType")
DEFINE_FSTR(RatedPowerLow, "RatedPowerLow")
DEFINE_FSTR(RatedPowerHigh, "RatedPowerHigh")
DEFINE_FSTR(MpptNoAndPhases, "MpptNoAndPhases")
DEFINE_FSTR(RemoteLock, "RemoteLock")
DEFINE_FSTR(SelfCheckTime, "SelfCheckTime")
DEFINE_FSTR(SysTimeYearMon, "SysTimeYearMon")
DEFINE_FSTR(SysTimeDayHour, "SysTimeDayHour")
DEFINE_FSTR(SysTimeMinSec, "SysTimeMinSec")
DEFINE_FSTR(InsImpedMin, "InsImpedMin")
DEFINE_FSTR(DcVoltageMax, "DcVoltageMax")
DEFINE_FSTR(GridVoltageMax, "GridVoltageMax")
DEFINE_FSTR(GridVoltageMin, "GridVoltageMin")
DEFINE_FSTR(GridFreqMax, "GridFreqMax")
DEFINE_FSTR(GridFreqLower, "GridFreqLower")
DEFINE_FSTR(GridCurrentMax, "GridCurrentMax")
DEFINE_FSTR(StartingVoltageMax, "StartingVoltageMax")
DEFINE_FSTR(StartingVoltageMin, "StartingVoltageMin")
DEFINE_FSTR(OverFreqDeratePoint, "OverFreqDeratePoint")
DEFINE_FSTR(OverFreqDeRate, "OverFreqDeRate")
DEFINE_FSTR(InternalTempMax, "InternalTempMax")
DEFINE_FSTR(CommsAddr, "CommsAddr")
DEFINE_FSTR(PowerFactorRegulation, "PowerFactorRegulation")
DEFINE_FSTR(ActivePowerRegulation, "ActivePowerRegulation")
DEFINE_FSTR(ReactivePowerRegulation, "ReactivePowerRegulation")
DEFINE_FSTR(ApparentPowerRegulation, "ApparentPowerRegulation")
DEFINE_FSTR(SwitchOnOffEnable, "SwitchOnOffEnable")
DEFINE_FSTR(FactoryResetEnable, "FactoryResetEnable")
DEFINE_FSTR(SelfCheckingTime, "SelfCheckingTime")
DEFINE_FSTR(IslandProtectionEnable, "IslandProtectionEnable")
DEFINE_FSTR(RunState, "RunState")
DEFINE_FSTR(ActiveEnergyToday, "ActiveEnergyToday")
DEFINE_FSTR(ReactiveEnergyToday, "ReactiveEnergyToday")
DEFINE_FSTR(GridWorkTimeToday, "GridWorkTimeToday")
DEFINE_FSTR(ActiveEnergyTotal, "ActiveEnergyTotal")
DEFINE_FSTR(ActiveEnergyTotalHigh, "ActiveEnergyTotalHigh")
DEFINE_FSTR(PvEnergyMonth, "PvEnergyMonth")
DEFINE_FSTR(LoadEnergyMonth, "LoadEnergyMonth")
DEFINE_FSTR(GridEnergyMonth, "GridEnergyMonth")
DEFINE_FSTR(PvEnergyYear, "PvEnergyYear")
DEFINE_FSTR(PvEnergyYearHigh, "PvEnergyYearHigh")
DEFINE_FSTR(BatChargeToday, "BatChargeToday")
DEFINE_FSTR(BatDischargeToday, "BatDischargeToday")
DEFINE_FSTR(BatChargeTotal, "BatChargeTotal")
DEFINE_FSTR(BatChargeTotalHigh, "BatChargeTotalHigh")
DEFINE_FSTR(BatDischargeTotal, "BatDischargeTotal")
DEFINE_FSTR(BatDischargeTotalHigh, "BatDischargeTotalHigh")
DEFINE_FSTR(GridImportToday, "GridImportToday")
DEFINE_FSTR(GridExportToday, "GridExportToday")
DEFINE_FSTR(GridImportTotal, "GridImportTotal")
DEFINE_FSTR(GridFrequency, "GridFrequency")
DEFINE_FSTR(GridImportTotalHigh, "GridImportTotalHigh")
DEFINE_FSTR(GridExportTotal, "GridExportTotal")
DEFINE_FSTR(GridExportTotalHigh, "GridExportTotalHigh")
DEFINE_FSTR(GenDailyOperatingTime, "GenDailyOperatingTime")
DEFINE_FSTR(LoadEnergyToday, "LoadEnergyToday")
DEFINE_FSTR(LoadEnergyTotal, "LoadEnergyTotal")
DEFINE_FSTR(LoadEnergyTotalHigh, "LoadEnergyTotalHigh")
DEFINE_FSTR(LoadEnergyYear, "LoadEnergyYear")
DEFINE_FSTR(LoadEnergyYearHigh, "LoadEnergyYearHigh")
DEFINE_FSTR(DcTemp, "DcTemp")
DEFINE_FSTR(IgbtTemp, "IgbtTemp")
DEFINE_FSTR(Inductance1Temp, "Inductance1Temp")
DEFINE_FSTR(PowerFactor, "PowerFactor")
DEFINE_FSTR(SdStatus, "SdStatus")
DEFINE_FSTR(EnvironmentTemperature, "EnvironmentTemperature")
DEFINE_FSTR(PvEnergyTotal, "PvEnergyTotal")
DEFINE_FSTR(PvEnergyTotalHigh, "PvEnergyTotalHigh")
DEFINE_FSTR(OtherTestFlags, "OtherTestFlags")
DEFINE_FSTR(Warning1, "Warning1")
DEFINE_FSTR(Warning2, "Warning2")
DEFINE_FSTR(Fault1, "Fault1")
DEFINE_FSTR(Fault2, "Fault2")
DEFINE_FSTR(Fault3, "Fault3")
DEFINE_FSTR(Fault4, "Fault4")
DEFINE_FSTR(CorrectedAh, "CorrectedAh")
DEFINE_FSTR(PvEnergyToday, "PvEnergyToday")
DEFINE_FSTR(Pv1Voltage, "Pv1Voltage")
DEFINE_FSTR(Pv1Current, "Pv1Current")
DEFINE_FSTR(Pv2Voltage, "Pv2Voltage")
DEFINE_FSTR(Pv2Current, "Pv2Current")
DEFINE_FSTR(Pv3Voltage, "Pv3Voltage")
DEFINE_FSTR(Pv3Current, "Pv3Current")
DEFINE_FSTR(Pv4Voltage, "Pv4Voltage")
DEFINE_FSTR(Pv4Current, "Pv4Current")
DEFINE_FSTR(GridVoltage, "GridVoltage")
DEFINE_FSTR(InverterVoltage, "InverterVoltage")
DEFINE_FSTR(LoadVoltage, "LoadVoltage")
DEFINE_FSTR(GridCurrentL1, "GridCurrentL1")
DEFINE_FSTR(GridCurrentL2, "GridCurrentL2")
DEFINE_FSTR(LimiterCurrentL1, "LimiterCurrentL1")
DEFINE_FSTR(LimiterCurrentL2, "LimiterCurrentL2")
DEFINE_FSTR(InverterCurrentL1, "InverterCurrentL1")
DEFINE_FSTR(InverterCurrentL2, "InverterCurrentL2")
DEFINE_FSTR(AuxPower, "AuxPower")
DEFINE_FSTR(GridPowerL1, "GridPowerL1")
DEFINE_FSTR(GridPowerL2, "GridPowerL2")
DEFINE_FSTR(GridPowerTotal, "GridPowerTotal")
DEFINE_FSTR(LimiterPowerL1, "LimiterPowerL1")
DEFINE_FSTR(LimiterPowerL2, "LimiterPowerL2")
DEFINE_FSTR(LimiterPowerTotal, "LimiterPowerTotal")
DEFINE_FSTR(InverterPowerL1, "InverterPowerL1")
DEFINE_FSTR(InverterPowerL2, "InverterPowerL2")
DEFINE_FSTR(InverterPowerTotal, "InverterPowerTotal")
DEFINE_FSTR(LoadPowerL1, "LoadPowerL1")
DEFINE_FSTR(LoadPowerL2, "LoadPowerL2")
DEFINE_FSTR(LoadPowerTotal, "LoadPowerTotal")
DEFINE_FSTR(LoadCurrentL1, "LoadCurrentL1")
DEFINE_FSTR(LoadCurrentL2, "LoadCurrentL2")
DEFINE_FSTR(Undefined181, "Undefined181")
DEFINE_FSTR(BatteryTemp, "BatteryTemp")
DEFINE_FSTR(BatteryVoltage, "BatteryVoltage")
DEFINE_FSTR(BatterySOC, "BatterySOC")
DEFINE_FSTR(Undefined185, "Undefined185")
DEFINE_FSTR(PvPower1, "PvPower1")
DEFINE_FSTR(PvPower2, "PvPower2")
DEFINE_FSTR(PvPower3, "PvPower3")
DEFINE_FSTR(PvPower4, "PvPower4")
DEFINE_FSTR(BatteryPower, "BatteryPower")
DEFINE_FSTR(BatteryCurrent, "BatteryCurrent")
DEFINE_FSTR(InverterFrequency, "InverterFrequency")
DEFINE_FSTR(GridRelayStatus, "GridRelayStatus")
DEFINE_FSTR(AuxRelayStatus, "AuxRelayStatus")
DEFINE_FSTR(BatteryCapacity, "BatteryCapacity")
DEFINE_FSTR(BatteryChargeMax, "BatteryChargeMax")
DEFINE_FSTR(BatteryDischargeMax, "BatteryDischargeMax")
DEFINE_FSTR(BatteryCapacityShutdown, "BatteryCapacityShutdown")
DEFINE_FSTR(BatteryCapacityRestart, "BatteryCapacityRestart")
DEFINE_FSTR(BatteryCapacityLow, "BatteryCapacityLow")
DEFINE_FSTR(BatteryVoltageShutdown, "BatteryVoltageShutdown")
DEFINE_FSTR(BatteryVoltageRestart, "BatteryVoltageRestart")
DEFINE_FSTR(BatteryVoltageLow, "BatteryVoltageLow")
DEFINE_FSTR(GenOpTimeMax, "GenOpTimeMax")
DEFINE_FSTR(GenCoolingTime, "GenCoolingTime")
DEFINE_FSTR(GenChargeStartVoltage, "GenChargeStartVoltage")
DEFINE_FSTR(GenChargeStartCapacity, "GenChargeStartCapacity")
DEFINE_FSTR(GenChargeCurrent, "GenChargeCurrent")
DEFINE_FSTR(GridChargeStartVoltage, "GridChargeStartVoltage")
DEFINE_FSTR(GridChargeStartCapacity, "GridChargeStartCapacity")
DEFINE_FSTR(GridChargeCurrent, "GridChargeCurrent")
DEFINE_FSTR(GenChargeEnable, "GenChargeEnable")
DEFINE_FSTR(GridChargeEnable, "GridChargeEnable")
DEFINE_FSTR(SolarInputAsPsu, "SolarInputAsPsu")
DEFINE_FSTR(GenForceAsLoad, "GenForceAsLoad")
DEFINE_FSTR(GenInputMode, "GenInputMode")
DEFINE_FSTR(SmartLoadOffVoltage, "SmartLoadOffVoltage")
DEFINE_FSTR(SmartLoadOffCapacity, "SmartLoadOffCapacity")
DEFINE_FSTR(SmartLoadOnVoltage, "SmartLoadOnVoltage")
DEFINE_FSTR(SmartLoadOnCapacity, "SmartLoadOnCapacity")
DEFINE_FSTR(GenStartMinSolar, "GenStartMinSolar")
DEFINE_FSTR(GenGridSignalOn, "GenGridSignalOn")
DEFINE_FSTR(LoadPriorityEnable, "LoadPriorityEnable")
DEFINE_FSTR(LimitControlFunction, "LimitControlFunction")
DEFINE_FSTR(GridPowerMax, "GridPowerMax")
DEFINE_FSTR(CurrentSensorPhase, "CurrentSensorPhase")
DEFINE_FSTR(SolarSellEnable, "SolarSellEnable")
DEFINE_FSTR(TimeOfUseSelling, "TimeOfUseSelling")
DEFINE_FSTR(Prog1Time, "Prog1Time")
DEFINE_FSTR(Prog2Time, "Prog2Time")
DEFINE_FSTR(Prog3Time, "Prog3Time")
DEFINE_FSTR(Prog4Time, "Prog4Time")
DEFINE_FSTR(Prog5Time, "Prog5Time")
DEFINE_FSTR(Prog6Time, "Prog6Time")
DEFINE_FSTR(Prog1Power, "Prog1Power")
DEFINE_FSTR(Prog2Power, "Prog2Power")
DEFINE_FSTR(Prog3Power, "Prog3Power")
DEFINE_FSTR(Prog4Power, "Prog4Power")
DEFINE_FSTR(Prog5Power, "Prog5Power")
DEFINE_FSTR(Prog6Power, "Prog6Power")
DEFINE_FSTR(Prog1Voltage, "Prog1Voltage")
DEFINE_FSTR(Prog2Voltage, "Prog2Voltage")
DEFINE_FSTR(Prog3Voltage, "Prog3Voltage")
DEFINE_FSTR(Prog4Voltage, "Prog4Voltage")
DEFINE_FSTR(Prog5Voltage, "Prog5Voltage")
DEFINE_FSTR(Prog6Voltage, "Prog6Voltage")
DEFINE_FSTR(Prog1Capacity, "Prog1Capacity")
DEFINE_FSTR(Prog2Capacity, "Prog2Capacity")
DEFINE_FSTR(Prog3Capacity, "Prog3Capacity")
DEFINE_FSTR(Prog4Capacity, "Prog4Capacity")
DEFINE_FSTR(Prog5Capacity, "Prog5Capacity")
DEFINE_FSTR(Prog6Capacity, "Prog6Capacity")
DEFINE_FSTR(Prog1Charge, "Prog1Charge")
DEFINE_FSTR(Prog2Charge, "Prog2Charge")
DEFINE_FSTR(Prog3Charge, "Prog3Charge")
DEFINE_FSTR(Prog4Charge, "Prog4Charge")
DEFINE_FSTR(Prog5Charge, "Prog5Charge")
DEFINE_FSTR(Prog6Charge, "Prog6Charge")
DEFINE_FSTR(MicroinverterExportToGridCutoff, "MicroinverterExportToGridCutoff")
DEFINE_FSTR(RestoreConnectionTime, "RestoreConnectionTime")
DEFINE_FSTR(ArcFaultMode, "ArcFaultMode")
DEFINE_FSTR(GridMode, "GridMode")
DEFINE_FSTR(GridFrequencySelect, "GridFrequencySelect")
DEFINE_FSTR(GridType, "GridType")
DEFINE_FSTR(GridVoltageHigh, "GridVoltageHigh")
DEFINE_FSTR(GridVoltageLow, "GridVoltageLow")
DEFINE_FSTR(GridFreqHigh, "GridFreqHigh")
DEFINE_FSTR(GridFreqLow, "GridFreqLow")
DEFINE_FSTR(GenGridInput, "GenGridInput")
DEFINE_FSTR(GenPeakShavingPower, "GenPeakShavingPower")
DEFINE_FSTR(GridPeakShavingPower, "GridPeakShavingPower")
DEFINE_FSTR(SmartLoadOpenDelay, "SmartLoadOpenDelay")
DEFINE_FSTR(OutputPfValue, "OutputPfValue")
DEFINE_FSTR(Efficiency, "Efficiency")
} // namespace RegName

DEFINE_FSTR_ARRAY(regInfo, RegInfo,
	{&RegName::DeviceType, 0, Unit::HEXVAL, 0, 0x01}, // DeviceType
	{&RegName::ModbusAddress, 1, Unit::HEXVAL, 0, 0x01}, // ModbusAddress
	{&RegName::CommsProtocolVersion, 2, Unit::HEXVAL, 0, 0x01}, // CommsProtocolVersion
	{&RegName::SerialNumber0, 3, Unit::HEXVAL, 0, 0x01}, // SerialNumber0
	{&RegName::SerialNumber1, 4, Unit::HEXVAL, 0, 0x01}, // SerialNumber1
	{&RegName::SerialNumber2, 5, Unit::HEXVAL, 0, 0x01}, // SerialNumber2
	{&RegName::SerialNumber3, 6, Unit::HEXVAL, 0, 0x01}, // SerialNumber3
	{&RegName::SerialNumber4, 7, Unit::HEXVAL, 0, 0x01}, // SerialNumber4
	{&RegName::FwVerControl, 13, Unit::HEXVAL, 0, 0x01}, // FwVerControl
	{&RegName::FwVerComms, 14, Unit::HEXVAL, 0, 0x01}, // FwVerComms
	{&RegName::SafetyType, 15, Unit::HEXVAL, 0, 0x01}, // SafetyType
	{&RegName::RatedPowerLow, 16, Unit::WATT, 1, 0x01}, // RatedPowerLow
	{&RegName::RatedPowerHigh, 17, Unit::WATT, 1, 0x09}, // RatedPowerHigh
	{&RegName::MpptNoAndPhases, 18, Unit::HEXVAL, 0, 0x01}, // MpptNoAndPhases
	{&RegName::RemoteLock, 20, Unit::HEXVAL, 0, 0x02}, // RemoteLock
	{&RegName::SelfCheckTime, 21, Unit::SECOND, 0, 0x02}, // SelfCheckTime
	{&RegName::SysTimeYearMon, 22, Unit::HEXVAL, 0, 0x02}, // SysTimeYearMon
	{&RegName::SysTimeDayHour, 23, Unit::HEXVAL, 0, 0x02}, // SysTimeDayHour
	{&RegName::SysTimeMinSec, 24, Unit::HEXVAL, 0, 0x02}, // SysTimeMinSec
	{&RegName::InsImpedMin, 25, Unit::OHM, 2, 0x02}, // InsImpedMin
	{&RegName::DcVoltageMax, 26, Unit::VOLT, -1, 0x02}, // DcVoltageMax
	{&RegName::GridVoltageMax, 27, Unit::VOLT, -1, 0x02}, // GridVoltageMax
	{&RegName::GridVoltageMin, 28, Unit::VOLT, -1, 0x02}, // GridVoltageMin
	{&RegName::GridFreqMax, 29, Unit::HERTZ, -2, 0x02}, // GridFreqMax
	{&RegName::GridFreqLower, 30, Unit::HERTZ, -2, 0x02}, // GridFreqLower
	{&RegName::GridCurrentMax, 31, Unit::AMP, -1, 0x02}, // GridCurrentMax
	{&RegName::StartingVoltageMax, 32, Unit::VOLT, -1, 0x02}, // StartingVoltageMax
	{&RegName::StartingVoltageMin, 33, Unit::VOLT, -1, 0x02}, // StartingVoltageMin
	{&RegName::OverFreqDeratePoint, 34, Unit::HERTZ, -2, 0x02}, // OverFreqDeratePoint
	{&RegName::OverFreqDeRate, 35, Unit::NONE, 0, 0x02}, // OverFreqDeRate
	{&RegName::InternalTempMax, 36, Unit::CELSIUS, -1, 0x06}, // InternalTempMax
	{&RegName::CommsAddr, 37, Unit::NONE, 0, 0x01}, // CommsAddr
	{&RegName::PowerFactorRegulation, 39, Unit::POWERFACTOR, -3, 0x02}, // PowerFactorRegulation
	{&RegName::ActivePowerRegulation, 40, Unit::PERCENT, -1, 0x02}, // ActivePowerRegulation
	{&RegName::ReactivePowerRegulation, 41, Unit::PERCENT, -1, 0x02}, // ReactivePowerRegulation
	{&RegName::ApparentPowerRegulation, 42, Unit::PERCENT, -1, 0x02}, // ApparentPowerRegulation
	{&RegName::SwitchOnOffEnable, 43, Unit::NONE, 0, 0x02}, // SwitchOnOffEnable
	{&RegName::FactoryResetEnable, 44, Unit::NONE, 0, 0x02}, // FactoryResetEnable
	{&RegName::SelfCheckingTime, 45, Unit::NONE, 0, 0x02}, // SelfCheckingTime
	{&RegName::IslandProtectionEnable, 46, Unit::NONE, 0, 0x02}, // IslandProtectionEnable
	{&RegName::RunState, 59, Unit::NONE, 0, 0x02}, // RunState
	{&RegName::ActiveEnergyToday, 60, Unit::WATTH, 2, 0x01}, // ActiveEnergyToday
	{&RegName::ReactiveEnergyToday, 61, Unit::VARH, 2, 0x01}, // ReactiveEnergyToday
	{&RegName::GridWorkTimeToday, 62, Unit::SECOND, 0, 0x01}, // GridWorkTimeToday
	{&RegName::ActiveEnergyTotal, 63, Unit::WATTH, 2, 0x01}, // ActiveEnergyTotal
	{&RegName::ActiveEnergyTotalHigh, 64, Unit::WATTH, 2, 0x09}, // ActiveEnergyTotalHigh
	{&RegName::PvEnergyMonth, 65, Unit::WATTH, 3, 0x01}, // PvEnergyMonth
	{&RegName::LoadEnergyMonth, 66, Unit::WATTH, 3, 0x01}, // LoadEnergyMonth
	{&RegName::GridEnergyMonth, 67, Unit::WATTH, 3, 0x01}, // GridEnergyMonth
	{&RegName::PvEnergyYear, 68, Unit::WATTH, 2, 0x01}, // PvEnergyYear
	{&RegName::PvEnergyYearHigh, 69, Unit::WATTH, 2, 0x09}, // PvEnergyYearHigh
	{&RegName::BatChargeToday, 70, Unit::WATTH, 2, 0x01}, // BatChargeToday
	{&RegName::BatDischargeToday, 71, Unit::WATTH, 2, 0x01}, // BatDischargeToday
	{&RegName::BatChargeTotal, 72, Unit::WATTH, 2, 0x01}, // BatChargeTotal
	{&RegName::BatChargeTotalHigh, 73, Unit::WATTH, 2, 0x09}, // BatChargeTotalHigh
	{&RegName::BatDischargeTotal, 74, Unit::WATTH, 2, 0x01}, // BatDischargeTotal
	{&RegName::BatDischargeTotalHigh, 75, Unit::WATTH, 2, 0x09}, // BatDischargeTotalHigh
	{&RegName::GridImportToday, 76, Unit::WATTH, 2, 0x01}, // GridImportToday
	{&RegName::GridExportToday, 77, Unit::WATTH, 2, 0x01}, // GridExportToday
	{&RegName::GridImportTotal, 78, Unit::WATTH, 2, 0x01}, // GridImportTotal
	{&RegName::GridFrequency, 79, Unit::HERTZ, -2, 0x01}, // GridFrequency
	{&RegName::GridImportTotalHigh, 80, Unit::WATTH, 2, 0x09}, // GridImportTotalHigh
	{&RegName::GridExportTotal, 81, Unit::WATTH, 2, 0x01}, // GridExportTotal
	{&RegName::GridExportTotalHigh, 82, Unit::WATTH, 2, 0x09}, // GridExportTotalHigh
	{&RegName::GenDailyOperatingTime, 83, Unit::SECOND, -1, 0x01}, // GenDailyOperatingTime
	{&RegName::LoadEnergyToday, 84, Unit::WATTH, 2, 0x01}, // LoadEnergyToday
	{&RegName::LoadEnergyTotal, 85, Unit::WATTH, 2, 0x01}, // LoadEnergyTotal
	{&RegName::LoadEnergyTotalHigh, 86, Unit::WATTH, 2, 0x09}, // LoadEnergyTotalHigh
	{&RegName::LoadEnergyYear, 87, Unit::WATTH, 2, 0x01}, // LoadEnergyYear
	{&RegName::LoadEnergyYearHigh, 88, Unit::WATTH, 2, 0x09}, // LoadEnergyYearHigh
	{&RegName::DcTemp, 90, Unit::CELSIUS, -1, 0x05}, // DcTemp
	{&RegName::IgbtTemp, 91, Unit::CELSIUS, -1, 0x05}, // IgbtTemp
	{&RegName::Inductance1Temp, 92, Unit::CELSIUS, -1, 0x05}, // Inductance1Temp
	{&RegName::PowerFactor, 93, Unit::POWERFACTOR, -3, 0x01}, // PowerFactor
	{&RegName::SdStatus, 94, Unit::NONE, 0, 0x01}, // SdStatus
	{&RegName::EnvironmentTemperature, 95, Unit::CELSIUS, -1, 0x05}, // EnvironmentTemperature
	{&RegName::PvEnergyTotal, 96, Unit::WATTH, 2, 0x01}, // PvEnergyTotal
	{&RegName::PvEnergyTotalHigh, 97, Unit::WATTH, 2, 0x09}, // PvEnergyTotalHigh
	{&RegName::OtherTestFlags, 100, Unit::NONE, 0, 0x01}, // OtherTestFlags
	{&RegName::Warning1, 101, Unit::NONE, 0, 0x01}, // Warning1
	{&RegName::Warning2, 102, Unit::NONE, 0, 0x01}, // Warning2
	{&RegName::Fault1, 103, Unit::NONE, 0, 0x01}, // Fault1
	{&RegName::Fault2, 104, Unit::NONE, 0, 0x01}, // Fault2
	{&RegName::Fault3, 105, Unit::NONE, 0, 0x01}, // Fault3
	{&RegName::Fault4, 106, Unit::NONE, 0, 0x01}, // Fault4
	{&RegName::CorrectedAh, 107, Unit::AMPH, 0, 0x01}, // CorrectedAh
	{&RegName::PvEnergyToday, 108, Unit::WATTH, 2, 0x01}, // PvEnergyToday
	{&RegName::Pv1Voltage, 109, Unit::VOLT, -1, 0x01}, // Pv1Voltage
	{&RegName::Pv1Current, 110, Unit::AMP, -1, 0x01}, // Pv1Current
	{&RegName::Pv2Voltage, 111, Unit::VOLT, -1, 0x01}, // Pv2Voltage
	{&RegName::Pv2Current, 112, Unit::AMP, -1, 0x01}, // Pv2Current
	{&RegName::Pv3Voltage, 113, Unit::VOLT, -1, 0x01}, // Pv3Voltage
	{&RegName::Pv3Current, 114, Unit::AMP, -1, 0x01}, // Pv3Current
	{&RegName::Pv4Voltage, 115, Unit::VOLT, -1, 0x01}, // Pv4Voltage
	{&RegName::Pv4Current, 116, Unit::AMP, -1, 0x01}, // Pv4Current
	{&RegName::GridVoltage, 150, Unit::VOLT, -1, 0x01}, // GridVoltage
	{&RegName::InverterVoltage, 154, Unit::VOLT, -1, 0x01}, // InverterVoltage
	{&RegName::LoadVoltage, 157, Unit::VOLT, -1, 0x01}, // LoadVoltage
	{&RegName::GridCurrentL1, 160, Unit::AMP, -2, 0x05}, // GridCurrentL1
	{&RegName::GridCurrentL2, 161, Unit::AMP, -2, 0x05}, // GridCurrentL2
	{&RegName::LimiterCurrentL1, 162, Unit::AMP, -2, 0x05}, // LimiterCurrentL1
	{&RegName::LimiterCurrentL2, 163, Unit::AMP, -2, 0x05}, // LimiterCurrentL2
	{&RegName::InverterCurrentL1, 164, Unit::AMP, -2, 0x05}, // InverterCurrentL1
	{&RegName::InverterCurrentL2, 165, Unit::AMP, -2, 0x05}, // InverterCurrentL2
	{&RegName::AuxPower, 166, Unit::WATT, 0, 0x01}, // AuxPower
	{&RegName::GridPowerL1, 167, Unit::WATT, 0, 0x05}, // GridPowerL1
	{&RegName::GridPowerL2, 168, Unit::WATT, 0, 0x05}, // GridPowerL2
	{&RegName::GridPowerTotal, 169, Unit::WATT, 0, 0x05}, // GridPowerTotal
	{&RegName::LimiterPowerL1, 170, Unit::WATT, 0, 0x05}, // LimiterPowerL1
	{&RegName::LimiterPowerL2, 171, Unit::WATT, 0, 0x05}, // LimiterPowerL2
	{&RegName::LimiterPowerTotal, 172, Unit::WATT, 0, 0x05}, // LimiterPowerTotal
	{&RegName::InverterPowerL1, 173, Unit::WATT, 0, 0x05}, // InverterPowerL1
	{&RegName::InverterPowerL2, 174, Unit::WATT, 0, 0x05}, // InverterPowerL2
	{&RegName::InverterPowerTotal, 175, Unit::WATT, 0, 0x05}, // InverterPowerTotal
	{&RegName::LoadPowerL1, 176, Unit::WATT, 0, 0x05}, // LoadPowerL1
	{&RegName::LoadPowerL2, 177, Unit::WATT, 0, 0x05}, // LoadPowerL2
	{&RegName::LoadPowerTotal, 178, Unit::WATT, 0, 0x05}, // LoadPowerTotal
	{&RegName::LoadCurrentL1, 179, Unit::AMP, -2, 0x05}, // LoadCurrentL1
	{&RegName::LoadCurrentL2, 180, Unit::AMP, -2, 0x05}, // LoadCurrentL2
	{&RegName::Undefined181, 181, Unit::NONE, 0, 0x01}, // Undefined181
	{&RegName::BatteryTemp, 182, Unit::CELSIUS, -1, 0x05}, // BatteryTemp
	{&RegName::BatteryVoltage, 183, Unit::VOLT, -2, 0x01}, // BatteryVoltage
	{&RegName::BatterySOC, 184, Unit::PERCENT, 0, 0x01}, // BatterySOC
	{&RegName::Undefined185, 185, Unit::NONE, 0, 0x01}, // Undefined185
	{&RegName::PvPower1, 186, Unit::WATT, 0, 0x01}, // PvPower1
	{&RegName::PvPower2, 187, Unit::WATT, 0, 0x01}, // PvPower2
	{&RegName::PvPower3, 188, Unit::WATT, 0, 0x01}, // PvPower3
	{&RegName::PvPower4, 189, Unit::WATT, 0, 0x01}, // PvPower4
	{&RegName::BatteryPower, 190, Unit::WATT, 0, 0x05}, // BatteryPower
	{&RegName::BatteryCurrent, 191, Unit::AMP, -2, 0x05}, // BatteryCurrent
	{&RegName::InverterFrequency, 193, Unit::HERTZ, -2, 0x01}, // InverterFrequency
	{&RegName::GridRelayStatus, 194, Unit::NONE, 0, 0x01}, // GridRelayStatus
	{&RegName::AuxRelayStatus, 195, Unit::HEXVAL, 0, 0x01}, // AuxRelayStatus
	{&RegName::BatteryCapacity, 204, Unit::AMPH, 0, 0x02}, // BatteryCapacity
	{&RegName::BatteryChargeMax, 210, Unit::AMP, 0, 0x02}, // BatteryChargeMax
	{&RegName::BatteryDischargeMax, 211, Unit::AMP, 0, 0x02}, // BatteryDischargeMax
	{&RegName::BatteryCapacityShutdown, 217, Unit::PERCENT, 0, 0x02}, // BatteryCapacityShutdown
	{&RegName::BatteryCapacityRestart, 218, Unit::PERCENT, 0, 0x02}, // BatteryCapacityRestart
	{&RegName::BatteryCapacityLow, 219, Unit::PERCENT, 0, 0x02}, // BatteryCapacityLow
	{&RegName::BatteryVoltageShutdown, 220, Unit::VOLT, -2, 0x02}, // BatteryVoltageShutdown
	{&RegName::BatteryVoltageRestart, 221, Unit::VOLT, -2, 0x02}, // BatteryVoltageRestart
	{&RegName::BatteryVoltageLow, 222, Unit::VOLT, -2, 0x02}, // BatteryVoltageLow
	{&RegName::GenOpTimeMax, 223, Unit::HOURS, -1, 0x02}, // GenOpTimeMax
	{&RegName::GenCoolingTime, 224, Unit::HOURS, -1, 0x02}, // GenCoolingTime
	{&RegName::GenChargeStartVoltage, 225, Unit::VOLT, -2, 0x02}, // GenChargeStartVoltage
	{&RegName::GenChargeStartCapacity, 226, Unit::PERCENT, 0, 0x02}, // GenChargeStartCapacity
	{&RegName::GenChargeCurrent, 227, Unit::AMP, 0, 0x02}, // GenChargeCurrent
	{&RegName::GridChargeStartVoltage, 228, Unit::VOLT, -2, 0x02}, // GridChargeStartVoltage
	{&RegName::GridChargeStartCapacity, 229, Unit::PERCENT, 0, 0x02}, // GridChargeStartCapacity
	{&RegName::GridChargeCurrent, 230, Unit::AMP, 0, 0x02}, // GridChargeCurrent
	{&RegName::GenChargeEnable, 231, Unit::NONE, 0, 0x02}, // GenChargeEnable
	{&RegName::GridChargeEnable, 232, Unit::NONE, 0, 0x02}, // GridChargeEnable
	{&RegName::SolarInputAsPsu, 233, Unit::NONE, 0, 0x02}, // SolarInputAsPsu
	{&RegName::GenForceAsLoad, 234, Unit::NONE, 0, 0x02}, // GenForceAsLoad
	{&RegName::GenInputMode, 235, Unit::NONE, 0, 0x02}, // GenInputMode
	{&RegName::SmartLoadOffVoltage, 236, Unit::VOLT, -2, 0x02}, // SmartLoadOffVoltage
	{&RegName::SmartLoadOffCapacity, 237, Unit::PERCENT, 0, 0x02}, // SmartLoadOffCapacity
	{&RegName::SmartLoadOnVoltage, 238, Unit::VOLT, -2, 0x02}, // SmartLoadOnVoltage
	{&RegName::SmartLoadOnCapacity, 239, Unit::PERCENT, 0, 0x02}, // SmartLoadOnCapacity
	{&RegName::GenStartMinSolar, 241, Unit::WATT, 0, 0x02}, // GenStartMinSolar
	{&RegName::GenGridSignalOn, 242, Unit::NONE, 0, 0x02}, // GenGridSignalOn
	{&RegName::LoadPriorityEnable, 243, Unit::NONE, 0, 0x02}, // LoadPriorityEnable
	{&RegName::LimitControlFunction, 244, Unit::NONE, 0, 0x02}, // LimitControlFunction
	{&RegName::GridPowerMax, 245, Unit::WATT, 0, 0x02}, // GridPowerMax
	{&RegName::CurrentSensorPhase, 246, Unit::NONE, 0, 0x02}, // CurrentSensorPhase
	{&RegName::SolarSellEnable, 247, Unit::NONE, 0, 0x02}, // SolarSellEnable
	{&RegName::TimeOfUseSelling, 248, Unit::NONE, 0, 0x02}, // TimeOfUseSelling
	{&RegName::Prog1Time, 250, Unit::BCDTIME, 0, 0x02}, // Prog1Time
	{&RegName::Prog2Time, 251, Unit::BCDTIME, 0, 0x02}, // Prog2Time
	{&RegName::Prog3Time, 252, Unit::BCDTIME, 0, 0x02}, // Prog3Time
	{&RegName::Prog4Time, 253, Unit::BCDTIME, 0, 0x02}, // Prog4Time
	{&RegName::Prog5Time, 254, Unit::BCDTIME, 0, 0x02}, // Prog5Time
	{&RegName::Prog6Time, 255, Unit::BCDTIME, 0, 0x02}, // Prog6Time
	{&RegName::Prog1Power, 256, Unit::WATT, 0, 0x02}, // Prog1Power
	{&RegName::Prog2Power, 257, Unit::WATT, 0, 0x02}, // Prog2Power
	{&RegName::Prog3Power, 258, Unit::WATT, 0, 0x02}, // Prog3Power
	{&RegName::Prog4Power, 259, Unit::WATT, 0, 0x02}, // Prog4Power
	{&RegName::Prog5Power, 260, Unit::WATT, 0, 0x02}, // Prog5Power
	{&RegName::Prog6Power, 261, Unit::WATT, 0, 0x02}, // Prog6Power
	{&RegName::Prog1Voltage, 262, Unit::VOLT, -2, 0x02}, // Prog1Voltage
	{&RegName::Prog2Voltage, 263, Unit::VOLT, -2, 0x02}, // Prog2Voltage
	{&RegName::Prog3Voltage, 264, Unit::VOLT, -2, 0x02}, // Prog3Voltage
	{&RegName::Prog4Voltage, 265, Unit::VOLT, -2, 0x02}, // Prog4Voltage
	{&RegName::Prog5Voltage, 266, Unit::VOLT, -2, 0x02}, // Prog5Voltage
	{&RegName::Prog6Voltage, 267, Unit::VOLT, -2, 0x02}, // Prog6Voltage
	{&RegName::Prog1Capacity, 268, Unit::PERCENT, 0, 0x02}, // Prog1Capacity
	{&RegName::Prog2Capacity, 269, Unit::PERCENT, 0, 0x02}, // Prog2Capacity
	{&RegName::Prog3Capacity, 270, Unit::PERCENT, 0, 0x02}, // Prog3Capacity
	{&RegName::Prog4Capacity, 271, Unit::PERCENT, 0, 0x02}, // Prog4Capacity
	{&RegName::Prog5Capacity, 272, Unit::PERCENT, 0, 0x02}, // Prog5Capacity
	{&RegName::Prog6Capacity, 273, Unit::PERCENT, 0, 0x02}, // Prog6Capacity
	{&RegName::Prog1Charge, 274, Unit::NONE, 0, 0x02}, // Prog1Charge
	{&RegName::Prog2Charge, 275, Unit::NONE, 0, 0x02}, // Prog2Charge
	{&RegName::Prog3Charge, 276, Unit::NONE, 0, 0x02}, // Prog3Charge
	{&RegName::Prog4Charge, 277, Unit::NONE, 0, 0x02}, // Prog4Charge
	{&RegName::Prog5Charge, 278, Unit::NONE, 0, 0x02}, // Prog5Charge
	{&RegName::Prog6Charge, 279, Unit::NONE, 0, 0x02}, // Prog6Charge
	{&RegName::MicroinverterExportToGridCutoff, 280, Unit::NONE, 0, 0x02}, // MicroinverterExportToGridCutoff
	{&RegName::RestoreConnectionTime, 282, Unit::SECOND, 0, 0x02}, // RestoreConnectionTime
	{&RegName::ArcFaultMode, 283, Unit::NONE, 0, 0x02}, // ArcFaultMode
	{&RegName::GridMode, 284, Unit::NONE, 0, 0x02}, // GridMode
	{&RegName::GridFrequencySelect, 285, Unit::NONE, 0, 0x02}, // GridFrequencySelect
	{&RegName::GridType, 286, Unit::NONE, 0, 0x02}, // GridType
	{&RegName::GridVoltageHigh, 287, Unit::VOLT, -1, 0x02}, // GridVoltageHigh
	{&RegName::GridVoltageLow, 288, Unit::VOLT, -1, 0x02}, // GridVoltageLow
	{&RegName::GridFreqHigh, 289, Unit::HERTZ, -2, 0x02}, // GridFreqHigh
	{&RegName::GridFreqLow, 290, Unit::HERTZ, -2, 0x02}, // GridFreqLow
	{&RegName::GenGridInput, 291, Unit::NONE, 0, 0x02}, // GenGridInput
	{&RegName::GenPeakShavingPower, 292, Unit::WATT, 0, 0x02}, // GenPeakShavingPower
	{&RegName::GridPeakShavingPower, 293, Unit::WATT, 0, 0x02}, // GridPeakShavingPower
	{&RegName::SmartLoadOpenDelay, 294, Unit::SECOND, 0, 0x02}, // SmartLoadOpenDelay
	{&RegName::OutputPfValue, 295, Unit::PERCENT, -1, 0x02}, // OutputPfValue
	{&RegName::Efficiency, 0, Unit::PERCENT, -1, 0x11}, // Efficiency
)

RegInfo getRegInfo(Register reg)
{
	return regInfo[unsigned(reg)];
}

} // namespace IO::Modbus::Sunsynk
