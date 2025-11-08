#include "test.h"
#include "iterate.h"

static const char *modifiers[] = { "", " ", "\t" };

void	iterate_no_arg(const char *format)
{
	char		format_iteration[512];
	size_t		i;

	run_test_no_arg(format);

	for (i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++)
	{
		snprintf(format_iteration, sizeof(format_iteration), "%s%s%s", modifiers[i], format, modifiers[i]);
		run_test_no_arg(format_iteration);
	}
}

void	iterate_on_string(const char *format, const char *arg)
{
	char		format_iteration[512];
	size_t		i;

	run_test_string(format, arg);
	if (!arg)
		return ;
	for (i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++)
	{
		snprintf(format_iteration, sizeof(format_iteration), "%s%s%s", modifiers[i], format, modifiers[i]);
		run_test_string(format_iteration, arg);
	}
}

void	iterate_on_long(const char *format, long arg)
{
	char		format_iteration[512];
	size_t		i;

	run_test_long(format, arg);

	for (i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++)
	{
		snprintf(format_iteration, sizeof(format_iteration), "%s%s%s", modifiers[i], format, modifiers[i]);
		run_test_long(format_iteration, arg);
	}
}

void	iterate_on_unsigned(const char *format, unsigned int arg)
{
	char		format_iteration[512];
	size_t		i;

	run_test_unsigned(format, arg);

	for (i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++)
	{
		snprintf(format_iteration, sizeof(format_iteration), "%s%s%s", modifiers[i], format, modifiers[i]);
		run_test_unsigned(format_iteration, arg);
	}
}

void	iterate_on_pointer(const char *format, void *arg)
{
	char		format_iteration[512];
	size_t		i;

	run_test_pointer(format, arg);

	for (i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++)
	{
		snprintf(format_iteration, sizeof(format_iteration), "%s%s%s", modifiers[i], format, modifiers[i]);
		run_test_pointer(format_iteration, arg);
	}
}
