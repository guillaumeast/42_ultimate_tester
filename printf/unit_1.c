#include "ultimate_tester.h"
#include "libftprintf.h"
#include <stdio.h>

Compare(Basic_values, printf, ft_printf, COMPARE_BOTH, 1)
{
	// TODO: Macro Proto((void) (*fn)()) => Prebuild remplace ULT_PB_PROTO_ partout par cette signature de fonction
	Try("42");
	Try("%d", 42);
}
