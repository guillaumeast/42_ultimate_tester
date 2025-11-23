#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_PRINT_INSIDE__
#include "redirect_io.h"
#undef __FUT_PRINT_INSIDE__
#undef __FUT_IO_INSIDE__
#undef __FUT_INSIDE__

#include <stdarg.h>

void	print_stdout(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(ULT_STDOUT, fmt, args);
	va_end(args);
}

void	print_stderr(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(ULT_STDERR, fmt, args);
	va_end(args);
}

// TODO: overwrite printf and fprintf to store user logs with h2 logs and print them at the end of the set
