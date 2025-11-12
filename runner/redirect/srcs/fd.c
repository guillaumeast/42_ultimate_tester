#include "file_priv.h"
#include "redirect_priv.h"
#include <unistd.h>

#define move_fd(from, to)	dup2(from, to)

bool	switch_file_descriptors(void)
{
	flush_all();
	if (g_output.mode != R_STDERR)
	{
		if (move_fd(g_output.out_fd, STDOUT_FILENO) == -1)
			return (false);
	}
	if (g_output.mode != R_STDOUT)
	{
		if (move_fd(g_output.out_fd, STDERR_FILENO) == -1)
			return (false);
	}
	return (true);
}

void	reset_file_descriptor(int *original_fd, int target_fd)
{
	move_fd(*original_fd, target_fd);
	close(*original_fd);
	*original_fd = -1;
}
