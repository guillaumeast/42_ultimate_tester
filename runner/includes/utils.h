#ifndef LIB_ULTIMATE_TESTER_UTILS_H
# define LIB_ULTIMATE_TESTER_UTILS_H

# include <stdbool.h>
# include <string.h>

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

static inline bool	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (!s1 && !s2);
	return (strcmp(s1, s2) == 0);
}

#endif
