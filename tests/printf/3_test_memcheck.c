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

void	worst_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	*nb = 5;
}

void just_timeout_dude(void)
{
	int	i = 0;

	(void)i;
	while (true)
		i++;
}

/* --------------------- TESTS --------------------- */

Test(correct, 0)
{
	memleaks(0, correct_func());
	memsafety(0, correct_func());
}

Test(no_free, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memsafety(0, no_free_func());
	memleaks(0, correct_func());
}

Test(unsafe, 0)
{
	memleaks(0, correct_func());
	memleaks(0, unsafe_func());
	memsafety(0, unsafe_func());
	memleaks(0, correct_func());
}

Test(both, 0)
{
	memleaks(0, correct_func());
	memleaks(0, worst_func());
	memsafety(0, worst_func());
	memleaks(0, correct_func());
}

Test(timeout_set, 2)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	just_timeout_dude();
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(crash_set, 0)
{
	int	*nul;

	nul = NULL;

	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	*nul = 5;
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(timeout_leaks, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memleaks(2, just_timeout_dude());
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(timeout_safety, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memsafety(2, just_timeout_dude());
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}
