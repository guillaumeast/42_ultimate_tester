#include "ft_ultimate_tester.h"
#include "libftprintf.h"

Test(comparison, 0)
{
	compare(COMP_RET_BOTH, printf, ft_printf, ("42"));
}
