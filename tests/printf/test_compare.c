#include "ft_ultimate_tester.h"
#include "libftprintf.h"

int my_test(void)
{

}

Test(comparison, 0)
{
	compare2(COMP_RET_BOTH, 1, printf, ft_printf, ("42"), ("42"));
	compare(COMP_RET_BOTH, 1, printf, ft_printf, ("42"));
}
