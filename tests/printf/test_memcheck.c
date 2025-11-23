#include "ft_ultimate_tester.h"
#include "libftprintf.h"
#include <stdlib.h>

void	correct_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	if (!nb)
		return;
	*nb = 5;
	free(nb);
}

void	no_free_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	if (!nb)
		return;
	*nb = 5;
}

void	unsafe_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	*nb = 5;
	free(nb);
}

Test(correct, 0)
{
	memcheck(0, correct_func());
}

Test(no_free, 0)
{
	memcheck(0, no_free_func());
}

Test(unsafe, 0)
{
	memcheck(0, unsafe_func());
}
