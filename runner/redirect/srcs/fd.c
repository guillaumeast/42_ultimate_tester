#include "fd.h"
#include "file.h"
#include "redirect.h"
#include <unistd.h>

#define cp_fd(fd) 			dup(fd)
#define move_fd(from, to)	dup2(from, to)

extern t_redirect	current_redirect;

bool	save_original_file_descriptors(void)
{
	if (current_redirect.mode != R_STDERR)
	{
		current_redirect.real_stdout_fd = dup(STDOUT_FILENO);
		if (current_redirect.real_stdout_fd == -1)
			return (false);
	}
	if (current_redirect.mode != R_STDOUT)
	{
		current_redirect.real_stderr_fd = dup(STDERR_FILENO);
		if (current_redirect.real_stderr_fd == -1)
			return (false);
	}
	return (true);
}

bool	switch_file_descriptors(void)
{
	flush_all();
	if (current_redirect.mode != R_STDERR)
	{
		if (move_fd(current_redirect.out_fd, STDOUT_FILENO) == -1)
			return (false);
	}
	if (current_redirect.mode != R_STDOUT)
	{
		if (move_fd(current_redirect.out_fd, STDERR_FILENO) == -1)
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
