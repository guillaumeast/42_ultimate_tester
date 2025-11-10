#include "ultimate_tester.h"
#include "libftprintf.h"
#include <stdio.h>

Compare(Basic_values, printf, ft_printf, COMPARE_BOTH, 1)
{
	char	a;
	
	Try();
	Try("42");
	Try(&a);
	Try("%d", 42);
}
