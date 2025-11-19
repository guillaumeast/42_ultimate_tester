#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_REDIRECT_INSIDE__
#include "redirect_internal.h"
#include "error_priv.h"
#include "file_priv.h"
#undef __FUT_REDIRECT_INSIDE__
#undef __FUT_IO_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

t_redirect	g_output =
{
	.real_stdout_fd = STDOUT_FILENO,
	.real_stderr_fd = STDERR_FILENO,
	.activ = false,
	.out_fd = -1,
	.out_file = NULL,
};

void	redirect_start(t_redirect_mode mode)
{
	exit_if(mode != R_STDOUT && mode != R_STDERR && mode != R_BOTH, REDIRECT_INVALID_MODE);

	redirect_init();
	redirect_save();

	flush_all();
	create_tmp_file();
	setvbuf(g_output.out_file, NULL, _IONBF, 0);

	if (mode != R_STDERR)
		exit_if(dup2(g_output.out_fd, STDOUT_FILENO) == -1, REDIRECT_START_FAILED);
	if (mode != R_STDOUT)
		exit_if(dup2(g_output.out_fd, STDERR_FILENO) == -1, REDIRECT_START_FAILED);
	
	g_output.activ = true;
}

char	*redirect_read()
{
	ssize_t	file_len;
	char	*res;

	if (!g_output.activ)
		return (NULL);

	flush_all();
	file_len = file_get_len(g_output.out_file);
	exit_if(file_len < 0, REDIRECT_READ_FAILED);
	exit_if(fseek(g_output.out_file, 0, SEEK_SET) != 0, REDIRECT_READ_FAILED);
	res = malloc(file_len + 1);
	exit_if(!res, REDIRECT_READ_NOT_ENOUGH_MEMORY);

	clearerr(g_output.out_file);
	file_nread(res, g_output.out_file, file_len);
	file_reset(g_output.out_file);

	return (res);
}

void	redirect_stop(void)
{
	if (!g_output.activ)
		return ;

	g_output.activ = false;
	flush_all();

	exit_if(dup2(g_output.real_stdout_fd, STDOUT_FILENO) == -1, REDIRECT_STOP_FAILED);
	exit_if(dup2(g_output.real_stderr_fd, STDERR_FILENO) == -1, REDIRECT_STOP_FAILED);
	if (g_output.out_file)
	{
		exit_if(fclose(g_output.out_file) != 0, REDIRECT_STOP_FAILED);
		g_output.out_fd = -1;
		g_output.out_file = NULL;
	}

	redirect_restore();
	flush_all();
}
