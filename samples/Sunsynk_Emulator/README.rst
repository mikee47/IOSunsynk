Sunsynk Emulator
================

Slave MODBUS device to support testing.

This version runs on an ESP8266 with dual MAX485.

======  ============
GPIO    Connection
======  ============
1       TXD
3       RXD
4       MAX1_DIR (MAX485#1 RE/DE)
5       MAX2_DIR (MAX485#2 RE/DE)
======  ============

Code will require adjusting depending on hardware.


Main registers are:

175 Inverter Power Total (synced with 178)
178 Load Power Total
184 Battery SOC
186 PV1 Power
187 PV2 Power
190 Battery Power

Battery power is calculated automatically when PV or load power registers are updated.
