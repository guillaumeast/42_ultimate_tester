#include "redirect_priv.h"
#include "fd_priv.h"
#include "file_priv.h"
#include "print_priv.h"
#include <stdlib.h>

bool	redirect_reset(const char *error_message);

t_redirect g_output =
{
	.real_stdout_fd = -1,
	.real_stderr_fd = -1,
	.activ = false,
	.mode = -1,
	.out_fd = -1,
	.out_file = NULL,
};

bool	redirect_init(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	g_output.real_stdout_fd = dup(STDOUT_FILENO);
	if (g_output.real_stdout_fd == -1)
		return (false);
	g_output.real_stderr_fd = dup(STDERR_FILENO);
	if (g_output.real_stderr_fd == -1)
		return (false);
	return (true);
}

bool	redirect_start(t_redirect_mode mode)
{
	if (g_output.activ)
		return (ult_err("Unable to create redirection (another one already exists)"), false);
	if (mode != R_STDOUT && mode != R_STDERR && mode != R_BOTH)
		return (ult_err("Unable to create redirection (invalid mode %i)", mode), false);

	flush_all();	// TODO: remove because already unbuffered or keep for safety ?
	if (!create_tmp_file())
		return (redirect_reset("unable to create temporary file"));
	if (!switch_file_descriptors())
		return (redirect_reset("unable to switch file descriptors"));

	setvbuf(g_output.out_file, NULL, _IONBF, 0);
	g_output.activ = true;
	return (true);
}

t_string	*redirect_read()
{
	ssize_t		file_len;
	t_string	*res;

	if (!g_output.activ)
		return (ult_err("Unable to read redirected output (no active redirection)"), NULL);
	flush_all();
	file_len = file_get_len(g_output.out_file);
	if (fseek(g_output.out_file, 0, SEEK_SET) != 0)
		return (ult_err("Unable to read redirected output\n"), NULL);
	if (file_len < 0)
		return (ult_err("Unable to read redirected output (unable to get file length)"), NULL);
	res = NULL;
	if (!(res = malloc(sizeof *res)) || !(res->data = malloc(file_len + 1)))
		return (free(res), ult_err("Unable to read redirected output (not enough memory)"), NULL);
	clearerr(g_output.out_file);
	res->len = fread(res->data, 1, file_len, g_output.out_file);
	if (ferror(g_output.out_file))
	{
		free(res->data);
		free(res);
		return (ult_err("Unable to read redirected output"), NULL);
	}
	res->data[res->len] = '\0';
	file_reset(g_output.out_file);
	return (res);
}

// Public
void	redirect_stop()
{
	redirect_reset(NULL);
}

// Private
bool	redirect_reset(const char *error_message)
{
	if (!g_output.activ)
		return (true);

	flush_all();
	g_output.activ = false;
	reset_file_descriptor(&g_output.real_stdout_fd, STDOUT_FILENO);
	reset_file_descriptor(&g_output.real_stderr_fd, STDERR_FILENO);
	if (g_output.out_file)
	{
		fclose(g_output.out_file);
		g_output.out_file = NULL;
	}
	g_output.out_fd = -1;
	if (error_message)
	{
		if (error_message[0])
	 		ult_err("Redirection aborted (%s)", error_message);
		else
		 	ult_err("Redirection aborted");
	}
	flush_all();
	return (false);
}
