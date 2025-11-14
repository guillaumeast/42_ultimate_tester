#include "print_priv.h"
#include "redirect_priv.h"
#include "set_priv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__)
    extern t_set __data_ult_tester_start[] __asm("section$start$__DATA$__ult_tester");
    extern t_set __data_ult_tester_end[]   __asm("section$end$__DATA$__ult_tester");
    # define START_SET __data_ult_tester_start
    # define STOP_SET  __data_ult_tester_end
#else
    extern t_set __start_ult_tester;
    extern t_set __stop_ult_tester;
    # define START_SET  &__start_ult_tester
    # define STOP_SET   &__stop_ult_tester
#endif

static inline void	init_context();

__attribute__((constructor))
static void	ult_main(void)
{
	t_error	error;
	t_set	*set;

	init_context();
	print_start();

    for (set = START_SET; set < STOP_SET; set++)
	{
		error = set_run(set);
		if (error == NO_ERROR)
			continue;
		ult_print_err_priv(error);
		exit(EXIT_FAILURE);
	}

	redirect_stop();
	print_result(&g_result);

	exit(EXIT_SUCCESS);
}

static inline void	init_context()
{
	if (!redirect_init())
	{
		fprintf(stderr, "Internal error. Please try again or report the issue.");
		exit (EXIT_FAILURE);
	}
	init_print_format();
	if (START_SET >= STOP_SET)
	{
		ult_print_err_priv(99);
		exit(EXIT_SUCCESS);
	}
}

__attribute__((weak))
int	main(void)
{
	fprintf(stderr, "This message should not appear: please report this issue.\n");
	return (0);
}
