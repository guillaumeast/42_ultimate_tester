#ifndef ULT_SET_H
# define ULT_SET_H

# include <stddef.h>

typedef void (*t_test_fn)(void);

typedef enum e_status
{
	QUEUED,
	RUNNING,
	DONE,
}	t_status;

typedef struct s_set
{
	char		*name;
	size_t		timeout;
	t_status	status;
	t_test_fn	func;
}	t_set;

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

void	run_set(t_set *set);

#endif
