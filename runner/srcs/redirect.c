#include "redirect.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Macros
#define cp_fd(fd) 			dup(fd)
#define move_fd(from, to)	dup2(from, to)

// Core methods
static inline bool		save_original_file_descriptors(void);
static inline bool		create_tmp_file(void);
static inline bool		switch_file_descriptors(void);
static inline bool		reset_output(const char *error_message);

// File helpers
static inline ssize_t	file_get_len(FILE *f);
static inline bool		file_reset(FILE *f);
static inline void		flush_all();

/*---------- PRIVATE STRUCT -----------*/

typedef struct s_redirect
{
	bool			activ;
	t_redirect_mode mode;
	int				original_stdout_fd;
	int				original_stderr_fd;
	FILE			*tmp_file;
	int				tmp_fd;
}	t_redirect;

static t_redirect r =
{
	.activ = false,
	.mode = R_NULL,
	.original_stdout_fd = -1,
	.original_stderr_fd = -1,
	.tmp_fd = -1,
	.tmp_file = NULL,
};

/*---------- PUBLIC METHODS -----------*/

bool	redirect_start(t_redirect_mode mode)
{
	if (r.activ)
		return (fprintf(stderr, "❗️ Unable to create redirection: another one already exists\n"), false);
	if (mode != R_STDOUT && mode != R_STDERR && mode != R_BOTH)
		return (fprintf(stderr, "❗️ Unable to create redirection: invalid mode %i\n", mode), false);

	flush_all();
	r.mode = mode;
	if (!save_original_file_descriptors())
		return (reset_output("unable to duplicate file descriptor"));
	if (!create_tmp_file())
		return (reset_output("unable to create temporary file"));
	if (!switch_file_descriptors())
		return (reset_output("unable to switch file descriptors"));

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(r.tmp_file, NULL, _IONBF, 0);

	r.activ = true;
	return (true);
}

t_string	*redirect_read()
{
	ssize_t		file_len;
	t_string	*res;

	if (!r.activ)
		return (fprintf(stderr, "❗️ Unable to read redirected output: no active redirection\n"), NULL);

	flush_all();
	file_len = file_get_len(r.tmp_file);
	if (fseek(r.tmp_file, 0, SEEK_SET) != 0)
		return (fprintf(stderr, "❗️ Unable to read redirected output\n"), NULL);
	if (file_len < 0)
		return (fprintf(stderr, "❗️ Unable to read redirected output: unable to get file length\n"), NULL);
	res = NULL;
	if (!(res = malloc(sizeof *res)) || !(res->data = malloc(file_len + 1)))
		return (free(res), fprintf(stderr, "❗️ Unable to read redirected output: not enough memory\n"), NULL);
	res->len = fread(res->data, 1, file_len, r.tmp_file);
	if (ferror(r.tmp_file))
	{
		free(res->data);
		free(res);
		return (fprintf(stderr, "❗️ Unable to read redirected output\n"), NULL);
	}
	res->data[res->len] = '\0';
	file_reset(r.tmp_file);
	return (res);
}

void	redirect_stop()
{
	reset_output(NULL);
}

/*---------- PRIVATE METHODS ----------*/

static inline bool	save_original_file_descriptors(void)
{
	if (r.mode != R_STDERR)
	{
		r.original_stdout_fd = dup(STDOUT_FILENO);
		if (r.original_stdout_fd == -1)
			return (false);
	}
	if (r.mode != R_STDOUT)
	{
		r.original_stderr_fd = dup(STDERR_FILENO);
		if (r.original_stderr_fd == -1)
			return (false);
	}
	return (true);
}

static inline bool		create_tmp_file(void)
{
	if (!(r.tmp_file = tmpfile()))
		return (false);
	r.tmp_fd = fileno(r.tmp_file);
	if (r.tmp_fd == -1)
		return (false);
	return (true);
}

static inline bool	switch_file_descriptors(void)
{
	flush_all();
	if (r.mode != R_STDERR)
	{
		if (move_fd(r.tmp_fd, STDOUT_FILENO) == -1)
			return (false);
	}
	if (r.mode != R_STDOUT)
	{
		if (move_fd(r.tmp_fd, STDERR_FILENO) == -1)
			return (false);
	}
	return (true);
}

static inline bool	reset_output(const char *error_message)
{
	flush_all();
	r.activ = false;
	r.mode = R_NULL;
	if (r.original_stdout_fd != -1)
	{
		move_fd(r.original_stdout_fd, STDOUT_FILENO);
		close(r.original_stdout_fd);
		r.original_stdout_fd = -1;
	}
	if (r.original_stderr_fd != -1)
	{
		move_fd(r.original_stderr_fd, STDERR_FILENO);
		close(r.original_stderr_fd);
		r.original_stderr_fd = -1;
	}
	if (r.tmp_file)
	{
		fclose(r.tmp_file);
		r.tmp_file = NULL;
	}
	r.tmp_fd = -1;
	if (error_message)
	{
		if (error_message[0])
	 		fprintf(stderr, "❗️ Redirection aborted: %s\n", error_message);
		else
		 	fprintf(stderr, "❗️ Redirection aborted\n");
	}
	return (false);
}

/*---------- PRIVATE HELPERS ----------*/

static inline ssize_t file_get_len(FILE *f)
{
	long	pos;
	ssize_t	len;

	pos = ftell(f);
	if (pos < 0)
		return (-1);
	if (fseek(f, 0, SEEK_END) != 0)
		return (-1);
	len = ftell(f);
	if (len < 0)
		return (-1);
	if (fseek(f, pos, SEEK_SET) != 0)
		return (-1);
	return (len);
}

static inline bool	file_reset(FILE *f)
{
	int	fd;

	fd = fileno(f);
	if (fd == -1)
		return (false);
	if (ftruncate(fd, 0) != 0)
		return (false);
	if (fseek(f, 0, SEEK_SET) != 0)
		return (false);
	clearerr(f);
	return (true);
}

static inline void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (r.tmp_file)
		fflush(r.tmp_file);
}
