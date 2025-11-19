#ifndef ULT_PRINT_PUB_H
#define ULT_PRINT_PUB_H

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fstring, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fstring, ...);

#endif
