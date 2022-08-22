
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
const char* unitSuffixes[]{$unit_suffixes};

const uint8_t unitSuffixLengths[]{$unit_suffix_lengths};

namespace RegName
{
$regnames
} // namespace RegName

DEFINE_FSTR_ARRAY(regInfo, RegInfo,
$regdefs
)

RegInfo getRegInfo(Register reg)
{
	return regInfo[unsigned(reg)];
}

} // namespace IO::Modbus::Sunsynk
