/*
 * sunsynk.js
 *
 * GENERATED FILE: DO NOT EDIT
 *
 */
"use strict";

// Unit enumeration
const Unit = Object.freeze({
$enum_Unit
});

const unitSuffixes = Object.freeze([$unit_suffixes]);
const unitSuffixLengths = Object.freeze([$unit_suffix_lengths]);

const Attr = Object.freeze({
$enum_Attr
});

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

	// Convert 16-bit unsigned integer value into actual floating point value
    fromint(value) {
		if (this.attr.has(Attr.Signed) && value >= 0x8000) {
			value -= 0x10000;
		}
        value *= Math.pow(10, this.scale);
        if (this.unit == Unit.CELSIUS) {
            value -= 100;
		}
        if (this.scale < 0) {
            value = +(value.toFixed(-this.scale));
		}
        return value;
	}

};

const SunsynkRegister = Object.freeze({
$regdefs
});
