from enum import IntEnum
from collections import OrderedDict
import argparse, string, os

class Unit(IntEnum):
    NONE = 0
    POWERFACTOR = 1
    WATT = 2
    WATTH = 3
    VARH = 4
    AMP = 5
    AMPH = 6
    VOLT = 7
    OHM = 8
    HERTZ = 9
    CELSIUS = 10
    PERCENT = 11
    SECOND = 12
    HOURS = 13
    BCDTIME = 14
    HEXVAL = 15
    ASCII = 16
    YEARMON = 17
    DAYHOUR = 18
    MINSEC = 19

    @property
    def suffix(self):
        suffixes = dict([
            (Unit.WATT, 'W'),
            (Unit.WATTH, 'Wh'),
            (Unit.VARH, 'VARh'),
            (Unit.AMP, 'A'),
            (Unit.AMPH, 'Ah'),
            (Unit.VOLT, 'V'),
            (Unit.OHM, 'R'),
            (Unit.HERTZ, 'Hz'),
            (Unit.CELSIUS, '°C'),
            (Unit.PERCENT, '%'),
            (Unit.SECOND, 's'),
            (Unit.HOURS, 'h'),
        ])
        return suffixes.get(self.value) or ''


SCALE_0_0001 = -4
SCALE_0_001 = -3
SCALE_0_01 = -2
SCALE_0_1 = -1
SCALE_NONE = 0
SCALE_10 = 1
SCALE_100 = 2
SCALE_1000 = 3


class Attr(IntEnum):
    ReadOnly = 0
    ReadWrite = 1
    Signed = 2
    LowWord = 3
    HighWord = 4
    Virtual = 5


class RegDef:
    def __init__(self, addr, name, unit=Unit.HEXVAL, scale=SCALE_NONE, attr=[Attr.ReadOnly]):
        self.addr = addr
        self.name = name
        self.unit = unit
        self.scale = scale
        self.attr = attr
        self.reg2 = None

    def toint(self, value: float):
        """Convert floating point value into stored integer representation"""
        if self.unit == Unit.CELSIUS:
            value += 100
        return round(value / pow(10, self.scale))

    def fromint(self, value: int):
        """Scale stored integer value into actual floating point value"""
        value = value * pow(10, self.scale)
        if self.unit == Unit.CELSIUS:
            value -= 100
        if self.scale < 0:
            value = round(value, -self.scale)
        return value


