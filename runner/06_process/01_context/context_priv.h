#ifndef ULT_CONTEXT_PRIV_H
#define ULT_CONTEXT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>
#include <sys/types.h>

typedef struct s_context
{
	bool	has_parent;
	bool	has_child;
	pid_t	child_pid;
	size_t	child_timeout;
	int		pipe_to_parent[2];
	int		pipe_to_child[2];
}	t_context;

extern t_context	g_context;

#endif /* __FUT_INSIDE__ */

#endif /* ULT_CONTEXT_PRIV_H */
