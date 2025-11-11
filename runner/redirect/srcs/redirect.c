#include "redirect.h"
#include "fd.h"
#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_redirect current_redirect =
{
	.activ = false,
	.real_stdout_fd = STDOUT_FILENO,
	.real_stderr_fd = STDERR_FILENO,
	.out_fd = -1,
	.out_file = NULL,
};

// TODO: handle_error() function which check for utf-8 + colors and calls ult_fprintf()

bool	redirect_start(t_redirect_mode mode)
{
	if (current_redirect.activ)
		return (fprintf(stderr, "❗️ Unable to create redirection: another one already exists\n"), false);
	if (mode != R_STDOUT && mode != R_STDERR && mode != R_BOTH)
		return (fprintf(stderr, "❗️ Unable to create redirection: invalid mode %i\n", mode), false);

	flush_all();
	if (!save_original_file_descriptors())
		return (redirect_reset("unable to duplicate file descriptor"));
	if (!create_tmp_file())
		return (redirect_reset("unable to create temporary file"));
	if (!switch_file_descriptors())
		return (redirect_reset("unable to switch file descriptors"));

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(current_redirect.out_file, NULL, _IONBF, 0);

	current_redirect.activ = true;
	return (true);
}

t_string	*redirect_read()
{
	ssize_t		file_len;
	t_string	*res;

	if (!current_redirect.activ)
		return (fprintf(stderr, "❗️ Unable to read redirected output: no active redirection\n"), NULL);
	flush_all();
	file_len = file_get_len(current_redirect.out_file);
	if (fseek(current_redirect.out_file, 0, SEEK_SET) != 0)
		return (fprintf(stderr, "❗️ Unable to read redirected output\n"), NULL);
	if (file_len < 0)
		return (fprintf(stderr, "❗️ Unable to read redirected output: unable to get file length\n"), NULL);
	res = NULL;
	if (!(res = malloc(sizeof *res)) || !(res->data = malloc(file_len + 1)))
		return (free(res), fprintf(stderr, "❗️ Unable to read redirected output: not enough memory\n"), NULL);
	clearerr(current_redirect.out_file);
	res->len = fread(res->data, 1, file_len, current_redirect.out_file);
	if (ferror(current_redirect.out_file))
	{
		free(res->data);
		free(res);
		return (fprintf(stderr, "❗️ Unable to read redirected output\n"), NULL);
	}
	res->data[res->len] = '\0';
	file_reset(current_redirect.out_file);
	return (res);
}

bool	redirect_reset(const char *error_message)
{
	flush_all();
	current_redirect.activ = false;
	if (current_redirect.real_stdout_fd != -1)
		reset_file_descriptor(&current_redirect.real_stdout_fd, STDOUT_FILENO);
	if (current_redirect.real_stderr_fd != -1)
		reset_file_descriptor(&current_redirect.real_stderr_fd, STDERR_FILENO);
	if (current_redirect.out_file)
	{
		fclose(current_redirect.out_file);
		current_redirect.out_file = NULL;
	}
	current_redirect.out_fd = -1;
	if (error_message)
	{
		if (error_message[0])
	 		fprintf(stderr, "❗️ Redirection aborted: %s\n", error_message);
		else
		 	fprintf(stderr, "❗️ Redirection aborted\n");
	}
	flush_all();
	return (false);
}
