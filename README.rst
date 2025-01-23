IOSunsynk
=========

Sunsynk hybrid inverter IO control library for https://github.com/SmingHub/Sming.

.. image:: xxxxxxxx

Connect to inverter via BMS RS485 port (top left, next to BMS CAN port).

The RS485 interface circuit should not have a termination resistor.
Typical interfaces include a 120 ohm termination which is too low - remove if present.

Open-circuit A/B voltage is between 4-5v, drops to around 0.5 with 120 ohms.

Inverter supposedly has termination resistor already but value unknown.
Resistor at other end should match it (clearly not 120 ohms).

.. doxygennamespace:: IO::Modbus::Sunsynk
   :members:
