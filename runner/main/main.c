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

__attribute__((constructor))
static void	ult_main(void)
{
	t_set	*set;

	if (START_SET >= STOP_SET)
	{
		fprintf(stderr, "No tests to run\n");
		exit (0);
	}

	if (!redirect_init())
	{
		fprintf(stderr, "Error: Unable to initialize output redirection: please report this issue.");
		exit (1);
	}
	print_init_format();

    for (set = START_SET; set < STOP_SET; set++)
		run_set(set);
	redirect_stop();

	print_result(&g_result);
	exit (0);
}

__attribute__((weak))
int	main(void)
{
	fprintf(stderr, "This message should not appear: please report this issue.\n");
	return (0);
}
