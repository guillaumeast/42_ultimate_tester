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

#define REDIRECT_STACK_SIZE 32

typedef struct s_saved_redirect
{
	FILE	*file;
	int		stdout_fd;
	int		stderr_fd;
}	t_saved_redirect;

void	redirect_cleanup(void);

static bool				s_redirect_initialized = false;
static size_t			s_redirect_stack_count = 0;
static t_saved_redirect	s_redirect_stack[REDIRECT_STACK_SIZE];

void	redirect_init(void)
{
	if (s_redirect_initialized == true)
		return ;

	atexit(redirect_cleanup);

	flush_all();
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	g_output.real_stdout_fd = dup(STDOUT_FILENO);
	exit_if(g_output.real_stdout_fd == -1, REDIRECT_INIT_FAILED);
	g_output.real_stderr_fd = dup(STDERR_FILENO);
	exit_if(g_output.real_stderr_fd == -1, REDIRECT_INIT_FAILED);
	
	s_redirect_initialized = true;
}

void	redirect_save(void)
{
	t_saved_redirect *saved;

	if (!g_output.activ)
		return ;
	exit_if(s_redirect_stack_count == REDIRECT_STACK_SIZE,REDIRECT_TOO_MANY_REDIRECTIONS);

	saved = &s_redirect_stack[s_redirect_stack_count];
	
	saved->file = g_output.out_file;
	saved->stdout_fd = dup(STDOUT_FILENO);
	saved->stderr_fd = dup(STDERR_FILENO);
	
	exit_if(saved->stdout_fd == -1 || saved->stderr_fd == -1, REDIRECT_SAVE_FAILED);
	s_redirect_stack_count++;
}

void	redirect_restore(void)
{
	t_saved_redirect	*saved;

	if (s_redirect_stack_count == 0)
		return ;

	s_redirect_stack_count--;
	saved = &s_redirect_stack[s_redirect_stack_count];

	g_output.out_file = saved->file;
	g_output.out_fd = fileno(saved->file);

	exit_if(dup2(saved->stdout_fd, STDOUT_FILENO) == -1, REDIRECT_RESTORE_FAILED);
	exit_if(dup2(saved->stderr_fd, STDERR_FILENO) == -1, REDIRECT_RESTORE_FAILED);
	close(saved->stdout_fd);
	close(saved->stderr_fd);

	g_output.activ = true;
}

void	redirect_cleanup(void)
{
	t_saved_redirect	*saved;

	if (g_output.real_stdout_fd != -1)
		close(g_output.real_stdout_fd);
	if (g_output.real_stderr_fd != -1)
		close(g_output.real_stderr_fd);
	if (g_output.out_file)
		fclose(g_output.out_file);

	while (s_redirect_stack_count > 0)
	{
		s_redirect_stack_count--;
		saved = &s_redirect_stack[s_redirect_stack_count];
		fclose(saved->file);
		close(saved->stdout_fd);
		close(saved->stderr_fd);
	}
}
