#include <stdio.h>
#define __FUT_INSIDE__
#include "global_priv.h"
#include "set_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>

#if defined(__APPLE__)
    extern t_set __data_ult_tester_start[] __asm("section$start$__DATA$__ult_tester");
    extern t_set __data_ult_tester_end[]   __asm("section$end$__DATA$__ult_tester");
    #define START_SET __data_ult_tester_start
    #define STOP_SET  __data_ult_tester_end
#else
    extern t_set __start_ult_tester;
    extern t_set __stop_ult_tester;
    #define START_SET  &__start_ult_tester
    #define STOP_SET   &__stop_ult_tester
#endif

__attribute__((constructor))
static void	ult_main(void)
{
	t_set	*set;
	
	print_start();
	for (set = START_SET; set < STOP_SET; set++)
		exit_if(!set_run(set));
	print_result(&g_result);

	exit(EXIT_SUCCESS);
}

__attribute__((weak))
int	main(void)
{
	return (0);
}
