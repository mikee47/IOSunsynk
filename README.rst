IOSunsynk
=========

Sunsynk hybrid inverter IO control library

.. image:: xxxxxxxx

Use BMS RS485 port (top left, next to BMS CAN port).

RS485 interface should not have a termination resistor.
At least, the typical 120 ohm value is too low - remove if present.

Open-circuit A/B voltage is between 4-5v, drops to around 0.5 with 120 ohms.

Inverter supposedly has termination resistor already but value unknown.
Resistor at other end should match it (clearly not 120 ohms).

.. doxygennamespace:: IO::Modbus::Sunsynk
   :members:
