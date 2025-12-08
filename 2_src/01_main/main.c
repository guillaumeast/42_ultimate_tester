#define __FUT_INSIDE__
#include "colors_priv.h"
#include "print_wrapper_pub.h"
#include "report_priv.h"
#include "set_priv.h"
#undef __FUT_INSIDE__

#include <stdio.h>
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

static void	print_start(void);

__attribute__((constructor))
static void	ult_main(void)
{
	t_set	*set;
	
	print_start();
	set_init((t_set *)START_SET, (t_set *)STOP_SET);

	for (set = START_SET; set < STOP_SET; set++)
		set_run(set);
	
	print_report(&g_result);

	exit(EXIT_SUCCESS);
}

__attribute__((weak))
int	main(void)
{
	return (0);
}

static void	print_start(void)
{
	print_stdout("\n   %s╭────────────────────────────────────────╮%s\n", CYAN, NONE);
	print_stdout("   %s│           %s42 ULTIMATE TESTER%s           │%s\n", CYAN, BBLUE, CYAN, NONE);
	print_stdout("   %s╰────────────────────────────────────────╯%s\n\n", CYAN, NONE);
}
