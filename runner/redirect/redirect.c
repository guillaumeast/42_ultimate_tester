#define __FUT_INSIDE__
#include "redirect_priv.h"
#include "file_priv.h"
#include "print_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

t_redirect g_output =
{
	.real_stdout_fd = STDOUT_FILENO,
	.real_stderr_fd = STDERR_FILENO,
	.activ = false,
	.mode = -1,
	.out_fd = -1,
	.out_file = NULL,
};

t_error	redirect_init(void)
{
	flush_all();
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	g_output.real_stdout_fd = dup(STDOUT_FILENO);
	if (g_output.real_stdout_fd == -1)
		return (REDIRECT_INIT_FAILED);
	g_output.real_stderr_fd = dup(STDERR_FILENO);
	if (g_output.real_stderr_fd == -1)
		return (REDIRECT_INIT_FAILED);
	return (NO_ERROR);
}

// TODO: don't fail if redirect already exists, juste store previous one and create a new one
t_error	redirect_start(t_redirect_mode mode)
{
	if (g_output.activ)
		return (ult_print_err("Unable to create redirection (another one already exists)"), false);
	if (mode != R_STDOUT && mode != R_STDERR && mode != R_BOTH)
		return (ult_print_err("Unable to create redirection (invalid mode %i)", mode), false);
	g_output.mode = mode;

	flush_all();
	if (!create_tmp_file())
		return (redirect_reset("unable to create temporary file"));
	if (g_output.mode != R_STDERR && dup2(g_output.out_fd, STDOUT_FILENO) == -1)
		return (redirect_reset("unable to switch file descriptors"));
	if (g_output.mode != R_STDOUT && dup2(g_output.out_fd, STDERR_FILENO) == -1)
		return (redirect_reset("unable to switch file descriptors"));
	
	setvbuf(g_output.out_file, NULL, _IONBF, 0);
	g_output.activ = true;
	return (true);
}

// TODO: return char * instead of t_string (Keep It Simple)
// TODO: refactor into smaller functions
t_string	*redirect_read()
{
	ssize_t		file_len;
	t_string	*res;
	size_t		nread;

	if (!g_output.activ)
		return (ult_print_err("Unable to read redirected output (no active redirection)"), NULL);
	flush_all();
	file_len = file_get_len(g_output.out_file);
	if (fseek(g_output.out_file, 0, SEEK_SET) != 0)
		return (ult_print_err("Unable to read redirected output\n"), NULL);
	if (file_len < 0)
		return (ult_print_err("Unable to read redirected output (unable to get file length)"), NULL);
	res = NULL;
	if (!(res = malloc(sizeof *res)) || !(res->data = malloc(file_len + 1)))
		return (free(res), ult_print_err("Unable to read redirected output (not enough memory)"), NULL);
	clearerr(g_output.out_file);
	res->len = 0;
	while (res->len < (size_t)file_len)
	{
		nread = fread(res->data + res->len, 1, file_len - res->len, g_output.out_file);
		res->len += nread;
		if (res->len == (size_t)file_len)
			break;
		if (nread == 0)
		{
			if (ferror(g_output.out_file))
				return (free(res->data), free(res), ult_print_err("Unable to read redirected output"), NULL);
			break; // EOF
		}
	}
	res->data[res->len] = '\0';
	if (ferror(g_output.out_file))
	{
		free(res->data);
		free(res);
		return (ult_print_err("Unable to read redirected output"), NULL);
	}
	res->data[res->len] = '\0';
	file_reset(g_output.out_file);
	return (res);
}

t_error	redirect_stop(void)
{
	t_error	error;

	error = NO_ERROR;
	if (!g_output.activ)
		return (error);

	g_output.activ = false;
	g_output.out_fd = -1;

	flush_all();
	if (dup2(g_output.real_stdout_fd, STDOUT_FILENO) == -1)
		error = REDIRECT_RESET_FAILED;
	if (dup2(g_output.real_stderr_fd, STDERR_FILENO) == -1)
		error = REDIRECT_RESET_FAILED;
	if (g_output.out_file)
	{
		if (fclose(g_output.out_file) != 0)
			error = REDIRECT_RESET_FAILED;
		g_output.out_file = NULL;
	}
	flush_all();
	
	return (error);
}
