#ifndef LIB_ULTIMATE_TESTER_UTILS_H
# define LIB_ULTIMATE_TESTER_UTILS_H

# include <string.h>
# include "ult_types.h"

#define GREY "\033[90m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define NONE "\033[0m"

static inline bool	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (!s1 && !s2);
	return (strcmp(s1, s2) == 0);
}

#endif
