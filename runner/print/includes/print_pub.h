#ifndef ULT_PRINT_PUB_H
# define ULT_PRINT_PUB_H

# include "redirect_pub.h"

void	ult_fprintf(t_ult_fd fd, const char *fmt, ...);

#define ult_print(fmt, ...) \
	ult_fprintf(ULT_STDOUT, fmt "%s", ##__VA_ARGS__, NONE)

#endif
