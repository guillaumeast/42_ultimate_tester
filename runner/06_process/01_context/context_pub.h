#ifndef ULT_CONTEXT_PUB_H
#define ULT_CONTEXT_PUB_H

#include <sys/types.h>

typedef struct s_context
{
	size_t	timeout;
	pid_t	child_pid;
	int		pipe[2];
}	t_context;

#endif
