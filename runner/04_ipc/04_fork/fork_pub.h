#ifndef ULT_FORK_PUB_H
#define ULT_FORK_PUB_H

#include <stdbool.h>
#include <sys/types.h>

typedef struct s_fork_context
{
	size_t	timeout;
	pid_t	child_pid;
	int		result_pipe[2];
	int		crash_infos_pipe[2];
}	t_context;

void	_fut_fork_init(t_context *context, size_t timeout);

#endif
