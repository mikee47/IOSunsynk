/**
 * @brief Sunsynk hybrid inverter sensor definitions
 * 
 * Based on https://github.com/kellerza/sunsynk/tree/main/sunsynk
 */

#pragma once

enum Group {
	Battery,
	InverterPower,
	GridPower,
	LoadPower,
	SolarPower1,
	SolarPower2,
	PowerOnOutput,
	Energy,
	General,
	Setting,
	Program,
};

enum Unit {
	CUSTOM,
	CELSIUS, // °C
	KWH,	 // kWh
	AMPS,	// A
	VOLT,	// V
	WATT,	// W
	PERCENT,
	HERTZ,
	TIME,
};

enum Class {
	Sensor,
	TempSensor,
	FaultSensor,
	InverterStateSensor,
	SDStatusSensor,
	SerialSensor,
	TimeRWSensor,
	RWSensor,
};

// Register, Group, Class, name, unit, factor
#define SUNSYNK_SENSOR_MAP(XX)                                                                                         \
	XX(0, DeviceType, General, Sensor, "Device Type")                                                                  \
	XX(1, ModbusAddress, General, Sensor)                                                                              \
	XX(2, CommsProtocolVersion, General, Sensor)                                                                       \
	XX(3, SerialNumber0, General, Sensor)                                                                              \
	XX(4, SerialNumber1, General, Sensor)                                                                              \
	XX(5, SerialNumber2, General, Sensor)                                                                              \
	XX(6, SerialNumber3, General, Sensor)                                                                              \
	XX(7, SerialNumber4, General, Sensor)                                                                              \
	XX(13, FwVerControl, General, Sensor)                                                                              \
	XX(14, FwVerComms, General, Sensor)                                                                                \
	XX(15, SafetyType, General, Sensor)                                                                                \
	XX(16, RatedPowerLow, General, Sensor, "", KWH)                                                                    \
	XX(17, RatedPowerHigh, General, Sensor)                                                                            \
	XX(18, MpptNoAndPhases, General, Sensor, "0x2201")                                                                 \
	XX(20, RemoteLock, General, RWSensor)                                                                              \
	XX(21, SelfCheckTime, General, RWSensor)                                                                           \
	XX(22, SysTimeYearMon, General, RWSensor)                                                                          \
	XX(23, SysTimeDayHour, General, RWSensor)                                                                          \
	XX(24, SysTimeMinSec, General, RWSensor)                                                                           \
	XX(25, InsImpedMin, General, RWSensor)                                                                             \
	XX(26, DcVoltsMax, General, RWSensor, "", VOLT)                                                                    \
	XX(27, GridVoltsMax, General, RWSensor, "", VOLT)                                                                  \
	XX(28, GridVoltsMin, General, RWSensor, "", VOLT)                                                                  \
	XX(29, GridFreqMax, General, RWSensor, "", HERTZ)                                                                  \
	XX(30, GridFreqLower, General, RWSensor, "", HERTZ)                                                                \
	XX(31, GridCurrentMax, General, RWSensor, "0 ?")                                                                   \
	XX(32, StartingVoltsMax, General, RWSensor, "10000 ?")                                                             \
	XX(33, StartingVoltsMin, General, RWSensor, "3000 ?")                                                              \
	XX(34, OverFreqDeratePoint, General, RWSensor, "8000 ?")                                                           \
	XX(35, OverFreqDeRate, General, RWSensor, "2000 ?")                                                                \
	XX(36, InternalTempMax, General, RWSensor, "850", CELSIUS)                                                         \
	XX(37, CommsAddr, General, Sensor, "1")                                                                            \
	XX(39, PowerFactorRegulation, General, RWSensor, "1000")                                                           \
	XX(40, ActivePowerRegulation, General, RWSensor, "0")                                                              \
	XX(41, ReactivePowerRegulation, General, RWSensor, "0")                                                            \
	XX(42, ApparentPower, General, RWSensor, "0 ?")                                                                    \
	XX(43, SwitchOnOffEnable, General, RWSensor, "1")                                                                  \
	XX(44, FactoryResetEnable, General, RWSensor)                                                                      \
	XX(45, SelfCheckingTime, General, RWSensor)                                                                        \
	XX(46, IslandProtectionEnable, General, Sensor, "0")                                                               \
	XX(59, RunState, General, InverterStateSensor, "Overall state")                                                    \
	XX(60, DayActivePower, Energy, Sensor, "Day Active Power", KWH, -0.1)                                              \
	XX(61, DayReactivePower, Energy, Sensor, "Day Reactive Power", "kVarh", -0.1)                                      \
	XX(65, MonthPvPower, Energy, Sensor, "Month PV Power", KWH)                                                        \
	XX(66, MonthLoadPower, Energy, Sensor, "Month Load Power", KWH)                                                    \
	XX(67, MonthGridPower, Energy, Sensor, "Month Grid Power", KWH)                                                    \
	XX(70, DayBatteryCharge, Energy, Sensor, "Day Battery Charge", KWH, 0.1)                                           \
	XX(71, DayBatteryDischarge, Energy, Sensor, "Day Battery discharge", KWH, 0.1)                                     \
	XX(76, DayGridImport, Energy, Sensor, "Day Grid Import", KWH, 0.1)                                                 \
	XX(77, DayGridExport, Energy, Sensor, "Day Grid Export", KWH, 0.1)                                                 \
	XX(79, GridFrequency, GridPower, Sensor, "Grid frequency", "Hz", 0.01)                                             \
	XX(84, DayLoadPower, Energy, Sensor, "Day Load Power", KWH, 0.1)                                                   \
	XX(90, DcTemp, General, TempSensor, "DC transformer temperature", CELSIUS, 0.1)                                    \
	XX(91, IgbtTemp, General, TempSensor, "IGBT temperature", CELSIUS, 0.1)                                            \
	XX(92, Inductance1Temp, General, TempSensor, "Inductance 1 temperature", CELCIUS, 0.1)                             \
	XX(93, PowerFactor, General, Sensor, "Power Factor")                                                               \
	XX(94, SdStatus, General, SDStatusSensor, "SD Status")                                                             \
	XX(95, EnvironmentTemperature, General, TempSensor, "Environment temperature", CELSIUS, 0.1)                       \
	XX(101, Warning1, General, Sensor)                                                                                 \
	XX(102, Warning2, General, Sensor)                                                                                 \
	XX(103, Fault1, General, Sensor)                                                                                   \
	XX(104, Fault2, General, Sensor)                                                                                   \
	XX(105, Fault3, General, Sensor)                                                                                   \
	XX(106, Fault4, General, Sensor)                                                                                   \
	XX(107, CorrectedAh, General, Sensor, "Corrected AH")                                                              \
	XX(108, DayPvEnergy, Energy, Sensor, "Day PV Energy", KWH, 0.1)                                                    \
	XX(109, PvVoltage1, SolarPower1, Sensor, "PV1 voltage", VOLT, 0.1)                                                 \
	XX(110, PvCurrent1, SolarPower1, Sensor, "PV1 current", AMPS, 0.1)                                                 \
	XX(111, PvVoltage2, SolarPower2, Sensor, "PV2 voltage", VOLT, 0.1)                                                 \
	XX(112, PvCurrent2, SolarPower2, Sensor, "PV2 current", AMPS, 0.1)                                                 \
	XX(150, GridVoltage, GridPower, Sensor, "Grid voltage", VOLT, 0.1)                                                 \
	XX(154, InverterVoltage, InverterPower, Sensor, "Inverter voltage", VOLT, 0.1)                                     \
	XX(157, LoadVoltage, LoadPower, Sensor, "Load voltage", VOLT, 0.1)                                                 \
	XX(160, GridCurrentL1, GridPower, Sensor, "Grid current L1", AMPS, 0.01)                                           \
	XX(161, GridCurrentL2, GridPower, Sensor, "Grid current L2", AMPS, 0.01)                                           \
	XX(166, AuxPower, PowerOnOutput, Sensor, "AUX power", WATT, -1)                                                    \
	XX(167, GridPowerL1, GridPower, Sensor, "Grid LD power", WATT, -1, "L1 seems to be LD")                            \
	XX(168, GridPowerL2, GridPower, Sensor, "Grid L2 power", WATT, -1)                                                 \
	XX(169, GridPowerTotal, GridPower, Sensor, "Grid power", WATT, -1, "L1(167) + L2(168)")                            \
	XX(172, GridPowerCT, GridPower, Sensor, "Grid CT power", WATT, -1)                                                 \
	XX(173, InverterPowerL1, InverterPower, Sensor, "Inverter power L1", WATT, -1)                                     \
	XX(174, InverterPowerL2, InverterPower, Sensor, "Inverter power L2", WATT, -1)                                     \
	XX(175, InverterTotalPower, InverterPower, Sensor, "Inverter power", WATT, -1)                                     \
	XX(176, LoadPowerL1, LoadPower, Sensor, "Load L1 power", WATT, -1)                                                 \
	XX(177, LoadPowerL2, LoadPower, Sensor, "Load L2 power", WATT, -1)                                                 \
	XX(178, LoadPowerTotal, LoadPower, Sensor, "Load power", WATT, -1, "L1(176) + L2(177)")                            \
	XX(179, LoadCurrentL1, LoadPower, Sensor, "Load current L1", AMP, 0.01)                                            \
	XX(180, LoadCurrentL2, LoadPower, Sensor, "Load current L2", AMP, 0.01)                                            \
	XX(182, BatteryTemperature, Battery, TempSensor, "Battery temperature", CELSIUS, 0.1)                              \
	XX(183, BatteryVoltage, Battery, Sensor, "Battery voltage", VOLT, 0.01)                                            \
	XX(184, BatterySOC, Battery, Sensor, "Battery SOC", PERCENT, 0)                                                    \
	XX(186, PvPower1, SolarPower1, Sensor, "PV1 power", WATT, -1)                                                      \
	XX(187, PvPower2, SolarPower2, Sensor, "PV2 power", WATT, -1)                                                      \
	XX(190, BatteryPower, Battery, Sensor, "Battery power", WATT, -1)                                                  \
	XX(191, BatteryCurrent, Battery, Sensor, "Battery current", AMPS, -0.01)                                           \
	XX(193, InverterFrequency, InverterPower, Sensor, "Inverter frequency", "Hz", 0.01)                                \
	XX(194, GridConnectedStatus, General, Sensor, "Grid Connected Status", CUSTOM, 0)                                  \
	XX(200, DayLoadPower, Energy, Sensor, "Day Load Power", KWH, 0.01)                                                 \
	XX(230, GridChargeBatteryCurrent, Setting, Sensor, "Grid Charge Battery current", AMPS, -1)                        \
	XX(232, GridChargeEnabled, Setting, Sensor, "Grid Charge enabled", CUSTOM, 0)                                      \
	XX(251, Program, TimeRWSensor, "Prog2 Time", TIME, 0)                                                              \
	XX(252, Program, TimeRWSensor, "Prog3 Time", TIME, 0)                                                              \
	XX(253, Program, TimeRWSensor, "Prog4 Time", TIME, 0)                                                              \
	XX(254, Program, TimeRWSensor, "Prog5 Time", TIME, 0)                                                              \
	XX(255, Program, TimeRWSensor, "Prog6 Time", TIME, 0)                                                              \
	XX(256, Program, RWSensor, "Prog1 power", WATT, 0)                                                                 \
	XX(257, Program, RWSensor, "Prog2 power", WATT, 0)                                                                 \
	XX(258, Program, RWSensor, "Prog3 power", WATT, 0)                                                                 \
	XX(259, Program, RWSensor, "Prog4 power", WATT, 0)                                                                 \
	XX(260, Program, RWSensor, "Prog5 power", WATT, 0)                                                                 \
	XX(261, Program, RWSensor, "Prog6 power", WATT, 0)                                                                 \
	XX(262, Program, RWSensor, "Prog1 voltage", VOLT, 0.1)                                                             \
	XX(263, Program, RWSensor, "Prog2 voltage", VOLT, 0.1)                                                             \
	XX(264, Program, RWSensor, "Prog3 voltage", VOLT, 0.1)                                                             \
	XX(265, Program, RWSensor, "Prog4 voltage", VOLT, 0.1)                                                             \
	XX(266, Program, RWSensor, "Prog5 voltage", VOLT, 0.1)                                                             \
	XX(267, Program, RWSensor, "Prog6 voltage", VOLT, 0.1)                                                             \
	XX(268, Program, RWSensor, "Prog1 Capacity", PERCENT, 0)                                                           \
	XX(269, Program, RWSensor, "Prog2 Capacity", PERCENT, 0)                                                           \
	XX(270, Program, RWSensor, "Prog3 Capacity", PERCENT, 0)                                                           \
	XX(271, Program, RWSensor, "Prog4 Capacity", PERCENT, 0)                                                           \
	XX(272, Program, RWSensor, "Prog5 Capacity", PERCENT, 0)                                                           \
	XX(273, Program, RWSensor, "Prog6 Capacity", PERCENT, 0)                                                           \
	XX(274, Program, RWSensor, "Prog1 Charge", CUSTOM, 0)                                                              \
	XX(275, Program, RWSensor, "Prog2 Charge", CUSTOM, 0)                                                              \
	XX(276, Program, RWSensor, "Prog3 Charge", CUSTOM, 0)                                                              \
	XX(277, Program, RWSensor, "Prog4 Charge", CUSTOM, 0)                                                              \
	XX(278, Program, RWSensor, "Prog5 Charge", CUSTOM, 0)                                                              \
	XX(279, Program, RWSensor, "Prog6 Charge", CUSTOM, 0)                                                              \
	XX(312, Setting, Sensor, "Battery charging voltage", VOLT, 0.01)                                                   \
	XX(603, Setting, Sensor, "Bat1 SOC", PERCENT, 1)                                                                   \
	XX(611, Setting, Sensor, "Bat1 Cycle", CUSTOM, 0)

