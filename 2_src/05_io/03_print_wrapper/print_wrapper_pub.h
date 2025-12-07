#ifndef ULT_PRINT_WRAPPER_PUB_H
#define ULT_PRINT_WRAPPER_PUB_H

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fmt, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fmt, ...);

#endif
