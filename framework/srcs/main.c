# include "ultimate_tester.h"

static inline void	print_results();

size_t g_total = 0;
size_t g_passed = 0;
size_t g_failed = 0;
size_t g_timed_out = 0;
size_t g_crashed = 0;

void run_set(t_set *set);

int	main(void)
{
	t_set	*current_set;

    for (current_set = START_SET; current_set < STOP_SET; current_set++)
        run_set(current_set);
	print_results();
	return (0);
}

void	run_set(t_set *set)
{
	set_current_set(set);
	set->status = RUNNING;

	printf("→ Running test set: %s (timeout %zu)\n",
	       set->name, set->timeout);

	if (set->runner)
		set->runner();

	set->status = PASSED; // TODO: update at each test (as for run)
	set_current_set(NULL);
}

static inline void	print_results()
{
	const char *border_color = RED;
	const char *passed_color = GREY;
	const char *failed_color = GREY;
	const char *to_color = GREY;
	const char *crash_color = GREY;

	if (g_passed == g_total)
		passed_color = border_color = GREEN;
	else
	{
		if (g_failed > 0)	failed_color = RED;
		if (g_timed_out > 0)	to_color = RED;
		if (g_crashed > 0)	crash_color = RED;
	}
	printf("\n  %s┌------------------------------------┐%s\n", border_color, NONE);
	printf("  %s| %sPASSED%s | %sFAILED%s | %sTM-OUT%s | %sCRASHED%s |%s\n", \
		border_color, passed_color, border_color, failed_color, border_color, \
		to_color, border_color, crash_color, border_color, NONE);
	printf("  %s├------------------------------------┤%s\n", border_color, NONE);
	printf("  %s|%s ✔  %3ld %s", border_color, passed_color, g_passed, NONE);
	printf("%s|%s ✖  %3ld %s", border_color, failed_color, g_failed, NONE);
	printf("%s|%s ⊘  %3ld %s", border_color, to_color, g_timed_out, NONE);
	printf("%s|%s ☠  %3ld %s |%s\n", border_color, crash_color, g_crashed, border_color, NONE);
	printf("  %s└------------------------------------┘%s\n\n", border_color, NONE);
}