/*
XX((63, 64), Energy, Sensor32, "Total Active Power", KWH, 0.1)                                                       \
XX((72, 73), Energy, Sensor32, "Total Battery Charge", KWH, 0.1)                                                     \
XX((74, 75), Energy, Sensor32, "Total Battery Discharge", KWH, 0.1)                                                  \
XX((81, 82), Energy, Sensor32, "Total Grid Export", KWH, 0.1)                                                        \
XX((78, 80), Energy, Sensor32, "Total Grid Import", KWH, 0.1)                                                        \
XX((85, 86), Energy, Sensor32, "Total Load Power", KWH, 0.1)                                                         \
XX((96, 97), Energy, Sensor32, "Total PV Power", KWH, 0.1)                                                           \
XX((98, 99), Energy, Sensor32, "Year Grid Export", KWH, 0.1)                                                         \
XX((87, 88), Energy, Sensor32, "Year Load Power", KWH, 0.1)                                                          \
XX((68, 69), Energy, Sensor32, "Year PV Power", KWH, 0.1)                                                            \
XX((160, 161), GridPower, MathSensor, "Grid current", AMPS, {0.01, 0.01}) \
XX((175, 167, 166), PowerOnOutput, MathSensor, "Essential power", WATT, factors=(1, 1, -1)) \
XX((172, 167), PowerOnOutput, MathSensor, "Non-Essential power", WATT, factors=(1, -1)) \
XX((103, 104, 105, 106, 107), General, FaultSensor, "Fault")                                                       \
XX((3, 4, 5, 6, 7), General, SerialSensor, "Serial")                                                               \
*/
