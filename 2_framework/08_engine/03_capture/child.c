#define __FUT_INSIDE__
#include "capture_pub.h"
#include "messages_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

void	_capture_child(t_capture_res *res)
{
	size_t			len;
	t_message_type	type;

	message_send(g_context.pipe_to_parent, RETURN_VALUE, (t_message_data *)&res->ret);

	if (res->out)
	{
		type = CUSTOM;
		write(g_context.pipe_to_parent[1], &type, sizeof type);
		
		len = strlen(res->out);
		write(g_context.pipe_to_parent[1], &len, sizeof len);

		write(g_context.pipe_to_parent[1], res->out, len);
		free(res->out);
	}

	fork_cleanup();
	exit (EXIT_SUCCESS);
}
