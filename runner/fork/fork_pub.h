#ifndef ULT_FORK_PUB_H
# define ULT_FORK_PUB_H

# include <sys/types.h>

typedef struct s_fork_context
{
	size_t			timeout;
	pid_t			child_pid;
	int				sync_pipe[2];
	int				result_pipe[2];
}	t_context;

#endif