SUNSYNK_REGISTERS = [
    RegDef(0, 'DeviceType'),
    RegDef(1, 'ModbusAddress'),
    RegDef(2, 'CommsProtocolVersion'),
    RegDef(3, 'SerialNumber0', Unit.ASCII),
    RegDef(4, 'SerialNumber1', Unit.ASCII),
    RegDef(5, 'SerialNumber2', Unit.ASCII),
    RegDef(6, 'SerialNumber3', Unit.ASCII),
    RegDef(7, 'SerialNumber4', Unit.ASCII),
    RegDef(13, 'FwVerControl'),
    RegDef(14, 'FwVerComms'),
    RegDef(15, 'SafetyType'),
    RegDef(16, 'RatedPower', Unit.WATT, SCALE_0_1, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(17, 'RatedPowerHigh', Unit.WATT, SCALE_0_1, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(18, 'MpptNoAndPhases'),
    RegDef(20, 'RemoteLock', Unit.HEXVAL, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(21, 'SelfCheckTime', Unit.SECOND, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(22, 'SysTimeYearMon', Unit.YEARMON, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(23, 'SysTimeDayHour', Unit.DAYHOUR, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(24, 'SysTimeMinSec', Unit.MINSEC, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(25, 'InsImpedMin', Unit.OHM, SCALE_100, [Attr.ReadWrite]),
    RegDef(26, 'DcVoltageMax', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(27, 'GridVoltageMax', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(28, 'GridVoltageMin', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(29, 'GridFreqMax', Unit.HERTZ, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(30, 'GridFreqLower', Unit.HERTZ, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(31, 'GridCurrentMax', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 ?
    RegDef(32, 'StartingVoltageMax', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 10000 ?
    RegDef(33, 'StartingVoltageMin', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 3000 ?
    RegDef(34, 'OverFreqDeratePoint', Unit.HERTZ, SCALE_0_01, [Attr.ReadWrite]),  # 8000 ?
    RegDef(35, 'OverFreqDeRate', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # 2000 ?
    RegDef(36, 'InternalTempMax', Unit.NONE, SCALE_0_1, [Attr.ReadWrite, Attr.Signed]), # 850 -> 85 degrees
    RegDef(37, 'CommsAddr', Unit.NONE),
    RegDef(39, 'PowerFactorRegulation', Unit.POWERFACTOR, SCALE_0_001, [Attr.ReadWrite]), # 1000
    RegDef(40, 'ActivePowerRegulation', Unit.PERCENT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(41, 'ReactivePowerRegulation', Unit.PERCENT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(42, 'ApparentPowerRegulation', Unit.PERCENT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(43, 'SwitchOnOffEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(44, 'FactoryResetEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(45, 'SelfCheckingTime', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(46, 'IslandProtectionEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(53, 'MaxSolarPower', Unit.WATT),
    RegDef(59, 'RunState', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(60, 'ActiveEnergyToday', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.Signed]),
    RegDef(61, 'ReactiveEnergyToday', Unit.VARH, SCALE_100, [Attr.ReadOnly, Attr.Signed]),
    RegDef(62, 'GenEnergyToday', Unit.WATTH, SCALE_100),
    RegDef(63, 'ActiveEnergyTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.Signed, Attr.LowWord]),
    RegDef(64, 'ActiveEnergyTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.Signed, Attr.HighWord]),
    RegDef(65, 'PvEnergyMonth', Unit.WATTH, SCALE_1000),
    RegDef(66, 'LoadEnergyMonth', Unit.WATTH, SCALE_1000),
    RegDef(67, 'GridEnergyMonth', Unit.WATTH, SCALE_1000),
    RegDef(68, 'PvEnergyYear', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(69, 'PvEnergyYearHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(70, 'BatChargeToday', Unit.WATTH, SCALE_100),
    RegDef(71, 'BatDischargeToday', Unit.WATTH, SCALE_100),
    RegDef(72, 'BatChargeTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(73, 'BatChargeTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(74, 'BatDischargeTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(75, 'BatDischargeTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(76, 'GridImportToday', Unit.WATTH, SCALE_100),
    RegDef(77, 'GridExportToday', Unit.WATTH, SCALE_100),
    RegDef(78, 'GridImportTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(79, 'GridFrequency', Unit.HERTZ, SCALE_0_01),
    RegDef(80, 'GridImportTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(81, 'GridExportTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(82, 'GridExportTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(83, 'GenDailyOperatingTime', Unit.SECOND, SCALE_0_1),
    RegDef(84, 'LoadEnergyToday', Unit.WATTH, SCALE_100),
    RegDef(85, 'LoadEnergyTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(86, 'LoadEnergyTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(87, 'LoadEnergyYear', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(88, 'LoadEnergyYearHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(90, 'DcTemp', Unit.CELSIUS, SCALE_0_1, [Attr.ReadOnly, Attr.Signed]),
    RegDef(91, 'IgbtTemp', Unit.CELSIUS, SCALE_0_1, [Attr.ReadOnly, Attr.Signed]),
    RegDef(92, 'Inductance1Temp', Unit.CELSIUS, SCALE_0_1, [Attr.ReadOnly, Attr.Signed]),
    RegDef(93, 'PowerFactor', Unit.POWERFACTOR, SCALE_0_001),
    RegDef(94, 'SdStatus', Unit.NONE),
    RegDef(95, 'EnvironmentTemperature', Unit.CELSIUS, SCALE_0_1, [Attr.ReadOnly, Attr.Signed]),
    RegDef(96, 'PvEnergyTotal', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.LowWord]),
    RegDef(97, 'PvEnergyTotalHigh', Unit.WATTH, SCALE_100, [Attr.ReadOnly, Attr.HighWord]),
    RegDef(100, 'OtherTestFlags', Unit.NONE),
    RegDef(101, 'Warning1', Unit.NONE),
    RegDef(102, 'Warning2', Unit.NONE),
    RegDef(103, 'Fault1', Unit.NONE),
    RegDef(104, 'Fault2', Unit.NONE),
    RegDef(105, 'Fault3', Unit.NONE),
    RegDef(106, 'Fault4', Unit.NONE),
    RegDef(107, 'CorrectedAh', Unit.AMPH),
    RegDef(108, 'PvEnergyToday', Unit.WATTH, SCALE_100),
    RegDef(109, 'Pv1Voltage', Unit.VOLT, SCALE_0_1),
    RegDef(110, 'Pv1Current', Unit.AMP, SCALE_0_1),
    RegDef(111, 'Pv2Voltage', Unit.VOLT, SCALE_0_1),
    RegDef(112, 'Pv2Current', Unit.AMP, SCALE_0_1),
    RegDef(113, 'Pv3Voltage', Unit.VOLT, SCALE_0_1),
    RegDef(114, 'Pv3Current', Unit.AMP, SCALE_0_1),
    RegDef(115, 'Pv4Voltage', Unit.VOLT, SCALE_0_1),
    RegDef(116, 'Pv4Current', Unit.AMP, SCALE_0_1),
    RegDef(150, 'GridVoltage', Unit.VOLT, SCALE_0_1),
    RegDef(154, 'InverterVoltage', Unit.VOLT, SCALE_0_1),
    RegDef(157, 'LoadVoltage', Unit.VOLT, SCALE_0_1),
    RegDef(160, 'GridCurrentL1', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(161, 'GridCurrentL2', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(162, 'LimiterCurrentL1', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(163, 'LimiterCurrentL2', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(164, 'InverterCurrentL1', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(165, 'InverterCurrentL2', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(166, 'AuxPower', Unit.WATT),
    RegDef(167, 'GridPowerL1', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(168, 'GridPowerL2', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(169, 'GridPowerTotal', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(170, 'LimiterPowerL1', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(171, 'LimiterPowerL2', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(172, 'LimiterPowerTotal', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(173, 'InverterPowerL1', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(174, 'InverterPowerL2', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(175, 'InverterPowerTotal', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(176, 'LoadPowerL1', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(177, 'LoadPowerL2', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(178, 'LoadPowerTotal', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(179, 'LoadCurrentL1', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(180, 'LoadCurrentL2', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(181, 'Undefined181', Unit.NONE),
    RegDef(182, 'BatteryTemp', Unit.CELSIUS, SCALE_0_1, [Attr.ReadOnly, Attr.Signed]),
    RegDef(183, 'BatteryVoltage', Unit.VOLT, SCALE_0_01),
    RegDef(184, 'BatterySOC', Unit.PERCENT),
    RegDef(186, 'Pv1Power', Unit.WATT),
    RegDef(187, 'Pv2Power', Unit.WATT),
    RegDef(188, 'Pv3Power', Unit.WATT),
    RegDef(189, 'Pv4Power', Unit.WATT),
    RegDef(190, 'BatteryPower', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(191, 'BatteryCurrent', Unit.AMP, SCALE_0_01, [Attr.ReadOnly, Attr.Signed]),
    RegDef(192, 'LoadFrequency', Unit.HERTZ, SCALE_0_01),
    RegDef(193, 'InverterFrequency', Unit.HERTZ, SCALE_0_01),
    RegDef(194, 'GridRelayStatus', Unit.NONE),
    RegDef(195, 'AuxRelayStatus'),
    RegDef(196, 'GeneratorFrequency', Unit.HERTZ, SCALE_0_01),
    RegDef(200, 'BatteryControlMode', Unit.NONE),
    RegDef(201, 'BatteryEqualizationVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(202, 'BatteryAbsorptionVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(203, 'BatteryFloatVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(204, 'BatteryCapacity', Unit.AMPH, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(205, 'BatteryEmptyVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(206, 'ZeroExportPowerLimit', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(207, 'BatteryEqualizationDayCycle', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # In days (90)
    RegDef(208, 'BatteryEqualizationTime', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(209, 'BatteryTempCo', Unit.NONE, SCALE_NONE, [Attr.ReadWrite, Attr.Signed]), # mV / deg. C
    RegDef(210, 'BatteryChargeMax', Unit.AMP, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(211, 'BatteryDischargeMax', Unit.AMP, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(213, 'BatteryVoltOrCapacity', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # 0: voltage, 1: capacity, 2: no battery
    RegDef(214, 'BatteryLithiumWakeupSignBit', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # 0: enabled, 1: disabled
    RegDef(215, 'BatteryResistance', Unit.OHM, SCALE_0_0001, [Attr.ReadWrite]),
    RegDef(216, 'BatteryChargingEfficiency', Unit.PERCENT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(217, 'BatteryCapacityShutdown', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(218, 'BatteryCapacityRestart', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(219, 'BatteryCapacityLow', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(220, 'BatteryVoltageShutdown', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(221, 'BatteryVoltageRestart', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(222, 'BatteryVoltageLow', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(223, 'GenOpTimeMax', Unit.HOURS, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(224, 'GenCoolingTime', Unit.HOURS, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(225, 'GenChargeStartVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(226, 'GenChargeStartCapacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(227, 'GenChargeCurrent', Unit.AMP, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(228, 'GridChargeStartVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(229, 'GridChargeStartCapacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(230, 'GridChargeCurrent', Unit.AMP, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(231, 'GenChargeEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(232, 'GridChargeEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(233, 'SolarInputAsPsu', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(234, 'GenForceAsLoad', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(235, 'GenInputMode', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(236, 'SmartLoadOffVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(237, 'SmartLoadOffCapacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(238, 'SmartLoadOnVoltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(239, 'SmartLoadOnCapacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(241, 'GenStartMinSolar', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(242, 'GenGridSignalOn', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(243, 'LoadPriorityEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(244, 'LimitControlFunction', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(245, 'GridPowerMax', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(246, 'CurrentSensorPhase', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(247, 'SolarSellEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(248, 'TimeOfUseSelling', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(250, 'Prog1Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(251, 'Prog2Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(252, 'Prog3Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(253, 'Prog4Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(254, 'Prog5Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(255, 'Prog6Time', Unit.BCDTIME, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(256, 'Prog1Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(257, 'Prog2Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(258, 'Prog3Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(259, 'Prog4Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(260, 'Prog5Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(261, 'Prog6Power', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(262, 'Prog1Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(263, 'Prog2Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(264, 'Prog3Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(265, 'Prog4Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(266, 'Prog5Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(267, 'Prog6Voltage', Unit.VOLT, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(268, 'Prog1Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(269, 'Prog2Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(270, 'Prog3Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(271, 'Prog4Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(272, 'Prog5Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(273, 'Prog6Capacity', Unit.PERCENT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(274, 'Prog1Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # Unit.1: Grid, 2: Gen
    RegDef(275, 'Prog2Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(276, 'Prog3Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(277, 'Prog4Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(278, 'Prog5Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(279, 'Prog6Charge', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(280, 'MicroinverterExportToGridCutoff', Unit.HEXVAL, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(282, 'RestoreConnectionTime', Unit.SECOND, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(283, 'ArcFaultMode', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(284, 'GridMode', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(285, 'GridFrequencySelect', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(286, 'GridType', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(287, 'GridVoltageHigh', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(288, 'GridVoltageLow', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(289, 'GridFreqHigh', Unit.HERTZ, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(290, 'GridFreqLow', Unit.HERTZ, SCALE_0_01, [Attr.ReadWrite]),
    RegDef(291, 'GenGridInput', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(292, 'GenPeakShavingPower', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(293, 'GridPeakShavingPower', Unit.WATT, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(294, 'SmartLoadOpenDelay', Unit.SECOND, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(295, 'OutputPfValue', Unit.PERCENT, SCALE_0_1, [Attr.ReadWrite]),
    RegDef(296, 'ExtRelayBit'),

    RegDef(312, 'ChargingVoltage', Unit.VOLT, SCALE_0_01),
    RegDef(313, 'DischargeVoltage', Unit.VOLT, SCALE_0_01),
    RegDef(314, 'ChargingCurrentLimiting', Unit.AMP),
    RegDef(315, 'DischargeCurrentLimiting', Unit.AMP),
    RegDef(316, 'RealTimeCapacity', Unit.PERCENT),
    RegDef(317, 'RealTimeVoltage', Unit.VOLT, SCALE_0_01),
    RegDef(318, 'RealTimeCurrent', Unit.AMP, SCALE_NONE, [Attr.ReadOnly, Attr.Signed]),
    RegDef(319, 'RealTimeTemp', Unit.CELSIUS, SCALE_0_1),
    RegDef(320, 'MaxChargeCurrentLimit', Unit.AMP),
    RegDef(321, 'MaxDischargeCurrentLimit', Unit.AMP),
    RegDef(322, 'LithiumBatteryAlarm', Unit.NONE),
    RegDef(323, 'LithiumBatteryFaultLocation'),
    RegDef(324, 'LithiumBatterySymbol2'),
    RegDef(325, 'LithiumBatteryType'),
    RegDef(326, 'Ex_MeterCT'),
    RegDef(327, 'CT_Ratio', Unit.NONE),
    RegDef(328, 'SpecialFunctionBits'),
    RegDef(329, 'AC_CoupleFrequencyUpperLimit', Unit.HERTZ, SCALE_0_01),
    RegDef(330, 'CommBoardSettingFunction'),

    RegDef(390, 'Solar1WindEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # 0: disable, 1: enable
    RegDef(391, 'Solar2WindEnable', Unit.NONE, SCALE_NONE, [Attr.ReadWrite]), # 0: disable, 1: enable
    RegDef(392, 'WindVoltage1', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(393, 'WindVoltage2', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(394, 'WindVoltage3', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(395, 'WindVoltage4', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(396, 'WindVoltage5', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(397, 'WindVoltage6', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(398, 'WindVoltage7', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(399, 'WindVoltage8', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(400, 'WindVoltage9', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(401, 'WindVoltage10', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(402, 'WindVoltage11', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(403, 'WindVoltage12', Unit.VOLT, SCALE_0_1, [Attr.ReadWrite]), # 500 - 5000
    RegDef(404, 'WindCurrent1', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(405, 'WindCurrent2', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(406, 'WindCurrent3', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(407, 'WindCurrent4', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(408, 'WindCurrent5', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(409, 'WindCurrent6', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(410, 'WindCurrent7', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(411, 'WindCurrent8', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(412, 'WindCurrent9', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(413, 'WindCurrent10', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(414, 'WindCurrent11', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200
    RegDef(415, 'WindCurrent12', Unit.AMP, SCALE_0_1, [Attr.ReadWrite]), # 0 - 200

    RegDef(416, 'ForcedOffGridOperation'),

    RegDef(417, 'ParallelRegister1'),
    RegDef(418, 'ParallelRegister2'),

    RegDef(419, 'LithiumBatteryVersionLow'),
    RegDef(420, 'LithiumBatteryVersionHigh'),

    RegDef(421, 'SyncTimeYearMon', Unit.YEARMON, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(422, 'SyncTimeDayHour', Unit.DAYHOUR, SCALE_NONE, [Attr.ReadWrite]),
    RegDef(423, 'SyncTimeMinSec', Unit.MINSEC, SCALE_NONE, [Attr.ReadWrite]),

    # Last readable register 698 - reading 699+ fails

    RegDef(0, 'Efficiency', Unit.PERCENT, SCALE_0_1, [Attr.ReadOnly, Attr.Virtual]),
    RegDef(0, 'PvPowerTotal', Unit.WATT, SCALE_NONE, [Attr.ReadOnly, Attr.Virtual]),
]

SUNSYNK_REGMAP = OrderedDict([(r.addr, r) for r in SUNSYNK_REGISTERS])
SUNSYNK_REGMAP_NAME = OrderedDict([(r.name, r) for r in SUNSYNK_REGISTERS])

for r in SUNSYNK_REGISTERS:
    if Attr.LowWord in r.attr:
        r.reg2 = SUNSYNK_REGMAP_NAME[r.name + 'High']
    elif Attr.HighWord in r.attr:
        r.reg2 = SUNSYNK_REGMAP_NAME[r.name.removesuffix('High')]


def main():
    parser = argparse.ArgumentParser(description='Sunsynk register definitions')
    parser.add_argument('--generate', action='store_true', help='Generate C++ header and code')

    args = parser.parse_args()

    if args.generate:
        def generate(filename, values):
            templateFilename = os.path.join('tools', os.path.basename(filename))
            with open(templateFilename, "r") as f:
                tmpl = string.Template(f.read())
            print("Writing to", filename)
            with open(filename, "w") as f:
                f.write(tmpl.substitute(values))

        def enumValues(enum):
            return "\n".join(f"\t{e.name} = {i}," for i, e in enumerate(enum))

        def attrvalue(attr):
            return sum((1 << a) for a in attr) if type(attr) is list else 1 << attr

        values = dict(
            enum_Unit = enumValues(Unit),
            enum_Attr = enumValues(Attr),
            enum_Attr_len = len(Attr),
            enum_Register = enumValues(SUNSYNK_REGISTERS),
            enum_Register_len = len(SUNSYNK_REGISTERS),
        )
        generate('src/include/Sunsynk/Sunsynk.h', values)

        def reg2_name(r):
            return ', Register::' + r.reg2.name if r.reg2 else ''
        values = dict(
            unit_suffixes = ", ".join(f'"{u.suffix}"' for u in Unit),
            unit_suffix_lengths = ", ".join(str(len(u.suffix)) for u in Unit),
            regnames = "\n".join(f'DEFINE_FSTR({r.name}, "{r.name}")' for r in SUNSYNK_REGISTERS),
            regdefs = "\n".join(f'\t{{&RegName::{r.name}, {r.addr}, Unit::{r.unit.name}, {r.scale}, {attrvalue(r.attr):#04x}{reg2_name(r)}}},' for r in SUNSYNK_REGISTERS),
        )
        generate('src/Sunsynk.cpp', values)

        # Javascript
        def jsEnumValues(enum):
            return "\n".join(f"\t{e.name}: {i}," for i, e in enumerate(enum))

        def jsAttrValue(attr):
            return ", ".join(f'Attr.{a.name}' for a in attr)

        values = dict(
            enum_Unit = jsEnumValues(Unit),
            enum_Attr = jsEnumValues(Attr),
            enum_Attr_len = len(Attr),
            unit_suffixes = ", ".join(f'"{u.suffix}"' for u in Unit),
            unit_suffix_lengths = ", ".join(str(len(u.suffix)) for u in Unit),
            regdefs = "".join(f'\t{r.name}: new RegDef("{r.name}", {r.addr}, Unit.{r.unit.name}, {r.scale}, [{jsAttrValue(r.attr)}]),\n' for r in SUNSYNK_REGISTERS),
        )
        generate('src/sunsynk.js', values)

if __name__ == "__main__":
    main()
