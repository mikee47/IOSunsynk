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
				return `0x$${hex(value)}`;
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
$regdefs
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
