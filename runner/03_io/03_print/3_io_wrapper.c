#define __FUT_INSIDE__
#define __FUT_PRINT_INSIDE__
#include "print_priv.h"
#include "redirect_priv.h"
#undef __FUT_PRINT_INSIDE__
#undef __FUT_INSIDE__

#include <stdio.h>
#include <stdarg.h>

static inline void	ult_fprintf(t_ult_fd fd, const char *fmt, va_list args);

void	print_stdout(const char *fstring, ...)
{
	va_list	args;

	va_start(args, fstring);
	ult_fprintf(ULT_STDOUT, fstring, args);
	va_end(args);
}

void	print_stderr(const char *fstring, ...)
{
	va_list	args;

	va_start(args, fstring);
	ult_fprintf(ULT_STDERR, fstring, args);
	va_end(args);
}

static inline void	ult_fprintf(t_ult_fd fd, const char *fmt, va_list args)
{
	int		target_fd;

	target_fd = (fd == ULT_STDOUT) 
		? g_output.real_stdout_fd
		: g_output.real_stderr_fd;

	dprintf(target_fd, "%s | %s", BLUE, NONE);
	vdprintf(target_fd, fmt, args);
}

void	print_raw_out(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(g_output.real_stdout_fd, fmt, args);
	va_end(args);
}

void	print_raw_err(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(g_output.real_stderr_fd, fmt, args);
	va_end(args);
}
