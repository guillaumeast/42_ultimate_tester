#include "ultimate_tester.h"	// Compare(), Try(), COMPARE_BOTH
#include "libftprintf.h"		// ft_printf()
#include <stdio.h>				// printf()

Compare(Basic_values, printf, ft_printf, COMPARE_BOTH, 1)
{
	Try();			// Compare outputs and returned_values of `printf()` and `ft_printf()`
	Try("42");		// Compare outputs and returned_values of `printf("42")` and `ft_printf("42")`
	Try("%d", 42);	// Compare outputs and returned_values of `printf("%d", 42)` and `ft_printf("%d", 42)`
}
