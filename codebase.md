tree
```bash
42_ultimate_tester
├── 1_scripts
│   ├── install.sh
│   ├── uninstall.sh
│   └── update.sh
├── 2_src
│   ├── 01_main
│   │   └── main.c
│   ├── 02_error
│   │   ├── error_priv.h
│   │   ├── error.c
│   │   └── error.x
│   ├── 03_status
│   │   └── status_pub.h
│   ├── 04_result
│   │   ├── result_pub.h
│   │   └── result.c
│   ├── 05_io
│   │   ├── 01_file
│   │   │   ├── file_io.h
│   │   │   └── file.c
│   │   ├── 02_redirect
│   │   │   ├── 1_redirect_internal.c
│   │   │   ├── 2_redirect.c
│   │   │   ├── redirect_internal.h
│   │   │   ├── redirect_io.h
│   │   │   └── redirect_pub.h
│   │   ├── 03_print_wrapper
│   │   │   ├── print_wrapper_pub.h
│   │   │   └── print_wrapper.c
│   │   └── io_priv.h
│   ├── 06_process
│   │   ├── 01_context
│   │   │   ├── context_process.h
│   │   │   ├── context_pub.h
│   │   │   └── context.c
│   │   ├── 02_messages
│   │   │   ├── messages_priv.h
│   │   │   └── messages.c
│   │   ├── 03_stacktrace
│   │   │   ├── stacktrace_process.h
│   │   │   └── stacktrace.c
│   │   ├── 04_timeout
│   │   │   ├── timeout_priv.h
│   │   │   ├── timeout_process.h
│   │   │   └── timeout.c
│   │   ├── 05_fork
│   │   │   ├── fork_priv.h
│   │   │   ├── fork_pub.h
│   │   │   └── fork.c
│   │   ├── process_priv.h
│   │   └── process_pub.h
│   ├── 07_logs
│   │   ├── 01_colors
│   │   │   ├── colors_priv.h
│   │   │   ├── colors.c
│   │   │   └── colors.x
│   │   ├── 02_emojis
│   │   │   ├── emojis_priv.h
│   │   │   ├── emojis.c
│   │   │   └── emojis.x
│   │   ├── 03_format
│   │   │   ├── 1_format_basic.c
│   │   │   ├── 2_format_addr.c
│   │   │   ├── 3_format_status.c
│   │   │   ├── format_logs.h
│   │   │   ├── format_priv.h
│   │   │   └── format_pub.h
│   │   ├── 04_manager
│   │   │   ├── manager_priv.h
│   │   │   └── manager.c
│   │   ├── 05_send
│   │   │   ├── send_priv.h
│   │   │   └── send.c
│   │   ├── logs_priv.h
│   │   └── logs_pub.h
│   ├── 08_engine
│   │   ├── 01_set
│   │   │   ├── 1_set.c
│   │   │   ├── 2_set_parent.c
│   │   │   ├── 3_set_child.c
│   │   │   ├── set_internal.h
│   │   │   ├── set_priv.h
│   │   │   └── set_pub.h
│   │   ├── 02_memcheck
│   │   │   ├── 1_memcheck_table.c
│   │   │   ├── 2_memcheck_hooks.c
│   │   │   ├── 4_memcheck_parent.c
│   │   │   ├── 5_memcheck_child.c
│   │   │   ├── memcheck_int.h
│   │   │   └── memcheck_pub.h
│   │   ├── 03_capture
│   │   │   ├── capture_pub.h
│   │   │   ├── child.c
│   │   │   └── parent.c
│   │   ├── 04_compare
│   │   │   ├── compare_engine.h
│   │   │   └── compare.c
│   │   ├── 05_assert
│   │   │   ├── 1_assert.c
│   │   │   ├── 2_assert_eq.c
│   │   │   ├── 3_assert_neq.c
│   │   │   ├── assert_int.h
│   │   │   └── assert_pub.h
│   │   ├── engine_priv.h
│   │   └── engine_pub.h
│   └── 09_report
│       ├── report_priv.h
│       └── report.c
├── 3_include
│   └── fut.h
├── 4_tests
│   ├── 1_basics.c
│   ├── 1_structs.c
│   ├── 3_memcheck.c
│   ├── 4_redirect.c
│   └── 5_old.c
├── docs
│   ├── 0_get_started.md
│   ├── 1_set.md
│   ├── 2_redirections.md
│   ├── 3_assert.md
│   ├── 4_compare.md
│   └── README.md
├── Makefile
├── README.md
└── todo.md

33 directories, 94 files
```

./2_src/01_main/main.c
```c
#define __FUT_INSIDE__
#include "colors_priv.h"
#include "print_wrapper_pub.h"
#include "report_priv.h"
#include "set_priv.h"
#undef __FUT_INSIDE__

#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__)
    extern t_set __data_ult_tester_start[] __asm("section$start$__DATA$__ult_tester");
    extern t_set __data_ult_tester_end[]   __asm("section$end$__DATA$__ult_tester");
    #define START_SET __data_ult_tester_start
    #define STOP_SET  __data_ult_tester_end
#else
    extern t_set __start_ult_tester;
    extern t_set __stop_ult_tester;
    #define START_SET  &__start_ult_tester
    #define STOP_SET   &__stop_ult_tester
#endif

static void	print_start(void);

__attribute__((constructor))
static void	ult_main(void)
{
	t_set	*set;
	
	print_start();
	set_init((t_set *)START_SET, (t_set *)STOP_SET);

	for (set = START_SET; set < STOP_SET; set++)
		set_run(set);
	
	print_report(&g_result);

	exit(EXIT_SUCCESS);
}

__attribute__((weak))
int	main(void)
{
	return (0);
}

static void	print_start(void)
{
	print_stdout("\n   %s╭────────────────────────────────────────╮%s\n", CYAN, NONE);
	print_stdout("   %s│           %s42 ULTIMATE TESTER%s           │%s\n", CYAN, BBLUE, CYAN, NONE);
	print_stdout("   %s╰────────────────────────────────────────╯%s\n\n", CYAN, NONE);
}

```

./2_src/02_error/error_priv.h
```c
#ifndef ULT_ERROR_PRIV_H
#define ULT_ERROR_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>

typedef enum e_error
{
#define X_ERROR(name) name,
#include "error.x"
# undef X_ERROR
}	t_error;

void	error_log(t_error error);
void	error_reset_trace(void);
void	error_print_trace(void);
void	exit_if(bool condition, t_error error);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_ERROR_PRIV_H */

```

./2_src/02_error/error.c
```c
#define __FUT_INSIDE__
#include "error_priv.h"
#include "colors_priv.h"
#include "emojis_priv.h"
#include "print_wrapper_pub.h"
#undef __FUT_INSIDE__

#include <stdlib.h>

#define MAX_ERR_COUNT 256

static const char *error_names[] =
{
#define X_ERROR(name) #name,
#include "error.x"
# undef X_ERROR
};

static	t_error	s_error_trace[MAX_ERR_COUNT];
static	size_t	s_error_count = 0;

void	error_log(t_error error)
{
	if (error == NO_ERROR)
		return ;

	s_error_trace[s_error_count] = error;
	s_error_count++;
	exit_if(s_error_count == MAX_ERR_COUNT, TOO_MANY_ERRORS);
}

void	error_reset_trace(void)
{
	size_t	i;

	i = 0;
	while (i < s_error_count)
		s_error_trace[i++] = NO_ERROR;
	s_error_count = 0;
}

void	error_print_trace(void)
{
	int		i;
	t_error	error;

	if (s_error_count == 0)
		return ;

	i = s_error_count;
	while(--i >= 0)
	{
		error = s_error_trace[i];
		print_stderr(" %s%s %s%s", YELLOW, EMJ_ARW_RIGHT, error_names[error], NONE);
	}
}

void	exit_if(bool condition, t_error error)
{
	if (!condition)
		return ;

	error_log(error);
	print_stderr(" %s%s Internal error%s", RED, EMJ_ERR, NONE);
	error_print_trace();
	print_stderr("%s Please try again or report the issue%s\n", GREY, NONE);

	exit(100 + error);
}

```

./2_src/03_status/status_pub.h
```c
#ifndef ULT_STATUS_PUB_H
#define ULT_STATUS_PUB_H

#include <stddef.h>

#define STATUS_BUFFER_SIZE 32

typedef enum e_status_type
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	LEAKED,
	DONE,	
}	t_status_type;

typedef struct s_status
{
	t_status_type	type;
	int				sig;
	void			*crash_address;
	size_t			timeout;
}	t_status;

#endif /* ULT_STATUS_PUB_H */

```

./2_src/04_result/result_pub.h
```c
#ifndef ULT_RESULT_PRIV_H
#define ULT_RESULT_PRIV_H

#include "status_pub.h"
#include <stddef.h>

typedef struct s_result
{
	t_status	status;
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
	size_t		leaks;
}	t_result;

void	result_compute(t_result *res);
void	result_add(const t_result *from, t_result *to);

#endif /* ULT_RESULT_PRIV_H */

```

./2_src/04_result/result.c
```c
#define __FUT_INSIDE__
#include "result_pub.h"
#undef __FUT_INSIDE__

void	result_compute(t_result *res)
{
	res->total = res->passed + res->failed + res->timed + res->crashed + res->leaks;

	if (res->passed == res->total)
		res->status.type = PASSED;
	else if (res->failed > 0)
		res->status.type = FAILED;
	else if (res->timed > 0)
		res->status.type = TIMED;
	else if (res->crashed > 0)
		res->status.type = CRASHED;
	else if (res->leaks > 0)
		res->status.type = LEAKED;
}

void	result_add(const t_result *from, t_result *to)
{
	to->passed += from->passed;
	to->failed += from->failed;
	to->timed += from->timed;
	to->crashed += from->crashed;
	to->leaks += from->leaks;

	result_compute(to);
}

```

./2_src/05_io/01_file/file_io.h
```c
#ifndef ULT_FILE_IO_H
#define ULT_FILE_IO_H

#ifndef __FUT_IO_INSIDE__
/*
**  Private header for the io subsystem.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>
#include <stdio.h>

void	create_tmp_file(void);
size_t	file_get_len(FILE *file);
void	file_nread(char *buffer, FILE *file, size_t n);
void	file_reset(FILE *file);
void	flush_all();

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FILE_IO_H */

```

./2_src/05_io/01_file/file.c
```c
#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#include "file_io.h"
#include "error_priv.h"
#include "redirect_io.h"
#undef __FUT_IO_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

void	create_tmp_file(void)
{
	exit_if(!(g_output.out_file = tmpfile()), FILE_CREATION_FAILED);
	g_output.out_fd = fileno(g_output.out_file);
}

size_t file_get_len(FILE *file)
{
	long	position;
	ssize_t	len;

	position = ftell(file);
	exit_if(position < 0, FILE_LEN_FAILED);
	exit_if(fseek(file, 0, SEEK_END) != 0, FILE_LEN_FAILED);
	len = ftell(file);
	exit_if(len < 0, FILE_LEN_FAILED);
	exit_if(fseek(file, position, SEEK_SET) != 0, FILE_LEN_FAILED);
	return ((size_t)len);
}

void	file_nread(char *buffer, FILE *file, size_t n)
{
	size_t	res_len;
	size_t	nread;

	res_len = 0;
	while (res_len < n)
	{
		nread = fread(buffer + res_len, 1, n - res_len, file);
		if (ferror(file))
		{
			free(buffer);
			exit_if(true, REDIRECT_READ_FAILED);
		}
		if (nread == 0)
			break;
		res_len += (ssize_t)nread;
	}
	buffer[res_len] = '\0';
}

void	file_reset(FILE *file)
{
	int	fd;

	fd = fileno(file);
	exit_if(fd == -1, FILE_RESET_FAILED);
	exit_if(ftruncate(fd, 0) != 0, FILE_RESET_FAILED);
	exit_if(fseek(file, 0, SEEK_SET) != 0, FILE_RESET_FAILED);
	clearerr(file);
}

void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (g_output.activ)
		fflush(g_output.out_file);
}

```

./2_src/05_io/02_redirect/1_redirect_internal.c
```c
#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_REDIRECT_INSIDE__
#include "redirect_internal.h"
#include "error_priv.h"
#include "file_io.h"
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

```

./2_src/05_io/02_redirect/2_redirect.c
```c
#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_REDIRECT_INSIDE__
#include "redirect_internal.h"
#include "error_priv.h"
#include "file_io.h"
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
	exit_if(!res, NOT_ENOUGH_MEMORY);

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

```

./2_src/05_io/02_redirect/redirect_internal.h
```c
#ifndef ULT_REDIRECT_INTERNAL_H
#define ULT_REDIRECT_INTERNAL_H

#ifndef __FUT_REDIRECT_INSIDE__
/*
**  Internal header for the redirect module.
**  Not available outside its compilation unit.
*/
#else

#include "redirect_io.h"

void	redirect_init(void);
void	redirect_save(void);
void	redirect_restore(void);

#endif /* __FUT_REDIRECT_INSIDE__ */

#endif /* ULT_REDIRECT_INTERNAL_H */

```

./2_src/05_io/02_redirect/redirect_io.h
```c
#ifndef ULT_REDIRECT_PRIV_H
#define ULT_REDIRECT_PRIV_H

#ifndef __FUT_IO_INSIDE__
/*
**  Private header for the IO subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "redirect_pub.h"
#include <stdio.h>

typedef enum e_ult_fds
{
	ULT_STDOUT,
	ULT_STDERR,
}	t_ult_fd;

typedef struct s_redirect
{
	bool			activ;
	int				real_stdout_fd;
	int				real_stderr_fd;
	FILE			*out_file;
	int				out_fd;
}	t_redirect;

extern t_redirect	g_output;

#endif /* __FUT_INSIDE__ */

#endif /* ULT_REDIRECT_PRIV_H */

```

./2_src/05_io/02_redirect/redirect_pub.h
```c
#ifndef ULT_REDIRECT_PUB_H
#define ULT_REDIRECT_PUB_H

#include <stdbool.h>
#include <stddef.h>

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH
}	t_redirect_mode;

void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#define get_output(mode, expr, out_var_name)	\
	do											\
	{											\
		redirect_start(mode);					\
		expr;									\
		out_var_name = redirect_read();			\
		redirect_stop();						\
	} while (0)

#endif

```

./2_src/05_io/03_print_wrapper/print_wrapper_pub.h
```c
#ifndef ULT_PRINT_WRAPPER_PUB_H
#define ULT_PRINT_WRAPPER_PUB_H

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fmt, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fmt, ...);

#endif

```

./2_src/05_io/03_print_wrapper/print_wrapper.c
```c
#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_PRINT_INSIDE__
#include "redirect_io.h"
#undef __FUT_PRINT_INSIDE__
#undef __FUT_IO_INSIDE__
#undef __FUT_INSIDE__

#include <stdarg.h>

void	print_stdout(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(g_output.real_stdout_fd, fmt, args);
	va_end(args);
}

void	print_stderr(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vdprintf(g_output.real_stderr_fd, fmt, args);
	va_end(args);
}

// TODO: overwrite printf and fprintf to store user logs with h2 logs and print them at the end of the set

```

./2_src/05_io/io_priv.h
```c
#ifndef ULT_IO_PUB_H
#define ULT_IO_PUB_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "redirect_pub.h"
#include "print_wrapper_pub.h"

#endif /* __FUT_INSIDE__ */

#endif /* ULT_IO_PUB_H */

```

./2_src/06_process/01_context/context_process.h
```c
#ifndef ULT_CONTEXT_PROCESS_H
#define ULT_CONTEXT_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "context_pub.h"
#include <signal.h>

extern volatile sig_atomic_t	g_handlers_target_pid;

void	context_init(void);
void	context_set_target_pid(pid_t target_pid);
void	context_init_sigint_handler(void);
void	context_cancel_sigint_handler(void);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_CONTEXT_PROCESS_H */

```

./2_src/06_process/01_context/context_pub.h
```c
#ifndef ULT_CONTEXT_PRIV_H
#define ULT_CONTEXT_PRIV_H

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

#endif

```

./2_src/06_process/01_context/context.c
```c
#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_pub.h"
#include "error_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <stddef.h>
#include <signal.h>

static void	sigint_handler(int sig);

t_context				g_context;
volatile sig_atomic_t	g_handlers_target_pid = -1;

void	context_init(void)
{
	g_context.has_parent = false;
	g_context.has_child = false;
	g_context.child_pid = -1;
	g_context.child_timeout = -1;
	g_context.pipe_to_parent[0] = -1;
	g_context.pipe_to_parent[1] = -1;
	g_context.pipe_to_child[0] = -1;
	g_context.pipe_to_child[1] = -1;
}

void	context_set_target_pid(pid_t target_pid)
{
	g_handlers_target_pid = (sig_atomic_t)target_pid;
}

void	context_init_sigint_handler(void)
{
	struct sigaction	new_action = {0};

	exit_if(sigemptyset(&new_action.sa_mask) == -1, SIGINT_HANDLER_SET_FAILED);
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = sigint_handler;
	exit_if(sigaction(SIGINT, &new_action, NULL) == -1, SIGINT_HANDLER_SET_FAILED);
}

void	context_cancel_sigint_handler(void)
{
	struct sigaction action = {0};
	
	action.sa_handler = SIG_DFL;
	exit_if(sigaction(SIGINT, &action, NULL) == -1, SIGINT_HANDLER_CANCEL_FAILED);
}

static void	sigint_handler(int sig)
{
	(void)sig;

	signal(SIGINT, SIG_IGN);
	if (g_handlers_target_pid != -1)
    	kill((pid_t)g_handlers_target_pid, SIGKILL);

	signal(sig, SIG_DFL);
	raise(sig);
}

```

./2_src/06_process/02_messages/messages_priv.h
```c
#ifndef ULT_MESSAGES_PRIV_H
#define ULT_MESSAGES_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "context_process.h"
#include "logs_priv.h"
#include "result_pub.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum e_message_type
{
	CUSTOM,
	RETURN_VALUE,
	RESULT,
	CRASH,
	LOG
}	t_message_type;

typedef union u_message_data
{
	intptr_t	ret_value;
	t_result	result;
	void		*crash_addr;
	char		log[H2_CAP];
}	t_message_data;

typedef struct s_message
{
	t_message_type	type;
	t_message_data	data;
}	t_message;

void	message_send(int pipe[2], t_message_type type, t_message_data *data);
bool	message_receive(int pipe[2], t_message *buff);
bool	message_read_type(int pipe[2], t_message_type *buff);
bool	message_read_len(int pipe[2], size_t *buff);
bool	message_read_data(int pipe[2], void *buff, size_t len);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_MESSAGES_PRIV_H */

```

./2_src/06_process/02_messages/messages.c
```c
#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <string.h>
#include <unistd.h>

static inline bool	read_complete(int fd, void *buff, size_t message_size);

void	message_send(int pipe[2], t_message_type type, t_message_data *data)
{
	size_t	len;

	len = 0;
	switch (type)
	{
		case RETURN_VALUE:	len = sizeof(intptr_t); break;
		case RESULT:		len = sizeof(t_result); break;
		case CRASH:			len = sizeof(void *); break;
		case LOG:			len = strlen((char *)data); break;
		default:			exit_if(true, MESSAGE_UNKNOWN_TYPE);
	}
	exit_if(len >= sizeof(t_message_data), MESSAGE_TOO_LONG);

	(void)write(pipe[1], &type, sizeof type);
	(void)write(pipe[1], &len, sizeof len);
	(void)write(pipe[1], data, len);
}

bool	message_receive(int pipe[2], t_message *buff)
{
	size_t	len;

	if (!read_complete(pipe[0], &buff->type, sizeof buff->type))
		return (false);
	if (!read_complete(pipe[0], &len, sizeof len))
		return (false);
	switch (buff->type)
	{
		case RETURN_VALUE:
			exit_if(len != sizeof(intptr_t), MESSAGE_INVALID_LEN);
			break;
		case RESULT:
			exit_if(len != sizeof(t_result), MESSAGE_INVALID_LEN);
			break;
		case CRASH:
			exit_if(len != sizeof(void *), MESSAGE_INVALID_LEN);
			break;
		case LOG:
			exit_if(len >= sizeof(t_message_data), MESSAGE_INVALID_LEN);
			break;
		default:
			exit_if(true, MESSAGE_UNKNOWN_TYPE);
	}
	if (!read_complete(pipe[0], &buff->data, len))
		return (false);
	if (buff->type == LOG)
		buff->data.log[len] = '\0';
	return (true);
}

bool	message_read_type(int pipe[2], t_message_type *buff)
{
	return (read_complete(pipe[0], buff, sizeof *buff));
}

bool	message_read_len(int pipe[2], size_t *buff)
{
	return (read_complete(pipe[0], buff, sizeof *buff));
}

bool	message_read_data(int pipe[2], void *buff, size_t len)
{
	return (read_complete(pipe[0], buff, len));
}

static inline bool	read_complete(int fd, void *buff, size_t message_size)
{
	ssize_t	bytes;
	size_t	total;

	total = 0;
	while (total < message_size)
	{
		bytes = read(fd, (char *)buff + total, message_size - total);
		if (bytes == 0 && total == 0)
			return (false);
		else if (bytes == 0)
			exit_if(true, PIPE_CLOSED_EARLY);
		else if (bytes < 0 && errno == EINTR)
			continue;
		exit_if(bytes < 0, PIPE_READ_FAILED);
		total += (size_t)bytes;
	}
	return (true);
}

```

./2_src/06_process/03_stacktrace/stacktrace_process.h
```c
#ifndef ULT_STACKTRACE_PROCESS_H
#define ULT_STACKTRACE_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

void	stacktrace_init(int fd_to_parent);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_STACKTRACE_PROCESS_H */

```

./2_src/06_process/03_stacktrace/stacktrace.c
```c
#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "messages_priv.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__


#include <signal.h>
#include <stddef.h>
#include <unistd.h>

#if defined(__APPLE__)
#include <sys/ucontext.h>
#else
#include <ucontext.h>
#endif

#if defined(__APPLE__) && defined(__x86_64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext->__ss.__rip)
#elif defined(__APPLE__) && defined(__aarch64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext->__ss.__pc)
#elif defined(__linux__) && defined(__x86_64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.gregs[REG_RIP])
#elif defined(__linux__) && defined(__i386__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.gregs[REG_EIP])
#elif defined(__linux__) && defined(__riscv)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.sc_pc)
#elif defined(__linux__) && defined(__aarch64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.pc)
#elif defined(__linux__) && defined(__powerpc64__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.regs->nip)
#elif defined(__linux__) && defined(__powerpc__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.regs->nip)
#elif defined(__linux__) && defined(__s390x__)
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.psw.addr)
#elif defined(__linux__) && (defined(__arm__) || defined(__ARM_ARCH))
	#define GET_PROGRAM_COUNTER(ctx) ((void *)(ctx)->uc_mcontext.arm_pc)
#else
	#define GET_PROGRAM_COUNTER(ctx) ((void *)0)
#endif

static volatile sig_atomic_t	s_fd_to_parent = -1;

static void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext);

void	stacktrace_init(int fd_to_parent)
{
	struct sigaction	action = {0};

	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = stacktrace_handler;
	sigemptyset(&action.sa_mask);

	sigaction(SIGSEGV, &action, NULL);
	sigaction(SIGBUS, &action, NULL);
	sigaction(SIGFPE,  &action, NULL);
	sigaction(SIGILL, &action, NULL);
	sigaction(SIGABRT, &action, NULL);

	s_fd_to_parent = (sig_atomic_t)fd_to_parent;
}

static void	stacktrace_handler(int sig, siginfo_t *info, void *ucontext)
{
	ucontext_t		*proc_context;
	void			*program_counter;
	t_message_type	type;
	size_t			len;

	(void)sig;
	(void)info;

	proc_context = (ucontext_t *)ucontext;
	program_counter = GET_PROGRAM_COUNTER(proc_context);

	if (s_fd_to_parent != -1)
	{
		type = CRASH;
		len = sizeof program_counter;
		(void)write(s_fd_to_parent, &type, sizeof type);
		(void)write(s_fd_to_parent, &len, sizeof len);
		(void)write(s_fd_to_parent, &program_counter, len);
	}

	signal(sig, SIG_DFL);
	raise(sig);
}

```

./2_src/06_process/04_timeout/timeout_priv.h
```c
#ifndef ULT_TIMEOUT_PRIV_H
#define ULT_TIMEOUT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>

bool	timeout_is_triggered(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */

```

./2_src/06_process/04_timeout/timeout_process.h
```c
#ifndef ULT_TIMEOUT_PROCESS_H
#define ULT_TIMEOUT_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

void	timeout_init(size_t timeout);
void	timeout_start(void);
void	timeout_cancel(void);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_TIMEOUT_PROCESS_H */

```

./2_src/06_process/04_timeout/timeout.c
```c
#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_process.h"
#include "error_priv.h"
#include "timeout_process.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <unistd.h>

static void	timeout_handler(int sig);

static bool				active = false;
volatile sig_atomic_t	g_timeout_triggered = (sig_atomic_t)false;

void	timeout_init(size_t timeout)
{
	g_context.child_timeout = timeout;
}

void	timeout_start(void)
{
	struct sigaction	new_action = {0};

	if (g_context.child_timeout == 0)
		return ;

	g_timeout_triggered = false;

	exit_if(sigemptyset(&new_action.sa_mask) == -1, ALARM_SET_FAILED);
	new_action.sa_flags = SA_RESETHAND;
	new_action.sa_handler = timeout_handler;
	exit_if(sigaction(SIGALRM, &new_action, NULL) == -1, ALARM_SET_FAILED);

	(void)alarm(g_context.child_timeout);
	active = true;
}

void	timeout_cancel(void)
{
	struct sigaction action = {0};

	g_timeout_triggered = false;
	if (active == false)
		return ;

	action.sa_handler = SIG_DFL;
	exit_if(sigaction(SIGALRM, &action, NULL) == -1, ALARM_CANCEL_FAILED);
	(void)alarm(0);

	active = false;
	g_context.child_timeout = -1;
}

bool	timeout_is_triggered(void)
{
	return ((bool)g_timeout_triggered);
}

static void	timeout_handler(int sig)
{
	(void)sig;
	
	if (g_handlers_target_pid != -1)
    	kill((pid_t)g_handlers_target_pid, SIGKILL);

	g_timeout_triggered = true;
	g_handlers_target_pid = -1;
}

```

./2_src/06_process/05_fork/fork_priv.h
```c
#ifndef ULT_FORK_PRIV_H
#define ULT_FORK_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "fork_pub.h"

void	fork_cleanup(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORK_PRIV_H */

```

./2_src/06_process/05_fork/fork_pub.h
```c
#ifndef ULT_FORK_PUB_H
#define ULT_FORK_PUB_H

#include <stddef.h>

void	_fork_init(size_t timeout);

#endif

```

./2_src/06_process/05_fork/fork.c
```c
#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_process.h"
#include "error_priv.h"
#include "fork_priv.h"
#include "stacktrace_process.h"
#include "timeout_process.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

static size_t		s_fork_depth = 0;

static inline void	fork_init_parent(t_context *prev_context, int new_pipe[2], int sync_pipe[2]);
static inline void	fork_init_child(int new_pipe[2], int sync_pipe[2]);

void	_fork_init(size_t timeout)
{
	t_context	previous_context;
	int			new_pipe[2];
	int			sync_pipe[2];

	previous_context = g_context;
	context_init();

	exit_if(pipe(new_pipe) == -1, PIPE_CREATION_FAILED);
	exit_if(pipe(sync_pipe) == -1, PIPE_CREATION_FAILED);
	timeout_init(timeout);

	g_context.child_pid = fork();
	exit_if(g_context.child_pid < 0, FORK_FAILED);
	
	if (g_context.child_pid > 0)
		fork_init_parent(&previous_context, new_pipe, sync_pipe);
	else
	 	fork_init_child(new_pipe, sync_pipe);

	close(sync_pipe[0]);
	close(sync_pipe[1]);
}

static inline void	fork_init_parent(t_context *prev_context, int new_pipe[2], int sync_pipe[2])
{
	bool	ready;

	if (s_fork_depth == 0)
	{
		context_set_target_pid(-g_context.child_pid);
		context_init_sigint_handler();
	}
	else
		context_set_target_pid(g_context.child_pid);

	g_context.has_parent = prev_context->has_parent;
	g_context.has_child = true;
	if (g_context.has_parent)
	{
		g_context.pipe_to_parent[0] = prev_context->pipe_to_parent[0];
		g_context.pipe_to_parent[1] = prev_context->pipe_to_parent[1];
	}
	g_context.pipe_to_child[0] = new_pipe[0];
	g_context.pipe_to_child[1] = new_pipe[1];

	timeout_start();
	ready = true;
	write(sync_pipe[1], &ready, sizeof ready);
	close(g_context.pipe_to_child[1]);
	g_context.pipe_to_child[1] = -1;
}

static inline void	fork_init_child(int new_pipe[2], int sync_pipe[2])
{
	bool	ready;

	s_fork_depth++;
	if (s_fork_depth == 1)
		setpgid(0, 0);

	g_context.has_parent = true;
	g_context.has_child = false;
	g_context.pipe_to_parent[0] = new_pipe[0];
	g_context.pipe_to_parent[1] = new_pipe[1];

	stacktrace_init(g_context.pipe_to_parent[1]);

	read(sync_pipe[0], &ready, sizeof ready);
	close(g_context.pipe_to_parent[0]);
	g_context.pipe_to_parent[0] = -1;
}

void	fork_cleanup(void)
{
	timeout_cancel();

	if (g_context.has_child == false)
	{
		close(g_context.pipe_to_parent[1]);
		g_context.pipe_to_parent[1] = -1;
	}
	if (g_context.has_child)
	{
		close(g_context.pipe_to_child[0]);
		g_context.pipe_to_child[0] = -1;
	}

	g_context.has_child = false;
	if (s_fork_depth == 0)
		context_cancel_sigint_handler();
}

```

./2_src/06_process/process_priv.h
```c
#ifndef ULT_PROCESS_PRIV_H
#define ULT_PROCESS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "process_pub.h"
#include "messages_priv.h"
#include "timeout_priv.h"
#include "fork_priv.h"
#include "timeout_priv.h"

#endif /* __FUT_INSIDE__ */

#endif /* ULT_PROCESS_PRIV_H */

```

./2_src/06_process/process_pub.h
```c
#ifndef ULT_PROCESS_PUB_H
#define ULT_PROCESS_PUB_H

#include "context_pub.h"
#include "fork_pub.h"

#endif

```

./2_src/07_logs/01_colors/colors_priv.h
```c
#ifndef ULT_COLORS_PRIV_H
#define ULT_COLORS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

/* Generate colors getter prototypes */
#define X_COLOR(color_name)	const char *colors_get_##color_name(void);
#include "colors.x"
#undef X_COLOR

#define GREY	colors_get_grey()
#define RED		colors_get_red()
#define BRED	colors_get_bred()
#define GREEN	colors_get_green()
#define BGREEN	colors_get_bgreen()
#define YELLOW	colors_get_yellow()
#define BLUE	colors_get_blue()
#define BBLUE	colors_get_bblue()
#define CYAN	colors_get_cyan()
#define NONE	colors_get_none()

#endif /* __FUT_INSIDE__ */

#endif /* ULT_COLORS_PRIV_H */

```

./2_src/07_logs/01_colors/colors.c
```c
#include <stdbool.h>
#include <unistd.h>

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*bred;
	char	*green;
	char	*bgreen;
	char	*yellow;
	char	*blue;
	char	*bblue;
	char	*cyan;
	char	*none;
}	t_colors;

static t_colors	g_colors;
static bool		s_colors_initialized = false;

static inline void	colors_init(void);

// Generate getters
#define X_COLOR(color_name)							\
    const char *colors_get_##color_name(void)		\
	{												\
        if (!s_colors_initialized) colors_init();	\
        return g_colors.color_name;					\
    }
#include "colors.x"
#undef X_COLOR

static inline void	colors_init(void)
{
	bool		istty;

	istty = isatty(STDOUT_FILENO);
	g_colors.grey =		istty ? "\033[0;90m" : "";
	g_colors.red =		istty ? "\033[0;31m" : "";
	g_colors.bred =		istty ? "\033[1;31m" : "";
	g_colors.green =	istty ? "\033[0;32m" : "";
	g_colors.bgreen =	istty ? "\033[1;32m" : "";
	g_colors.yellow =	istty ? "\033[0;33m" : "";
	g_colors.blue =		istty ? "\033[0;34m" : "";
	g_colors.bblue =	istty ? "\033[1;34m" : "";
	g_colors.cyan =		istty ? "\033[1;36m" : "";
	g_colors.none =		istty ? "\033[0m" : "";
	s_colors_initialized = true;
}

```

./2_src/07_logs/02_emojis/emojis_priv.h
```c
#ifndef ULT_EMOJIS_PRIV_H
#define ULT_EMOJIS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

/* Generate emojis getter prototypes */
#define X_EMOJI(emoji_name)	\
    const char *emojis_get_##emoji_name(void);
#include "emojis.x"
#undef X_EMOJI

#define EMJ_ARW_DR		emojis_get_arrow_down_right()
#define EMJ_ARW_RIGHT	emojis_get_arrow_right()
#define EMJ_PASS		emojis_get_passed()
#define EMJ_FAIL		emojis_get_failed()
#define EMJ_TIMD		emojis_get_timed()
#define EMJ_CRSH		emojis_get_crashed()
#define EMJ_LEAK		emojis_get_leaked()
#define EMJ_ERR			emojis_get_error()
#define EMJ_TEST		emojis_get_test()
#define EMJ_SUC_START	emojis_get_success_title_start()
#define EMJ_SUC_END		emojis_get_success_title_end()
#define EMJ_FAIL_START	emojis_get_fail_title_start()
#define EMJ_FAIL_END	emojis_get_fail_title_end()

#endif /* __FUT_INSIDE__ */

#endif /* ULT_EMOJIS_PRIV_H */

```

./2_src/07_logs/02_emojis/emojis.c
```c
#include <locale.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_emojis
{
	char	*arrow_down_right;
	char	*arrow_right;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed;
	char	*leaked;
	char	*error;
	char	*test;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

static t_emojis	g_emojis;
static bool		s_emojis_initialized = false;

static inline void	emojis_init(void);

// Generate getters
#define X_EMOJI(emoji_name)							\
    const char *emojis_get_##emoji_name(void)		\
	{												\
        if (!s_emojis_initialized) emojis_init();	\
        return g_emojis.emoji_name;					\
    }
#include "emojis.x"
#undef X_EMOJI

static inline void	emojis_init(void)
{
	bool		isutf8;
	const char	*locale;

	setlocale(LC_CTYPE, "");
	locale = setlocale(LC_CTYPE, NULL);
	isutf8 = locale && strstr(locale, "UTF-8");
	g_emojis.arrow_down_right =			isutf8 ? "⤷" : "> ";
	g_emojis.arrow_right =				isutf8 ? "➜" : "> ";
	g_emojis.passed =					isutf8 ? "✔" : "V ";
	g_emojis.failed =					isutf8 ? "✖" : "X ";
	g_emojis.timed =					isutf8 ? "❄" : "T ";
	g_emojis.crashed =					isutf8 ? "☠" : "C ";
	g_emojis.leaked =					isutf8 ? "◍" : "L ";
	g_emojis.error =					isutf8 ? "❗️" : "E ";
	g_emojis.test =						isutf8 ? "🧪" : " ";
	g_emojis.success_title_start =		isutf8 ? "🎉" : " ";
	g_emojis.success_title_end =		isutf8 ? "🚀" : " ";
	g_emojis.fail_title_start =			isutf8 ? "💥" : " ";
	g_emojis.fail_title_end =			isutf8 ? "😈" : " ";
}

```

./2_src/07_logs/03_format/1_format_basic.c
```c
#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_LOGS_INSIDE__
#include "colors_priv.h"
#include "emojis_priv.h"
#include "format_logs.h"
#include "status_pub.h"
#undef __FUT_INSIDE__
#undef __FUT_IO_INSIDE__
#undef __FUT_LOGS_INSIDE__

#include <stdarg.h>
#include <stdio.h>

#define H1_CAP 256
#define INDICATOR_CAP 16

const char	*format_h1(const char *fmt, va_list args)
{
	static char	buff[H1_CAP];
	size_t	offset;

	offset = snprintf(buff, sizeof buff, " %s%s%s ", GREY, EMJ_ARW_RIGHT, BBLUE);
	offset += vsnprintf(buff + offset, sizeof buff - offset, fmt, args);
	(void)snprintf(buff + offset, sizeof buff - offset, "%s", NONE);

	return (buff);
}

const char	*format_indicator(t_status *status)
{
	static char buff[INDICATOR_CAP];

	switch (status->type)
	{
		case PASSED:	snprintf(buff, sizeof buff, "%s%s%s ", GREEN, EMJ_PASS, NONE); break;
		case FAILED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_FAIL, NONE); break;
		case TIMED:		snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_TIMD, NONE); break;
		case CRASHED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_CRSH, NONE); break;
		case LEAKED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_LEAK, NONE); break;
		default:		buff[0] = '\0'; break;
	}
	return (buff);
}

const char	*format_h2(const char *fmt, va_list args)
{
	static char	buff[H2_CAP];
	size_t	offset;

	offset = snprintf(buff, sizeof buff, "    %s%s%s ", GREY, EMJ_ARW_DR, NONE);
	offset += vsnprintf(buff + offset, sizeof buff - offset, fmt, args);

	return (buff);
}

```

./2_src/07_logs/03_format/2_format_addr.c
```c
#include <dlfcn.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#if defined(__APPLE__)
#define PATH_FALLBACK ""
#else
#define PATH_FALLBACK "/proc/self/exe"
#endif

#define ADDR_CAP 128

static void	get_binary_path(char *buffer, size_t buffer_size)
{
	Dl_info	info;

	buffer[0] = '\0';
	if (dladdr((void *)&get_binary_path, &info) != 0 \
		&& info.dli_fname && info.dli_fname[0] != '\0')
		snprintf(buffer, buffer_size, "%s", info.dli_fname);
	else
		snprintf(buffer, buffer_size, PATH_FALLBACK);
}

#if defined(__APPLE__)
static inline void	build_atos_cmd(void *addr, char *cmd_buff, size_t buffer_size)
{
	Dl_info	info;
	char	binary_path[PATH_MAX];

	if (dladdr(addr, &info) == 0 || !info.dli_fbase)
		return ;

	get_binary_path(binary_path, sizeof binary_path);
	snprintf(cmd_buff, buffer_size, "atos -o \"%s\" -l %#lx %#lx 2>/dev/null",
		binary_path, (unsigned long)info.dli_fbase, (unsigned long)addr
	);
}

static inline void	run_atos_cmd(const char *cmd, char *buffer, size_t buffer_size)
{
	FILE	*fp;

	fp = popen(cmd, "r");
	if (!fp)
		return;

	if (!fgets(buffer, buffer_size, fp))
	{
		pclose(fp);
		return;
	}
	pclose(fp);

	if (buffer[0] == '\0' || strstr(buffer, "0x") == buffer)
		return;
	buffer[strcspn(buffer, "\r\n")] = '\0';
}

static inline void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	char	cmd[PATH_MAX + 256];
	char	resolved[256];
	char	*opening_par;
	char	*closing_par;

	build_atos_cmd(addr, cmd, sizeof cmd);
	run_atos_cmd(cmd, resolved, sizeof resolved);

	opening_par = strrchr(resolved, '(');
	closing_par = strrchr(resolved, ')');

	if (opening_par && closing_par && closing_par > opening_par + 1)
	{
		*closing_par = '\0';
		snprintf(buffer, buffer_size, "%s", opening_par + 1);
	}
	else
	{
		snprintf(buffer, buffer_size, "unknown location");
	}
}
#else
static inline void resolve_address(void *addr, char *buffer, size_t buffer_size)
{
	char	binary_path[PATH_MAX];
	char	cmd[PATH_MAX + 128];
	char	loc[256];
	char	func[256];
	FILE	*fp;

	get_binary_path(binary_path, sizeof binary_path);
	snprintf(cmd, sizeof cmd, "addr2line -f -e \"%s\" %p 2>/dev/null", binary_path, addr);
	fp = popen(cmd, "r");
	if (!fp)
		return;
	if (!fgets(func, sizeof func, fp))
	{
		pclose(fp);
		return;
	}
	if (!fgets(loc, sizeof loc, fp))
	{
		pclose(fp);
		return;
	}
	pclose(fp);
	func[strcspn(func, "\r\n")] = '\0';
	loc[strcspn(loc, "\r\n")] = '\0';
	snprintf(buffer, buffer_size, "%s() in %s", func, loc);
}
#endif

const char	*format_addr(void *ptr)
{
	static char	buff[ADDR_CAP];

	if (!ptr)
		snprintf(buff, sizeof buff, "unknown location");
	else
	{
		buff[0] = '\0';
		resolve_address(ptr, buff, sizeof buff);
		if (buff[0] == '\0')
			snprintf(buff, sizeof buff, "%p", ptr);
	}

	return (buff);
}

```

./2_src/07_logs/03_format/3_format_status.c
```c
#include "status_pub.h"
#include <stdio.h>
#include <signal.h>

#define STATUS_BUFF_SIZE 64

static const char *status_names[] =
{
	"queued",
	"running",
	"passed",
	"failed",
	"timed out",
	"crashed",
	"leaked",
	"done",	
};

static inline const char	*format_sig(t_status *status)
{
	switch (status->sig)
	{
		case SIGINT:	return ("SIGINT");
		case SIGQUIT:	return ("SIGQUIT");
		case SIGILL:	return ("SIGILL");
		case SIGABRT:	return ("SIGABRT");
		case SIGFPE:	return ("SIGFPE");
		case SIGKILL:	return ("SIGKILL");
		case SIGSEGV:	return ("SIGSEGV");
		case SIGPIPE:	return ("SIGPIPE");
		case SIGALRM:	return ("SIGALRM");
		case SIGTERM:	return ("SIGTERM");
		case SIGBUS:	return ("SIGBUS");
		case SIGSYS:	return ("SIGSYS");
		case SIGTRAP:	return ("SIGTRAP");
		case SIGCHLD:	return ("SIGCHLD");
		case SIGSTOP:	return ("SIGSTOP");
		case SIGTSTP:	return ("SIGTSTP");
		case SIGCONT:	return ("SIGCONT");
		case SIGURG:	return ("SIGURG");
		default:		return ("UNKNOWN_SIGNAL");
	}
}

const char	*format_status(t_status *status)
{
	static char	buffer[STATUS_BUFF_SIZE];

	switch (status->type)
	{
		case TIMED:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "timed out (%zus)", status->timeout);
			break;
		case CRASHED:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "crashed (%s)", format_sig(status));
			break;
		default:
			(void)snprintf(buffer, STATUS_BUFF_SIZE, "%s", status_names[status->type]);
			break;
	}
	return (buffer);
}

```

./2_src/07_logs/03_format/format_logs.h
```c
#ifndef ULT_FORMAT_LOGS_H
#define ULT_FORMAT_LOGS_H

#ifndef __FUT_LOGS_INSIDE__
/*
**  Private header for the LOGS module.
**  Not available outside its compilation unit.
*/
#else

#include "format_priv.h"
#include "status_pub.h"
#include <stdarg.h>

const char	*format_h1(const char *fmt, va_list args);
const char	*format_h2(const char *fmt, va_list args);
const char	*format_indicator(t_status *status);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORMAT_LOGS_H */

```

./2_src/07_logs/03_format/format_priv.h
```c
#ifndef ULT_FORMAT_PRIV_H
#define ULT_FORMAT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"

#define H2_CAP 512

const char	*format_addr(void *ptr);
const char	*format_status(t_status *status);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORMAT_PRIV_H */

```

./2_src/07_logs/03_format/format_pub.h
```c
#ifndef ULT_FORMAT_PUB_H
#define ULT_FORMAT_PUB_H

typedef enum e_format {
	F_BOOL,
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING,
	F_STRUCT
}	t_format;

#endif



```

./2_src/07_logs/04_manager/manager_priv.h
```c
#ifndef ULT_MANAGER_PRIV_H
#define ULT_MANAGER_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"

__attribute__((format(printf, 1, 2)))
void	logs_print_h1(const char *fmt, ...);

void	logs_print_indicator(t_status *status);

__attribute__((format(printf, 1, 2)))
void	logs_store_h2(const char *fmt, ...);
void	logs_print_h2(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_MANAGER_PRIV_H */

```

./2_src/07_logs/04_manager/manager.c
```c
#define __FUT_INSIDE__
#define __FUT_LOGS_INSIDE__
#include "error_priv.h"
#include "format_logs.h"
#include "print_wrapper_pub.h"
#include "status_pub.h"
#undef __FUT_LOGS_INSIDE__
#undef __FUT_INSIDE__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define H2_STORE_INITIAL_CAP 128
#define H2_STORE_GROWTH_RATIO 2

static char		**h2_stored_logs = NULL;
static size_t	h2_store_cap = 0;
static size_t	h2_store_count = 0;

static inline void	init_h2_storage(void);

void	logs_print_h1(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	print_stdout("%s", format_h1(fmt, args));
	va_end(args);
}

void	logs_print_indicator(t_status *status)
{
	print_stdout("%s", format_indicator(status));
}

void	logs_store_h2(const char *fmt, ...)
{
	va_list	args;
	char	*log;

	init_h2_storage();

	log = malloc(H2_CAP);
	exit_if(!log, NOT_ENOUGH_MEMORY);

	va_start(args, fmt);
	snprintf(log, H2_CAP, "%s", format_h2(fmt, args));
	va_end(args);

	h2_stored_logs[h2_store_count] = log;
	h2_store_count++;
}

void	logs_print_h2(void)
{
	print_stdout("\n");
	for (size_t i = 0; i < h2_store_count; i++)
	{
		print_stdout("%s", h2_stored_logs[i]);
		free(h2_stored_logs[i]);
	}
	free(h2_stored_logs);
	h2_stored_logs = NULL;
	h2_store_count = 0;
	h2_store_cap = 0;
}

static inline void	init_h2_storage(void)
{
	size_t	new_cap;
	char	**new_ptr;

	if (h2_store_cap == 0)
	{
		h2_stored_logs = malloc(H2_STORE_INITIAL_CAP * sizeof h2_stored_logs);
		exit_if(!h2_stored_logs, NOT_ENOUGH_MEMORY);
		h2_store_cap = H2_STORE_INITIAL_CAP;
	}
	else if (h2_store_count == h2_store_cap)
	{
		new_cap = h2_store_cap * 2;
		new_ptr = realloc(h2_stored_logs, new_cap * sizeof h2_stored_logs);
		exit_if(!new_ptr, NOT_ENOUGH_MEMORY);
		h2_stored_logs = new_ptr;
		h2_store_cap = new_cap;
	}
}

```

./2_src/07_logs/05_send/send_priv.h
```c
#ifndef ULT_SEND_PRIV_H
#define ULT_SEND_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "process_priv.h"

#include <inttypes.h>
#include <stdio.h>

void	send_incorrect_status(const char *expr, t_status *got, t_status *exp);
void	send_incorrect_return(const char *expr, t_format fmt, intptr_t got, intptr_t *exp);
void	send_incorrect_output(const char *expr, const char *got, const char *exp);
void	send_leak(const char *expr, size_t size, void *caller);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SEND_PRIV_H */

```

./2_src/07_logs/05_send/send.c
```c
#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "messages_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

static inline void	add_formatted_value(char *buff, size_t cap, size_t *offset, t_format fmt, intptr_t value);

void	send_incorrect_status(const char *expr, t_status *got, t_status *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	if (got->type == DONE)
	{
		exp->crash_address = NULL;
		snprintf(log, sizeof log, "%s%s %sdid not %s\n", RED, expr, YELLOW, format_status(exp));
	}
	else
	{
		offset = snprintf(log, sizeof log, "%s%s %s%s", RED, expr, YELLOW, format_status(got));
		if (got->crash_address)
			offset += snprintf(log + offset, sizeof log - offset, " %sat %s", GREY, format_addr(got->crash_address));
		if (exp && exp->type != DONE)
			offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s%s", GREY, RED, format_status(exp));

		snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	}
	message_send(g_context.pipe_to_parent, LOG, (t_message_data *)log);
}

void	send_incorrect_return(const char *expr, t_format fmt, intptr_t got, intptr_t *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	if (fmt == F_BOOL)
		snprintf(log, sizeof log, "%s%s %s%s %s\n", RED, expr, YELLOW, "is false", NONE);
	else
	{
		offset = snprintf(log, sizeof log, "%s%s %s%s %s", RED, expr, YELLOW, "returned", RED);
		add_formatted_value(log, sizeof log, &offset, fmt, got);
		if (exp)
		{
			offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s", GREY, RED);
			add_formatted_value(log, sizeof log, &offset, fmt, *exp);
		}

		snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	}
	message_send(g_context.pipe_to_parent, LOG, (t_message_data *)log);
}

void	send_incorrect_output(const char *expr, const char *got, const char *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	offset = snprintf(log, sizeof log, "%s%s %s%s %s", RED, expr, YELLOW, "outputed", RED);
	add_formatted_value(log, sizeof log, &offset, F_STRING, (intptr_t)got);
	if (exp)
	{
		offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s", GREY, RED);
		add_formatted_value(log, sizeof log, &offset, F_STRING, (intptr_t)exp);
	}
	snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	message_send(g_context.pipe_to_parent, LOG, (t_message_data *)log);
}

void	send_leak(const char *expr, size_t size, void *caller)
{
	char	log[H2_CAP];

	snprintf(log, sizeof log, "%s%s %s%s %s%zu bytes %sat %s%s\n", \
		RED, expr, YELLOW, "leaked", RED, size, GREY, \
		format_addr(caller), NONE
	);
	message_send(g_context.pipe_to_parent, LOG, (t_message_data *)log);
}

static inline void	add_formatted_value(char *buff, size_t cap, size_t *offset, t_format fmt, intptr_t value)
{
	switch (fmt)
	{
		case F_BOOL:
			if (value == true) *offset+= snprintf(buff + *offset, cap - *offset, "true");
			else *offset+= snprintf(buff + *offset, cap - *offset, "false");
			break;
		case F_SIGNED:		*offset+= snprintf(buff + *offset, cap - *offset, "%" PRIdPTR, (intptr_t)value); break;
		case F_UNSIGNED:	*offset+= snprintf(buff + *offset, cap - *offset, "%" PRIuPTR, (uintptr_t)value); break;
		case F_CHAR:		*offset+= snprintf(buff + *offset, cap - *offset, "%c", (char)value); break;
		case F_STRING:
			// TODO: Remove log max size + don't truncate logs anymore
			if (strlen((char *)value) > 64)
				*offset+= snprintf(buff + *offset, cap - *offset, "%s'%s%.20s[...]%s'%s", GREY, RED, (char *)value, GREY, RED);
			else
				*offset+= snprintf(buff + *offset, cap - *offset, "%s'%s%s%s'%s", GREY, RED, (char *)value, GREY, RED);
			break;
		case F_STRUCT:		*offset+= snprintf(buff + *offset, cap - *offset, "unexpected struct content"); break;
		default:			*offset+= snprintf(buff + *offset, cap - *offset, "%#" PRIxPTR, (uintptr_t)value); break;
	}
}

```

./2_src/07_logs/logs_priv.h
```c
#ifndef ULT_LOGS_PRIV_H
#define ULT_LOGS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "logs_pub.h"
#include "colors_priv.h"
#include "emojis_priv.h"
#include "format_priv.h"
#include "manager_priv.h"
#include "send_priv.h"

#endif /* __FUT_INSIDE__ */

#endif /* ULT_LOGS_PRIV_H */

```

./2_src/07_logs/logs_pub.h
```c
#ifndef ULT_LOGS_PUB_H
#define ULT_LOGS_PUB_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "format_pub.h"

#endif /* __FUT_INSIDE__ */

#endif /* ULT_LOGS_PRIV_H */

```

./2_src/08_engine/01_set/1_set.c
```c
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "print_wrapper_pub.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <string.h>

t_result		g_result;
static size_t	s_h1_max_len;

void	set_run(t_set *set)
{
	logs_print_h1("%-*s ", (int)s_h1_max_len, set->name);
	set->result.status.type = RUNNING;

	_fork_init(set->timeout);
	if (g_context.child_pid > 0)
		set_run_parent(set);
	else
		set_run_child(set);

	if (set->result.status.type != PASSED)
		print_stdout("\n");
}

void	set_init(t_set *first_set, t_set *last_set)
{
	t_set	*set;
	size_t	len;

	for (set = first_set; set < last_set; set++)
	{
		len = strlen(set->name);
		if (len > s_h1_max_len)
			s_h1_max_len = len;
	}
}

```

./2_src/08_engine/01_set/2_set_parent.c
```c
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "error_priv.h"
#include "print_wrapper_pub.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static inline void	wait_for_child(int *status, t_set *set);
static inline void	handle_timeout(t_set *set);
static inline void	handle_crash(t_set *set, int status);

static t_set	*s_current_set;

void	set_run_parent(t_set *set)
{
	int		status;

	s_current_set = set;
	wait_for_child(&status, set);

	if (timeout_is_triggered() || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
		handle_timeout(set);
	else if (set->result.status.crash_address || WIFSIGNALED(status))
		handle_crash(set, status);
	else
		logs_print_h2();

	result_compute(&set->result);
	result_add(&set->result, &g_result);
	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_set *set)
{
	t_message	message;

	while (message_receive(g_context.pipe_to_child, &message))
	{
		switch (message.type)
		{
			case RESULT:
				result_add(&message.data.result, &set->result);
				break;
			case CRASH:
				set->result.status.crash_address = message.data.crash_addr;
				break;
			case LOG:
				logs_store_h2("%s", message.data.log);
				break;
			default: exit_if(true, SET_UNKNOWN_MESSAGE_TYPE);
		}
	}

	waitpid(g_context.child_pid, status, 0);
}

static inline void	handle_timeout(t_set *set)
{
	set->result.timed++;
	set->result.status.type = TIMED;
	set->result.status.timeout = set->timeout;

	logs_print_indicator(&set->result.status);
	logs_print_h2();

	print_stdout(" %s%s %s%s %stimed out (%zus)%s\n", GREY, EMJ_ARW_DR, RED, set->name, YELLOW, set->timeout, NONE);
}

static inline void	handle_crash(t_set *set, int status)
{
	set->result.crashed++;
	set->result.status.type = CRASHED;
	set->result.status.sig = WTERMSIG(status);

	logs_print_indicator(&set->result.status);
	logs_print_h2();

	print_stdout(" %s%s %s%s %s%s %sat %s%s\n", \
		GREY, EMJ_ARW_DR, \
		RED, set->name, YELLOW, format_status(&set->result.status), \
		GREY, format_addr(set->result.status.crash_address), NONE);
}

```

./2_src/08_engine/01_set/3_set_child.c
```c
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

void	set_run_child(t_set *set)
{
	set->func();

	fork_cleanup();
	exit(EXIT_SUCCESS);
}

```

./2_src/08_engine/01_set/set_internal.h
```c
#ifndef ULT_SET_INTERNAL_H
#define ULT_SET_INTERNAL_H

#ifndef __FUT_SET_INSIDE__
/*
**  Internal header for the SET module.
**  Not available outside its compilation unit.
*/
#else

#include "process_priv.h"
#include "set_priv.h"

void	set_run_parent(t_set *set);
void	set_run_child(t_set *set);

#endif /* __FUT_SET_INSIDE__ */

#endif /* ULT_SET_INTERNAL_H */

```

./2_src/08_engine/01_set/set_priv.h
```c
#ifndef ULT_SET_PRIV_H
#define ULT_SET_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "set_pub.h"

extern t_result	g_result;

void	set_init(t_set *first_set, t_set *last_set);
void	set_run(t_set *set);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_SET_PRIV_H */

```

./2_src/08_engine/01_set/set_pub.h
```c
#ifndef ULT_SET_PUB_H
#define ULT_SET_PUB_H

#include "result_pub.h"
#include <stddef.h>

#if defined(__APPLE__)
	#define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	#define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

typedef void (*t_test_fn)(void);

typedef struct s_set
{
	const char	*name;
	size_t		timeout;
	t_test_fn	func;
	t_result	result;
}	t_set;

#define Test(name, timeout_sec) 						\
	static void name(void); 							\
	static t_set ULT_SECTION _##name##__##__COUNTER__ =	\
	{													\
		#name,											\
		timeout_sec,									\
		name,											\
		{ {QUEUED, 0, 0, 0}, 0, 0, 0, 0, 0, 0 }			\
	};													\
	static void name(void)

#endif

```

./2_src/08_engine/02_memcheck/1_memcheck_table.c
```c
#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "error_priv.h"
#include "memcheck_int.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__
#include <stdlib.h>
#include <string.h>

#define TABLE_INITIAL_SIZE 1024
#define TABLE_GROWTH_RATIO 2

t_leak	*g_leaks_table = NULL;
size_t	g_leaks_count = 0;

static size_t	s_leaks_table_cap = 0;
static bool		s_enabled = false;
t_mem_mode		g_mem_mode;

void	register_alloc(void *ptr, size_t size, void *caller);
void	register_free(void *ptr);

void	_memcheck_enable(t_mem_mode mode)
{
	if (s_leaks_table_cap > 0)
		bzero(g_leaks_table, g_leaks_count * sizeof(t_leak));
	else
	{
		s_leaks_table_cap = TABLE_INITIAL_SIZE;
		s_enabled = false;
		g_leaks_table = calloc(s_leaks_table_cap, sizeof(t_leak));
	}

	g_leaks_count = 0;
	s_enabled = true;
	g_mem_mode = mode;
}

void	memcheck_disable(void)
{
	s_enabled = false;
}

void	register_alloc(void *ptr, size_t size, void *caller)
{
	if (!s_enabled || g_mem_mode != LEAKS)
		return ;

	if (g_leaks_count == s_leaks_table_cap)
	{
		s_leaks_table_cap *= TABLE_GROWTH_RATIO;
		s_enabled = false;
		g_leaks_table = realloc(g_leaks_table, s_leaks_table_cap * sizeof(t_leak));
		s_enabled = true;
		exit_if(!g_leaks_table, NOT_ENOUGH_MEMORY);
	}

	g_leaks_table[g_leaks_count].ptr = ptr;
	g_leaks_table[g_leaks_count].size = size;
	g_leaks_table[g_leaks_count].caller = caller;
	g_leaks_count++;
}

void	register_free(void *ptr)
{
	size_t	i;

	if (!s_enabled || g_mem_mode != LEAKS)
		return ;

	i = 0;
	while (i < g_leaks_count && g_leaks_table[i].ptr != ptr)
		i++;

	if (g_leaks_count == 0 || i >= g_leaks_count)
		return ;

	if (g_leaks_count == 1)
	{
		g_leaks_count--;
		g_leaks_table[0].ptr = NULL;
		g_leaks_table[0].size = 0;
		g_leaks_table[0].caller = NULL;
	}
	else
	{
		g_leaks_count--;
		g_leaks_table[i].ptr = g_leaks_table[g_leaks_count].ptr;
		g_leaks_table[i].size = g_leaks_table[g_leaks_count].size;
		g_leaks_table[i].caller = g_leaks_table[g_leaks_count].caller;
	}
}

```

./2_src/08_engine/02_memcheck/2_memcheck_hooks.c
```c
#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "memcheck_int.h"
#include "error_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <dlfcn.h>

static void	*(*real_malloc)(size_t) = NULL;
static void	*(*real_calloc)(size_t count, size_t) = NULL;
static void	*(*real_realloc)(void *ptr, size_t) = NULL;
static void	(*real_free)(void *) = NULL;

static inline void	init_hooks(void)
{
	if (!real_malloc)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		real_calloc = dlsym(RTLD_NEXT, "calloc");
		real_realloc = dlsym(RTLD_NEXT, "realloc");
		real_free = dlsym(RTLD_NEXT, "free");
	}

	exit_if( \
		!real_malloc || !real_calloc || !real_realloc || !real_free,\
		UNABLE_TO_FETCH_REAL_ALLOCATORS \
	);
}

void	*malloc(size_t size)
{
	void	*ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
		return (NULL);

	ptr = real_malloc(size);
	caller = __builtin_return_address(0);
	register_alloc(ptr, size, caller);

	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
		return (NULL);

	ptr = real_calloc(count, size);
	caller = __builtin_return_address(0);
	register_alloc(ptr, size, caller);

	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
	{
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}

	if (size == 0)
		register_free(ptr);
	
	new_ptr = real_realloc(ptr, size);

	if (size > 0 && new_ptr)
	{
		register_free(ptr);
		caller = __builtin_return_address(0);
		register_alloc(new_ptr, size, caller);
	}
	return (new_ptr);
}

void	free(void *ptr)
{
	init_hooks();
	register_free(ptr);
	real_free(ptr);
}

```

./2_src/08_engine/02_memcheck/4_memcheck_parent.c
```c
#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

static inline void	wait_for_child(int *status, t_result *result);

void	_memcheck_parent(const char *expr)
{
	int			status;
	t_result	result = {0};

	wait_for_child(&status, &result);

	if (timeout_is_triggered())
	{
		result.timed++;
		result.status.type = TIMED;
		result.status.timeout = g_context.child_timeout;
		logs_print_indicator(&result.status);
		send_incorrect_status(expr, &result.status, NULL);
	}
	else if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		if (WIFSIGNALED(status))
			result.status.sig = WTERMSIG(status);

		result.crashed++;
		send_incorrect_status(expr, &result.status, NULL);
	}

	result_compute(&result);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);
	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_result *result)
{
	t_message	message;

	while (message_receive(g_context.pipe_to_child, &message))
	{
		switch (message.type)
		{
			case RESULT:
				logs_print_indicator(&message.data.result.status);
				result_add(&message.data.result, result);
				break;
			case CRASH:
				result->status.type = CRASHED;
				result->status.crash_address = message.data.crash_addr;
				logs_print_indicator(&result->status);
				break;
			case LOG:
				message_send(g_context.pipe_to_parent, LOG, &message.data);
				break;
			default: exit_if(true, SET_UNKNOWN_MESSAGE_TYPE);
		}
	}

	waitpid(g_context.child_pid, status, 0);
}

```

./2_src/08_engine/02_memcheck/5_memcheck_child.c
```c
#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "memcheck_int.h"
#include "messages_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

void	_memcheck_child(const char *expr)
{
	t_result	result = {0};

	memcheck_disable();

	for (size_t i = 0; i < g_leaks_count; i++)
	{
		send_leak(expr, g_leaks_table[i].size, g_leaks_table[i].caller);
		result.leaks++;
	}

	if (result.leaks == 0)
		result.passed++;
	
	result_compute(&result);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);

	fork_cleanup();

	exit(EXIT_SUCCESS);
}

```

./2_src/08_engine/02_memcheck/memcheck_int.h
```c
#ifndef ULT_MEMCHECK_INTERNAL_H
#define ULT_MEMCHECK_INTERNAL_H

#ifndef __FUT_MEMCHECK_INSIDE__
/*
**  Internal header for the memcheck module.
**  Not available outside its compilation unit.
*/
#else

#include "memcheck_pub.h"
#include "status_pub.h"
#include <stddef.h>

typedef struct s_leak
{
	void	*ptr;
	size_t	size;
	void	*caller;
}	t_leak;

extern t_leak		*g_leaks_table;
extern size_t		g_leaks_count;
extern t_mem_mode	g_mem_mode;

void	memcheck_enable(void);
void	memcheck_disable(void);
void	register_alloc(void *ptr, size_t size, void *caller);
void	register_free(void *ptr);

#endif /* __FUT_MEMCHECK_INSIDE__ */

#endif /* ULT_MEMCHECK_INTERNAL_H */

```

./2_src/08_engine/02_memcheck/memcheck_pub.h
```c
#ifndef ULT_MEMCHECK_PUB_H
#define ULT_MEMCHECK_PUB_H

#include <stddef.h>

typedef enum e_mem_mode
{
	LEAKS,
	SAFETY,
}	t_mem_mode;

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr);
void	_memcheck_enable(t_mem_mode mode);
void	_memcheck_child(const char *expr);

#define memleaks(timeout, expr)				\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(LEAKS);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#define memsafety(timeout, expr)			\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(SAFETY);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#endif

```

./2_src/08_engine/03_capture/capture_pub.h
```c
#ifndef ULT_CAPTURE_PUB_H
#define ULT_CAPTURE_PUB_H

#include "redirect_pub.h"
#include "status_pub.h"
#include <string.h>

typedef enum e_capture_mode
{
	RET,
	OUT,
	ERR,
	BOTH,
	RET_OUT,
	RET_ERR,
	RET_BOTH,
}	t_capture_mode;

static const t_redirect_mode g_capture_to_redirect[] = {
	[RET]		= -1,
    [OUT]       = R_STDOUT,
    [ERR]       = R_STDERR,
    [BOTH]      = R_BOTH,
    [RET_OUT]   = R_STDOUT,
    [RET_ERR]   = R_STDERR,
    [RET_BOTH]  = R_BOTH
};

typedef struct s_capture {
	t_status	status;
	intptr_t	ret;
	char		*out;
} t_capture;

typedef struct s_capture_res
{
	intptr_t	ret;
	char		*out;
}	t_capture_res;

void	_capture_parent(t_capture *capture);
void	_capture_child(t_capture_res *res);

#define __type_is_void(expr) __builtin_types_compatible_p(__typeof__(expr), void)
#define __expr_or_zero(expr) __builtin_choose_expr(__type_is_void(expr), 0, (expr))
#define CAP_VOID(expr, dest) ({ (void)(expr); (dest) = 0; 0; })
#define CAP_VALUE(expr, dest) ({ (dest) = (intptr_t)(__expr_or_zero(expr)); 0; })
#define CAP_DISPATCH(expr, dest)				\
	__builtin_choose_expr(__type_is_void(expr),	\
		CAP_VOID(expr, dest),					\
		CAP_VALUE(expr, dest))

#define capture(mode, timeout_sec, expr, capture_var_name)		\
	do {														\
		memset(&capture_var_name, 0, sizeof capture_var_name);	\
		capture_var_name.status.timeout = timeout_sec;			\
		_fork_init(timeout_sec);								\
		if (g_context.child_pid > 0)							\
			_capture_parent(&capture_var_name);					\
		else													\
		{														\
			t_capture_res capture_res = {0};					\
			if (mode != RET)									\
				redirect_start(g_capture_to_redirect[mode]);	\
			CAP_DISPATCH(expr, capture_res.ret);				\
			if (mode != RET)									\
			{													\
				capture_res.out = redirect_read();				\
				redirect_stop();								\
			}													\
			_capture_child(&capture_res);						\
		}														\
	} while (0)

#endif

```

./2_src/08_engine/03_capture/child.c
```c
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

```

./2_src/08_engine/03_capture/parent.c
```c
#define __FUT_INSIDE__
#include "capture_pub.h"
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline void	wait_for_child(int *status, t_capture *capture);
static inline void	read_ret(t_capture *capture);
static inline void	read_out(t_capture *capture);
static inline void	read_crash(t_capture *capture);

void	_capture_parent(t_capture *capture)
{
	int		status;

	wait_for_child(&status, capture);

	if (timeout_is_triggered())
		capture->status.type = TIMED;
	else if (capture->status.crash_address || !WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		capture->status.type = CRASHED;
		if (WIFSIGNALED(status))
			capture->status.sig = WTERMSIG(status);
	}
	else
		capture->status.type = DONE;

	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_capture *capture)
{
	t_message_type	type;

	while (message_read_type(g_context.pipe_to_child, &type))
	{
		switch (type)
		{
			case RETURN_VALUE:	read_ret(capture); break;
			case CUSTOM:		read_out(capture); break;
			case CRASH:			read_crash(capture); break;
			default:			exit_if(true, MESSAGE_UNKNOWN_TYPE);
		}
	}
	waitpid(g_context.child_pid, status, 0);
}

static inline void	read_ret(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);
	exit_if(len != sizeof capture->ret, MESSAGE_INVALID_LEN);

	(void)message_read_data(g_context.pipe_to_child, &capture->ret, sizeof capture->ret);
}

static inline void	read_out(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);

	capture->out = malloc(len + 1);
	exit_if(!capture->out, NOT_ENOUGH_MEMORY);

	(void)message_read_data(g_context.pipe_to_child, capture->out, len);
	capture->out[len] = '\0';
}

static inline void	read_crash(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);
	exit_if(len != sizeof capture->status.crash_address, MESSAGE_INVALID_LEN);

	(void)message_read_data( \
		g_context.pipe_to_child, \
		&capture->status.crash_address, \
		sizeof capture->status.crash_address \
	);
}

```

./2_src/08_engine/04_compare/compare_engine.h
```c
#ifndef ULT_COMPARE_ENGINE_H
#define ULT_COMPARE_ENGINE_H

#ifndef __FUT_ENGINE_INSIDE__
/*
**  Internal header for the engine subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool	compare_status(const t_status *s1, const t_status *s2);
bool	compare_strings(const char *s1, const char *s2);
bool	compare_intptr_t(intptr_t i1, intptr_t i2);
bool	compare_structs(const void *s1, const void *s2, size_t struct_size);

#endif /* __FUT_ENGINE_INSIDE__ */

#endif /* ULT_COMPARE_ENGINE_H */

```

./2_src/08_engine/04_compare/compare.c
```c
#define __FUT_ENGINE_INSIDE__
#include "compare_engine.h"
#undef __FUT_ENGINE_INSIDE__

#include <stdbool.h>
#include <string.h>

bool	compare_status(const t_status *s1, const t_status *s2)
{
	if (s1->type == CRASHED && s2->type == CRASHED)
		return (s1->sig == s2->sig);
	else
	 	return (s1->type == s2->type);
}

bool	compare_strings(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (!s1 && !s2);

	return (strcmp(s1, s2) == 0);
}

bool	compare_intptr_t(intptr_t i1, intptr_t i2)
{
	return (i1 == i2);
}

bool	compare_structs(const void *s1, const void *s2, size_t struct_size)
{
	if (!s1 || !s2)
		return (!s1 && !s2);
	
	return (memcmp(s1, s2, struct_size) == 0);
}

```

./2_src/08_engine/05_assert/1_assert.c
```c
#define __FUT_INSIDE__
#define __FUT_ASSERT_INSIDE__
#include "assert_int.h"
#include "messages_priv.h"
#undef __FUT_ASSERT_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

void	_assert_run(t_assert *assert)
{
	t_status	status = {0};
	t_result	result = {0};

	if (assert->eq == true)
		status = assert_check_eq(assert);
	else
	 	status = assert_check_neq(assert);

	if (status.type == PASSED)
		result.passed++;
	else if (status.type == FAILED)
		result.failed++;
	else if (status.type == TIMED)
		result.timed++;
	else if (status.type == CRASHED)
		result.crashed++;

	result_compute(&result);
	logs_print_indicator(&result.status);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);

	if (assert->got_capt->out)
		free(assert->got_capt->out);
	if (assert->exp_capt->out)
		free(assert->exp_capt->out);
}

```

./2_src/08_engine/05_assert/2_assert_eq.c
```c
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#include "assert_pub.h"
#include "compare_engine.h"
#include "send_priv.h"
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <inttypes.h>

static inline t_status	check_status(t_assert *assert);
static inline bool		check_ret(t_assert *assert);
static inline bool		check_out(t_assert *assert);

t_status	assert_check_eq(t_assert *assert)
{
	t_status	status_res = {0};
	bool		ret_passed;
	bool		out_passed;
	t_status	final_res = {0};
	
	status_res = check_status(assert);
	if (status_res.type != PASSED)
		return (status_res);

	ret_passed = true;
	if (assert->mode != OUT && assert->mode != ERR && assert->mode != BOTH)
		ret_passed = check_ret(assert);

	out_passed = true;
	if (assert->mode != RET)
		out_passed = check_out(assert);

	if (ret_passed && out_passed)
		final_res.type = PASSED;
	else
		final_res.type = FAILED;
	
	return (final_res);
}

static inline t_status	check_status(t_assert *assert)
{
	t_status	status = {0};

	if (compare_status(&assert->got_capt->status, &assert->exp_capt->status))
		status.type = PASSED;
	else if (assert->got_capt->status.type == CRASHED)
	{
		status.type = CRASHED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, &assert->exp_capt->status);
	}
	else if (assert->got_capt->status.type == TIMED)
	{
		status.type = TIMED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, &assert->exp_capt->status);
	}
	else
	{
		status.type = FAILED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, &assert->exp_capt->status);
	}
	return (status);
}

static inline bool	check_ret(t_assert *a)
{
	if (a->format == F_STRING && !compare_strings((const char *)a->got_capt->ret, (const char *)a->exp_capt->ret))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	else if (a->format == F_STRUCT && !compare_structs((const void *)a->got_capt->ret, (const void *)a->exp_capt->ret, a->ret_size))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	else if (a->format != F_STRING && a->format != F_STRUCT && !compare_intptr_t(a->got_capt->ret, a->exp_capt->ret))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	return (true);
}

static inline bool	check_out(t_assert *assert)
{
	if (!compare_strings(assert->got_capt->out, assert->exp_capt->out))
	{
		send_incorrect_output(assert->lab, assert->got_capt->out, assert->exp_capt->out);
		return (false);
	}
	return (true);
}



```

./2_src/08_engine/05_assert/3_assert_neq.c
```c
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#include "assert_pub.h"
#include "compare_engine.h"
#include "send_priv.h"
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <inttypes.h>

static inline t_status	check_status(t_assert *assert);
static inline bool		check_ret(t_assert *assert);
static inline bool		check_out(t_assert *assert);

t_status	assert_check_neq(t_assert *assert)
{
	t_status	status_res = {0};
	bool		ret_passed;
	bool		out_passed;
	t_status	final_res = {0};
	
	status_res = check_status(assert);
	if (status_res.type != PASSED)
		return (status_res);

	ret_passed = true;
	if (assert->mode != OUT && assert->mode != ERR && assert->mode != BOTH)
		ret_passed = check_ret(assert);

	out_passed = true;
	if (assert->mode != RET)
		out_passed = check_out(assert);

	if (ret_passed && out_passed)
		final_res.type = PASSED;
	else
		final_res.type = FAILED;

	return (final_res);
}

static inline t_status	check_status(t_assert *assert)
{
	t_status	status = {0};

	status.type = PASSED;
	if (assert->got_capt->status.type == CRASHED)
	{
		status.type = CRASHED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, NULL);
	}
	else if (assert->got_capt->status.type == TIMED)
	{
		status.type = TIMED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, NULL);
	}
	else if (assert->exp_capt->status.type == CRASHED)
	{
		status.type = CRASHED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, NULL);
	}
	else if (assert->exp_capt->status.type == TIMED)
	{
		status.type = TIMED;
		send_incorrect_status(assert->lab, &assert->got_capt->status, NULL);
	}
	return (status);
}

static inline bool	check_ret(t_assert *a)
{
	if (a->format == F_STRING && compare_strings((const char *)a->got_capt->ret, (const char *)a->exp_capt->ret))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, NULL);
		return (false);
	}
	else if (a->format == F_STRUCT && compare_structs((const void *)a->got_capt->ret, (const void *)a->exp_capt->ret, a->ret_size))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, NULL);
		return (false);
	}
	else if (compare_intptr_t(a->got_capt->ret, a->exp_capt->ret))
	{
		send_incorrect_return(a->lab, a->format, a->got_capt->ret, NULL);
		return (false);
	}
	return (true);
}

static inline bool	check_out(t_assert *assert)
{
	if (compare_strings(assert->got_capt->out, assert->exp_capt->out))
	{
		send_incorrect_output(assert->lab, assert->got_capt->out, NULL);
		return (false);
	}
	return (true);
}

```

./2_src/08_engine/05_assert/assert_int.h
```c
#ifndef ULT_ASSERT_INTERNAL_H
#define ULT_ASSERT_INTERNAL_H

#ifndef __FUT_ASSERT_INSIDE__
/*
**  Internal header for the assert module.
**  Not available outside its compilation unit.
*/
#else

#include "assert_pub.h"
#include "status_pub.h"

t_status	assert_check_eq(t_assert *assert);
t_status	assert_check_neq(t_assert *assert);

#endif /* __FUT_ASSERT_INSIDE__ */

#endif /* ULT_ASSERT_INTERNAL_H */

```

./2_src/08_engine/05_assert/assert_pub.h
```c
#ifndef ULT_ASSERT_PUB_H
#define ULT_ASSERT_PUB_H

#include "format_pub.h"
#include "capture_pub.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct s_assert
{
	t_capture_mode	mode;
	bool			eq;
	const char		*lab;
	t_capture		*got_capt;
	t_capture		*exp_capt;
	t_format		format;
	size_t			ret_size;
}	t_assert;

void	_assert_run(t_assert *assert);

#define _assert(should_be_equal, cap_mode, timeout_sec, label, got_expr, exp_expr)	\
	do {																			\
		t_capture _capt_got = {0};													\
		capture(cap_mode, timeout_sec, (got_expr), _capt_got);						\
																					\
		t_capture _capt_exp = {0};													\
		capture(cap_mode, timeout_sec, (exp_expr), _capt_exp);						\
																					\
		t_assert _assert = {0};														\
		_assert.mode = cap_mode;													\
		_assert.eq = should_be_equal;												\
		_assert.lab = label;														\
		_assert.got_capt = &_capt_got;												\
		_assert.exp_capt = &_capt_exp;												\
		if (__type_is_void(exp_expr) && __type_is_void(got_expr))					\
		{																			\
			_assert.ret_size = sizeof(int);											\
			_assert.format = F_SIGNED;												\
		}																			\
		else																		\
		{																			\
			_assert.ret_size = sizeof(__typeof__(exp_expr)); 						\
			_assert.format = _Generic(__typeof__(exp_expr), 						\
					bool: F_BOOL, 													\
					char: F_CHAR, 													\
					signed char: F_SIGNED, 											\
					short: F_SIGNED, 												\
					int: F_SIGNED, 													\
					long: F_SIGNED, 												\
					long long: F_SIGNED, 											\
					void *: F_HEX,													\
					char *: F_STRING,												\
					const char *: F_STRING,											\
					unsigned char: F_UNSIGNED, 										\
					unsigned short: F_UNSIGNED, 									\
					unsigned int: F_UNSIGNED, 										\
					unsigned long: F_UNSIGNED, 										\
					unsigned long long: F_UNSIGNED, 								\
					unsigned char *: F_STRING,										\
					const unsigned char *: F_STRING,								\
					default: F_HEX);												\
		}																			\
		_assert_run(&_assert);														\
	} while (0)

#define assert(timeout_sec, expr)													\
	_assert(true, RET, timeout_sec, #expr, expr, (bool)true)
#define assert_label(timeout_sec, label, expr)										\
	_assert(true, RET, timeout_sec, label, expr, (bool)true)

#define assert_eq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(true, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_eq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(true, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define assert_neq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(false, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_neq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(false, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define compare(cap_mode, timeout_sec, fn1_name, fn2_name, fn_args)					\
	_assert(true, cap_mode, timeout_sec, #fn1_name#fn_args, fn1_name fn_args, fn2_name fn_args)
#define compare_label(cap_mode, timeout_sec, label, fn1_name, fn2_name, fn_args)	\
	_assert(true, cap_mode, timeout_sec, label, fn1_name fn_args, fn2_name fn_args)

#endif

```

./2_src/08_engine/engine_priv.h
```c
#ifndef ULT_ENGINE_PRIV_H
#define ULT_ENGINE_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "set_priv.h"

#endif /* __FUT_INSIDE__ */

#endif /* ULT_ENGINE_PRIV_H */

```

./2_src/08_engine/engine_pub.h
```c
#ifndef ULT_ENGINE_PUB_H
#define ULT_ENGINE_PUB_H

#include "set_pub.h"
#include "memcheck_pub.h"
#include "capture_pub.h"
#include "assert_pub.h"

#endif

```

./2_src/09_report/report_priv.h
```c
#ifndef ULT_GLOBAL_PRIV_H
#define ULT_GLOBAL_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "result_pub.h"

void	print_report(const t_result *result);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_GLOBAL_PRIV_H */

```

./2_src/09_report/report.c
```c
#define __FUT_INSIDE__
#define __FUT_RESULT_INSIDE__
#include "colors_priv.h"
#include "emojis_priv.h"
#include "print_wrapper_pub.h"
#include "result_pub.h"
#undef __FUT_RESULT_INSIDE__
#undef __FUT_INSIDE__

#include <stdio.h>
#include <string.h>

#define START_TITLE_MAX_LEN 29
#define RES_TITLE_BUFF_SIZE 256
#define SEPARATOR_BUFF_SIZE 16
#define SCORE_BUFF_SIZE 64
#define SCORE_DIGITS 3

typedef struct s_res_colors
{
	const char	*title;
	const char	*passed;
	const char	*failed;
	const char	*timed;
	const char	*crashed;
	const char	*leaks;
}	t_res_colors;

typedef struct s_res_content
{
	char	title[RES_TITLE_BUFF_SIZE];
	char	separator[SEPARATOR_BUFF_SIZE];
	char	passed[SCORE_BUFF_SIZE];
	char	failed[SCORE_BUFF_SIZE];
	char	timed[SCORE_BUFF_SIZE];
	char	crashed[SCORE_BUFF_SIZE];
	char	leaks[SCORE_BUFF_SIZE];
}	t_res_content;

static inline void	get_colors(const t_result *res, t_res_colors *colors);
static inline void	get_content(const t_result *res, t_res_colors *colors, t_res_content *cont);

void	print_report(const t_result *result)
{
	t_res_content	content;
	t_res_colors	colors;

	get_colors(result, &colors);
	get_content(result, &colors, &content);

	print_stdout("\n   %s╭─────────────────────────────────────────╮%s\n", CYAN, NONE);
	print_stdout("   %s\n", content.title);
	print_stdout("   %s╞════════╤════════╤═══════╤═══════╤═══════╡%s\n", CYAN, NONE);
	print_stdout("   %s %sPASSED %s %sFAILED %s %sTIMED %s %sCRASH %s %sLEAKS %s\n", \
		content.separator, colors.passed, content.separator, colors.failed, \
		content.separator, colors.timed, content.separator, colors.crashed, \
		content.separator, colors.leaks, content.separator);
	print_stdout("   %s├────────┼────────┼───────┼───────┼───────┤%s\n", CYAN, NONE);
	print_stdout("   %s %s %s %s %s\n", content.passed, content.failed, content.timed, content.crashed, content.leaks);
	print_stdout("   %s╰────────┴────────┴───────┴───────┴───────╯%s\n", CYAN, NONE);
}

static inline void	get_colors(const t_result *res, t_res_colors *col)
{
	col->title = res->total == res->passed ? BGREEN : BRED;
	col->passed = res->passed > 0 ? BGREEN : GREY;
	col->failed = res->failed > 0 ? BRED : GREY;
	col->timed = res->timed > 0 ? BRED : GREY;
	col->crashed = res->crashed > 0 ? BRED : GREY;
	col->leaks = res->leaks > 0 ? BRED : GREY;
}

static inline void	get_content(const t_result *res, t_res_colors *colors, t_res_content *cont)
{
	if (res->passed == res->total)
		sprintf(cont->title, "%s│             %s%s CONGRATS! %s             %s│%s", \
			CYAN, EMJ_SUC_START, colors->title, EMJ_SUC_END, CYAN, NONE);
	else
		sprintf(cont->title, "%s│             %s%s TRY AGAIN %s             %s│%s", \
			CYAN, EMJ_FAIL_START, colors->title, EMJ_FAIL_END, CYAN, NONE);

	sprintf(cont->separator, "%s%s%s", CYAN, "│", NONE);

	sprintf(cont->passed, "%s %s%s  %*zu%s", cont->separator, \
		colors->passed, EMJ_PASS, SCORE_DIGITS, res->passed, NONE);
	sprintf(cont->failed, "%s %s%s  %*zu%s", cont->separator, \
		colors->failed, EMJ_FAIL, SCORE_DIGITS, res->failed, NONE);
	sprintf(cont->timed, "%s %s%s %*zu%s", cont->separator, \
		colors->timed, EMJ_TIMD, SCORE_DIGITS, res->timed, NONE);
	sprintf(cont->crashed, "%s %s%s %*zu%s", cont->separator, \
		colors->crashed, EMJ_CRSH, SCORE_DIGITS, res->crashed, NONE);
	sprintf(cont->leaks, "%s %s%s %*zu %s", cont->separator, \
		colors->leaks, EMJ_LEAK, SCORE_DIGITS, res->leaks, cont->separator);
}

```

./3_include/fut.h
```c
#ifndef FUT_H
#define FUT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

/*---------- status/status_pub.h ----------*/

#define STATUS_BUFFER_SIZE 32

typedef enum e_status_type
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	LEAKED,
	DONE,	
}	t_status_type;

typedef struct s_status
{
	t_status_type	type;
	int				sig;
	void			*crash_address;
	size_t			timeout;
}	t_status;

/*---------- result/result_pub.h ----------*/

typedef struct s_result
{
	t_status	status;
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
	size_t		leaks;
}	t_result;

void	result_compute(t_result *res);
void	result_add(const t_result *from, t_result *to);

/*---------- io/redirect_pub.h ----------*/

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH
}	t_redirect_mode;

void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#define get_output(mode, expr, out_var_name)	\
	do											\
	{											\
		redirect_start(mode);					\
		expr;									\
		out_var_name = redirect_read();			\
		redirect_stop();						\
	} while (0)

/*---------- io/print_wrapper_pub.h ----------*/

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fmt, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fmt, ...);

/*---------- process/context_pub.h ----------*/

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

/*---------- process/fork_pub.h ----------*/

void	_fork_init(size_t timeout);

/*---------- logs/format_pub.h ----------*/

typedef enum e_format {
	F_BOOL,
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING,
	F_STRUCT
}	t_format;

/*---------- engine/set_pub.h ----------*/

#if defined(__APPLE__)
	#define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	#define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

typedef void (*t_test_fn)(void);

typedef struct s_set
{
	const char	*name;
	size_t		timeout;
	t_test_fn	func;
	t_result	result;
}	t_set;

#define Test(name, timeout_sec) 						\
	static void name(void); 							\
	static t_set ULT_SECTION _##name##__##__COUNTER__ =	\
	{													\
		#name,											\
		timeout_sec,									\
		name,											\
		{ {QUEUED, 0, 0, 0}, 0, 0, 0, 0, 0, 0 }			\
	};													\
	static void name(void)

/*---------- engine/memcheck_pub.h ----------*/

typedef enum e_mem_mode
{
	LEAKS,
	SAFETY,
}	t_mem_mode;

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr);
void	_memcheck_enable(t_mem_mode mode);
void	_memcheck_child(const char *expr);

#define memleaks(timeout, expr)				\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(LEAKS);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#define memsafety(timeout, expr)			\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(SAFETY);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

/*---------- engine/capture_pub.h ----------*/

typedef enum e_capture_mode
{
	RET,
	OUT,
	ERR,
	BOTH,
	RET_OUT,
	RET_ERR,
	RET_BOTH,
}	t_capture_mode;

static const t_redirect_mode g_capture_to_redirect[] = {
	[RET]		= -1,
    [OUT]       = R_STDOUT,
    [ERR]       = R_STDERR,
    [BOTH]      = R_BOTH,
    [RET_OUT]   = R_STDOUT,
    [RET_ERR]   = R_STDERR,
    [RET_BOTH]  = R_BOTH
};

typedef struct s_capture {
	t_status	status;
	intptr_t	ret;
	char		*out;
} t_capture;

typedef struct s_capture_res
{
	intptr_t	ret;
	char		*out;
}	t_capture_res;

void	_capture_parent(t_capture *capture);
void	_capture_child(t_capture_res *res);

#define __type_is_void(expr) __builtin_types_compatible_p(__typeof__(expr), void)
#define __expr_or_zero(expr) __builtin_choose_expr(__type_is_void(expr), 0, (expr))
#define CAP_VOID(expr, dest) ({ (void)(expr); (dest) = 0; 0; })
#define CAP_VALUE(expr, dest) ({ (dest) = (intptr_t)(__expr_or_zero(expr)); 0; })
#define CAP_DISPATCH(expr, dest)				\
	__builtin_choose_expr(__type_is_void(expr),	\
		CAP_VOID(expr, dest),					\
		CAP_VALUE(expr, dest))

#define capture(mode, timeout_sec, expr, capture_var_name)		\
	do {														\
		memset(&capture_var_name, 0, sizeof capture_var_name);	\
		capture_var_name.status.timeout = timeout_sec;			\
		_fork_init(timeout_sec);								\
		if (g_context.child_pid > 0)							\
			_capture_parent(&capture_var_name);					\
		else													\
		{														\
			t_capture_res capture_res = {0};					\
			if (mode != RET)									\
				redirect_start(g_capture_to_redirect[mode]);	\
			CAP_DISPATCH(expr, capture_res.ret);				\
			if (mode != RET)									\
			{													\
				capture_res.out = redirect_read();				\
				redirect_stop();								\
			}													\
			_capture_child(&capture_res);						\
		}														\
	} while (0)

/*---------- engine/assert_pub.h ----------*/

typedef struct s_assert
{
	t_capture_mode	mode;
	bool			eq;
	const char		*lab;
	t_capture		*got_capt;
	t_capture		*exp_capt;
	t_format		format;
	size_t			ret_size;
}	t_assert;

void	_assert_run(t_assert *assert);

#define _assert(should_be_equal, cap_mode, timeout_sec, label, got_expr, exp_expr)	\
	do {																			\
		t_capture _capt_got = {0};													\
		capture(cap_mode, timeout_sec, (got_expr), _capt_got);						\
																					\
		t_capture _capt_exp = {0};													\
		capture(cap_mode, timeout_sec, (exp_expr), _capt_exp);						\
																					\
		t_assert _assert = {0};														\
		_assert.mode = cap_mode;													\
		_assert.eq = should_be_equal;												\
		_assert.lab = label;														\
		_assert.got_capt = &_capt_got;												\
		_assert.exp_capt = &_capt_exp;												\
		if (__type_is_void(exp_expr) && __type_is_void(got_expr))					\
		{																			\
			_assert.ret_size = sizeof(int);											\
			_assert.format = F_SIGNED;												\
		}																			\
		else																		\
		{																			\
			_assert.ret_size = sizeof(__typeof__(exp_expr)); 						\
			_assert.format = _Generic(__typeof__(exp_expr), 						\
					bool: F_BOOL, 													\
					char: F_CHAR, 													\
					signed char: F_SIGNED, 											\
					short: F_SIGNED, 												\
					int: F_SIGNED, 													\
					long: F_SIGNED, 												\
					long long: F_SIGNED, 											\
					void *: F_HEX,													\
					char *: F_STRING,												\
					const char *: F_STRING,											\
					unsigned char: F_UNSIGNED, 										\
					unsigned short: F_UNSIGNED, 									\
					unsigned int: F_UNSIGNED, 										\
					unsigned long: F_UNSIGNED, 										\
					unsigned long long: F_UNSIGNED, 								\
					unsigned char *: F_STRING,										\
					const unsigned char *: F_STRING,								\
					default: F_HEX);												\
		}																			\
		_assert_run(&_assert);														\
	} while (0)

#define assert(timeout_sec, expr)													\
	_assert(true, RET, timeout_sec, #expr, expr, (bool)true)
#define assert_label(timeout_sec, label, expr)										\
	_assert(true, RET, timeout_sec, label, expr, (bool)true)

#define assert_eq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(true, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_eq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(true, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define assert_neq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(false, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_neq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(false, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define compare(cap_mode, timeout_sec, fn1_name, fn2_name, fn_args)					\
	_assert(true, cap_mode, timeout_sec, #fn1_name#fn_args, fn1_name fn_args, fn2_name fn_args)
#define compare_label(cap_mode, timeout_sec, label, fn1_name, fn2_name, fn_args)	\
	_assert(true, cap_mode, timeout_sec, label, fn1_name fn_args, fn2_name fn_args)

#endif

```

./4_tests/1_basics.c
```c
#include "fut.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void fake_fn(const char *str)
{
	(void)str;
	printf("hey");
}

void fake_fn2(const char *s1, const char *s2)
{
	(void)s1;
	(void)s2;
	printf("hey 2");
}

void	my_void_func(void)
{
	printf("Hello World");
}

int	add(int a, int b)
{
	return (a + b);
}

void just_timeout_bro(void)
{
	int	i = 0;

	(void)i;
	while (true)
		i++;
}

void just_crash_bro(void)
{
	volatile int *oops;

	oops = NULL;
	*oops = 42;
}

void just_timeout_with_arg(int i)
{
	(void)i;
	while (true)
		i++;
}

void just_crash_with_arg(int i)
{
	volatile int *oops;

	oops = NULL;
	*oops = i;
}

/* -------------------- ASSERT & REDIRECT -------------------- */

Test(generic_assert_check, 0)
{
	assert(1, just_timeout_bro());									// TIMED
	assert(0, add(1, 2) > 2 && add(1, 2) < 4);						// PASS
	assert(0, add(1, 2) > 3 && add(1, 2) < 4);						// FAIL
	redirect_start(R_STDOUT);
	assert(0, printf("Hello World") == printf("Hello World"));	// PASS
	assert(0, printf("Hello World") == printf("Not same ret"));	// FAIL
	redirect_stop();
}

/* -------------------- GET_OUTPUT -------------------- */

Test(get_output_check, 0)
{
	char *out1;
	char *out2;
	get_output(R_STDOUT, printf("Hello World"), out1);
	get_output(R_STDOUT, printf("Hello World"), out2);
	assert_eq(RET, 0, out1, out2);							// PASS
	assert(0, strcmp(out1, out2) == 0);			// PASS
	get_output(R_STDOUT, printf("Hello World"), out1);
	get_output(R_STDOUT, printf("Not sameout"), out2);
	assert_eq(RET, 0, out1, out2);							// FAIL
}

/* -------------------- CONST HANDLING -------------------- */

Test(nonvoid_and_constant, 0)
{
	assert_eq(RET, 1, add(1,2), 3);			// TRUE
	assert_neq(RET, 1, add(1,2), 4);			// TRUE
	assert_eq(OUT, 1, add(1,2), 3);			// TRUE
	assert_eq(OUT, 1, add(1,2), 4);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), 3);		// TRUE

	assert_neq(RET, 1, add(1,2), 3);			// FALSE
	assert_eq(RET, 1, add(1,2), 4);			// FALSE
	assert_neq(OUT, 1, add(1,2), 3);			// FALSE
	assert_neq(OUT, 1, add(1,2), 4);			// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), 3);	// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), 4);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), 4);	// FALSE

	// TRUE = 5 | FALSE = 7
}

/* -------------------- VAR HANDLING -------------------- */

Test(nonvoid_and_var, 0)
{
	int exp = 3;

	assert_eq(RET, 1, add(1,2), exp);			// TRUE
	assert_eq(OUT, 1, add(1,2), exp);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), exp);		// TRUE
	assert_neq(RET, 1, add(1,2), exp);			// FALSE
	assert_neq(OUT, 1, add(1,2), exp);			// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), exp);		// FALSE

	exp = 4;
	assert_neq(RET, 1, add(1,2), exp);			// TRUE
	assert_eq(OUT, 1, add(1,2), exp);			// TRUE
	assert_eq(RET, 1, add(1,2), exp);			// FALSE
	assert_neq(OUT, 1, add(1,2), exp);			// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), exp);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), exp);		// FALSE

	// TRUE = 5 | FALSE = 7
}

Test(nonvoid_and_unref, 0)
{
	int exp = 3;
	int *exp_p = &exp;

	assert_eq(RET, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(OUT, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), *exp_p);	// TRUE
	assert_neq(RET, 1, add(1,2), *exp_p);		// FALSE
	assert_neq(OUT, 1, add(1,2), *exp_p);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE

	exp = 4;
	assert_neq(RET, 1, add(1,2), *exp_p);		// TRUE
	assert_eq(OUT, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(RET, 1, add(1,2), *exp_p);			// FALSE
	assert_neq(OUT, 1, add(1,2), *exp_p);		// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE

	// TRUE = 5 | FALSE = 7
}

/* -------------------- TIME OUT -------------------- */

Test(test_time_out_after_asserts, 10)
{
	assert_eq(RET, 1, 1, just_timeout_bro());
	assert_eq(RET, 1, just_timeout_bro(), 1);
	assert_neq(RET, 1, just_timeout_bro(), just_timeout_bro());
}

Test(test_time_out_during_asserts, 4)
{
	assert_eq(RET, 2, 1, just_timeout_bro());
	assert_eq(RET, 2, just_timeout_bro(), 1);
	assert_neq(RET, 2, just_timeout_bro(), just_timeout_bro());
}

Test(test_time_out_before_asserts, 1)
{
	assert_eq(RET, 2, 1, just_timeout_bro());
	assert_eq(RET, 2, just_timeout_bro(), 1);
	assert_neq(RET, 2, just_timeout_bro(), just_timeout_bro());
}

/* -------------------- CRASH -------------------- */

Test(test_crash_after_asserts, 0)
{
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
	just_crash_bro();
}

Test(test_crash_during_asserts, 0)
{
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	just_crash_bro();
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
}

Test(test_crash_before_asserts, 0)
{
	just_crash_bro();
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
}

Test(void_func, 0)
{
	assert_eq(RET_BOTH, 1, my_void_func(), my_void_func());	// PASS
	assert_neq(RET_BOTH, 1, my_void_func(), my_void_func());	// FAIL
}

Test(variadic, 0)
{
	assert_eq(RET_BOTH, 1, printf("%i", 42), printf("%i", 42));	// PASS
	assert_eq(RET_BOTH, 1, printf("%i", 42), printf("%i", -42));	// FAIL
	assert_neq(RET_BOTH, 1, printf("%i", 42), printf("%i", -42));	// PASS
	assert_neq(RET_BOTH, 1, printf("%i", 42), printf("%i", 42));	// FAIL
}

Test(comparison_ok, 0)
{
	compare(RET_BOTH, 1, printf, printf, ("Hello world"));			// PASS
	compare(RET_BOTH, 1, printf, printf, ("%s", "Hello world"));	// PASS
	compare(RET_BOTH, 1, just_timeout_bro, just_timeout_bro, );				// PASS
	compare(RET_BOTH, 1, just_crash_bro, just_crash_bro, );					// PASS
	compare(RET_BOTH, 1, my_void_func, my_void_func, );						// PASS
	
	compare(RET_BOTH, 1, fake_fn, printf, ("Hello world"));	// FAIL
	compare(RET_BOTH, 1, fake_fn2, printf, ("%s", "Hello world"));	// FAIL
	compare(RET_BOTH, 1, just_timeout_bro, my_void_func, );					// FAIL
	compare(RET_BOTH, 1, just_crash_bro, my_void_func, );						// FAIL
	compare(RET_BOTH, 1, my_void_func, just_timeout_bro, );					// FAIL
	compare(RET_BOTH, 1, my_void_func, just_crash_bro, );						// FAIL
	compare(RET_BOTH, 1, just_timeout_bro, just_crash_bro, );					// FAIL
	compare(RET_BOTH, 1, just_crash_bro, just_timeout_bro, );					// FAIL
}

/* -------------------- SIGINT HANDLER -------------------- */

// Test(please_kill_me_to_test_SIGINT_handling, 0)
// {
// 	assert_eq(RET, 0, just_timeout_bro(), just_timeout_bro());
// }

```

./4_tests/1_structs.c
```c
#include "fut.h"

// typedef struct s_test
// {
// 	size_t	a;
// 	size_t	b;
// 	size_t	c;
// 	size_t	d;
// }	t_test;

// t_test	*func_1(size_t a, size_t b)
// {
// 	static t_test test;

// 	test.a = a;
// 	test.b = b;
// 	test.c = a + b;
// 	test.d = a * b;
// 	return (&test);
// }

// t_test	*func_2(size_t a, size_t b)
// {
// 	static t_test test;

// 	test.a = a;
// 	test.b = b;
// 	test.c = a + b;
// 	test.d = a * b;
// 	return (&test);
// }

// Test(struct_same, 0)
// {
// 	t_test	test_a;
// 	t_test	test_b;

// 	test_a.a = 1;
// 	test_a.b = 2;
// 	test_a.c = 3;
// 	test_a.d = 2;
// 	test_b.a = 1;
// 	test_b.b = 2;
// 	test_b.c = 3;
// 	test_b.d = 2;
// 	assert_eq(RET, 0, &test_a, &test_a);						// should PASS -> is PASS
// 	assert_neq(RET, 0, &test_a, &test_a);						// should FAIL -> is FAIL
// 	assert_eq(RET, 0, &test_a, &test_b);						// should PASS -> is FAIL (wrong!)
// 	assert_neq(RET, 0, &test_a, &test_b);						// should FAIL -> is PASS (wrong!)
// }

// Test(struct_diff, 0)
// {
// 	t_test	test_a;
// 	t_test	test_b;

// 	test_a.a = 1;
// 	test_a.b = 2;
// 	test_a.c = 3;
// 	test_a.d = 4;
// 	test_b.a = 1;
// 	test_b.b = 2;
// 	test_b.c = 5;
// 	test_b.d = 6;
// 	assert_eq(RET, 0, &test_a, &test_a);						// should PASS -> is PASS
// 	assert_neq(RET, 0, &test_a, &test_a);						// should FAIL -> is FAIL
// 	assert_eq(RET, 0, &test_a, &test_b);						// should FAIL -> is FAIL
// 	assert_neq(RET, 0, &test_a, &test_b);						// should PASS -> is PASS
// }

// Test(struct_from_fn_ok, 0)
// {
// 	assert_eq(RET, 0, func_1(1, 2), func_2(1, 2));		// should PASS -> is PASS
// 	assert_neq(RET, 0, func_1(1, 2), func_2(1, 2));	// should FAIL -> is FAIL
// }

// Test(struct_from_fn_bug, 0)
// {
// 	assert_eq(RET, 0, func_1(1, 2), func_2(2, 3));		// should FAIL -> is PASS (wrong!)
// 	assert_neq(RET, 0, func_1(1, 2), func_2(2, 3));	// should PASS -> is FAIL (wrong!)
// }

```

./4_tests/3_memcheck.c
```c
#include "fut.h"
#include <stdlib.h>

void	correct_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	if (!nb)
		return;
	*nb = 5;
	free(nb);
}

void	no_free_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	nb = malloc(sizeof(int));
	if (!nb)
		return;
	*nb = 5;
}

void	unsafe_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	*nb = 5;
	free(nb);
}

void	worst_func(void)
{
	int	*nb;

	nb = malloc(sizeof(int));
	*nb = 5;
}

void just_timeout_dude(void)
{
	int	i = 0;

	(void)i;
	while (true)
		i++;
}

/* --------------------- TESTS --------------------- */

Test(correct, 0)
{
	memleaks(0, correct_func());
	memsafety(0, correct_func());
}

Test(no_free, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memsafety(0, no_free_func());
	memleaks(0, correct_func());
}

Test(unsafe, 0)
{
	memleaks(0, correct_func());
	memleaks(0, unsafe_func());
	memsafety(0, unsafe_func());
	memleaks(0, correct_func());
}

Test(both, 0)
{
	memleaks(0, correct_func());
	memleaks(0, worst_func());
	memsafety(0, worst_func());
	memleaks(0, correct_func());
}

Test(timeout_set, 2)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	just_timeout_dude();
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(crash_set, 0)
{
	int	*nul;

	nul = NULL;

	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	*nul = 5;
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(timeout_leaks, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memleaks(2, just_timeout_dude());
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

Test(timeout_safety, 0)
{
	memleaks(0, correct_func());
	memleaks(0, no_free_func());
	memsafety(2, just_timeout_dude());
	memleaks(0, no_free_func());
	memleaks(0, correct_func());
}

```

./4_tests/4_redirect.c
```c
#include "fut.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

Test(Redirect_stdout, 0)
{
	char	*output;

	output = NULL;

	printf("\n1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_STDOUT);

	printf("\n12\n");
	fprintf(stderr, "5\n");
	print_stdout("6\n");
	print_stderr("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	print_stdout("10\n");
	print_stderr("11\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Redirect_stderr, 0)
{
	char	*output;

	output = NULL;

	printf("\n1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_STDERR);

	printf("5\n");
	fprintf(stderr, "12\n");
	print_stdout("6\n");
	print_stderr("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	print_stdout("10\n");
	print_stderr("11\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Redirect_both, 0)
{
	char	*output;

	output = NULL;

	printf("\n1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_BOTH);

	printf("\n11\n");
	fprintf(stderr, "12\n");
	print_stdout("5\n");
	print_stderr("6\n");

	output = redirect_read();
	redirect_stop();

	printf("7\n");
	fprintf(stderr, "8\n");
	print_stdout("9\n");
	print_stderr("10\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Stacked_redirections, 0)
{
	char	*output1;
	char	*output2;

	output1 = NULL;
	output2 = NULL;

	printf("\n1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_BOTH);
	printf("\n14\n");

	redirect_start(R_STDERR);
	fprintf(stderr, "13\n");

	print_stdout("5\n");
	print_stderr("6\n");

	output1 = redirect_read();
	redirect_stop();

	print_stdout("7\n");
	print_stderr("8\n");

	output2 = redirect_read();
	redirect_stop();

	printf("9\n");
	fprintf(stderr, "10\n");
	print_stdout("11\n");
	print_stderr("12\n");

	if (output1)
		printf("%s", output1);
	else
	 	printf("No output1\n");
	if (output2)
		printf("%s", output2);
	else
	 	printf("No output2\n");
	
	if (output1)
		free(output1);
	if (output2)
		free(output2);
}

```

./4_tests/5_old.c
```c
#include "fut.h"

// Test(unnamed, 0)
// {

// 	assert_eq("assert_eq(expl char)", (char)'a', (char)'a');
// 	assert_eq("assert_eq(expl signed char)", (signed char)'a', (signed char)'a');
// 	assert_eq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

// 	assert_eq("assert_eq(expl short)", (short)-42, (short)-42);
// 	assert_eq("assert_eq(expl signed short)", (signed short)-42, (signed short)-42);
// 	assert_eq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

// 	assert_eq("assert_eq(impl bool)", true, true);
// 	assert_eq("assert_eq(expl bool)", (bool)true, (bool)true);

// 	assert_eq("assert_eq(impl int)", -42, -42);
// 	assert_eq("assert_eq(expl int)", (int)-42, (int)-42);
// 	assert_eq("assert_eq(expl signed int)", (signed int)-42, (signed int)-42);
// 	assert_eq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

// 	assert_eq("assert_eq(expl long)", (long)-42, (long)-42);
// 	assert_eq("assert_eq(expl signed long)", (signed long)-42, (signed long)-42);
// 	assert_eq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

// 	assert_eq("assert_eq(expl long long)", (long long)-42, (long long)-42);
// 	assert_eq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
// 	assert_eq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

// 	assert_eq("assert_eq(expl size_t)", (size_t)42, (size_t)42);

// 	assert_eq("assert_eq(impl NULL *)", NULL, NULL);
// 	assert_eq("assert_eq(expl NULL *)", (void *)NULL, (void *)NULL);

// 	int stack = 0;
// 	assert_eq("assert_eq(impl stack *)", &stack, &stack);
// 	assert_eq("assert_eq(expl stack int *)", (int *)&stack, (int *)&stack);
// 	assert_eq("assert_eq(expl stack void *)", (void *)&stack, (void *)&stack);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_eq("assert_eq(impl heap *)", &heap, &heap);
// 	assert_eq("assert_eq(expl heap int *)", (int *)&heap, (int *)&heap);
// 	assert_eq("assert_eq(expl heap void *)", (void *)&heap, (void *)&heap);
// 	free (heap);

// 	assert_eq("assert_eq(impl char *)", "42", "42");
// 	assert_eq("assert_eq(expl char *)", (char *)"42", (char *)"42");
// 	assert_eq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
// 	assert_eq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
// }

// Test(eq_fail, 0)
// {
// 	assert_eq("assert_eq(impl char)", 'a', 'b');
// 	assert_eq("assert_eq(expl char)", (char)'a', (char)'b');
// 	assert_eq("assert_eq(expl signed char)", (signed char)'a', (signed char)'b');
// 	assert_eq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

// 	assert_eq("assert_eq(expl short)", (short)-42, (short)-1);
// 	assert_eq("assert_eq(expl signed short)", (signed short)-42, (signed short)-1);
// 	assert_eq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

// 	assert_eq("assert_eq(impl bool)", true, false);
// 	assert_eq("assert_eq(expl bool)", (bool)true, (bool)false);

// 	assert_eq("assert_eq(impl int)", -42, -1);
// 	assert_eq("assert_eq(expl int)", (int)-42, (int)-1);
// 	assert_eq("assert_eq(expl signed int)", (signed int)-42, (signed int)-1);
// 	assert_eq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

// 	assert_eq("assert_eq(expl long)", (long)-42, (long)-1);
// 	assert_eq("assert_eq(expl signed long)", (signed long)-42, (signed long)-1);
// 	assert_eq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

// 	assert_eq("assert_eq(expl long long)", (long long)-42, (long long)-1);
// 	assert_eq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
// 	assert_eq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

// 	assert_eq("assert_eq(expl size_t)", (size_t)42, (size_t)1);

// 	int stack = 0;
// 	assert_eq("assert_eq(impl stack *)", &stack, NULL);
// 	assert_eq("assert_eq(expl stack int *)", (int *)&stack, (int *)NULL);
// 	assert_eq("assert_eq(expl stack void *)", (void *)&stack, (void *)NULL);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_eq("assert_eq(impl heap *)", &heap, NULL);
// 	assert_eq("assert_eq(expl heap int *)", (int *)&heap, (int *)NULL);
// 	assert_eq("assert_eq(expl heap void *)", (void *)&heap, (void *)NULL);
// 	free (heap);

// 	assert_eq("assert_eq(impl char *)", "42", "1");
// 	assert_eq("assert_eq(expl char *)", (char *)"42", (char *)"1");
// 	assert_eq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
// 	assert_eq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
// }

// Test(neq_fail, 0)
// {
// 	assert_neq("assert_eq(impl char)", 'a', 'a');
// 	assert_neq("assert_eq(expl char)", (char)'a', (char)'a');
// 	assert_neq("assert_eq(expl signed char)", (signed char)'a', (signed char)'a');
// 	assert_neq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

// 	assert_neq("assert_eq(expl short)", (short)-42, (short)-42);
// 	assert_neq("assert_eq(expl signed short)", (signed short)-42, (signed short)-42);
// 	assert_neq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

// 	assert_neq("assert_eq(impl bool)", true, true);
// 	assert_neq("assert_eq(expl bool)", (bool)true, (bool)true);

// 	assert_neq("assert_eq(impl int)", -42, -42);
// 	assert_neq("assert_eq(expl int)", (int)-42, (int)-42);
// 	assert_neq("assert_eq(expl signed int)", (signed int)-42, (signed int)-42);
// 	assert_neq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

// 	assert_neq("assert_eq(expl long)", (long)-42, (long)-42);
// 	assert_neq("assert_eq(expl signed long)", (signed long)-42, (signed long)-42);
// 	assert_neq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

// 	assert_neq("assert_eq(expl long long)", (long long)-42, (long long)-42);
// 	assert_neq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
// 	assert_neq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

// 	assert_neq("assert_eq(expl size_t)", (size_t)42, (size_t)42);

// 	assert_neq("assert_eq(impl NULL *)", NULL, NULL);
// 	assert_neq("assert_eq(expl NULL *)", (void *)NULL, (void *)NULL);

// 	int stack = 0;
// 	assert_neq("assert_eq(impl stack *)", &stack, &stack);
// 	assert_neq("assert_eq(expl stack int *)", (int *)&stack, (int *)&stack);
// 	assert_neq("assert_eq(expl stack void *)", (void *)&stack, (void *)&stack);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_neq("assert_eq(impl heap *)", &heap, &heap);
// 	assert_neq("assert_eq(expl heap int *)", (int *)&heap, (int *)&heap);
// 	assert_neq("assert_eq(expl heap void *)", (void *)&heap, (void *)&heap);
// 	free (heap);

// 	assert_neq("assert_eq(impl char *)", "42", "42");
// 	assert_neq("assert_eq(expl char *)", (char *)"42", (char *)"42");
// 	assert_neq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
// 	assert_neq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
// }

// Test(neq_pass, 0)
// {
// 	assert_neq("assert_eq(impl char)", 'a', 'b');
// 	assert_neq("assert_eq(expl char)", (char)'a', (char)'b');
// 	assert_neq("assert_eq(expl signed char)", (signed char)'a', (signed char)'b');
// 	assert_neq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

// 	assert_neq("assert_eq(expl short)", (short)-42, (short)-1);
// 	assert_neq("assert_eq(expl signed short)", (signed short)-42, (signed short)-1);
// 	assert_neq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

// 	assert_neq("assert_eq(impl bool)", true, false);
// 	assert_neq("assert_eq(expl bool)", (bool)true, (bool)false);

// 	assert_neq("assert_eq(impl int)", -42, -1);
// 	assert_neq("assert_eq(expl int)", (int)-42, (int)-1);
// 	assert_neq("assert_eq(expl signed int)", (signed int)-42, (signed int)-1);
// 	assert_neq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

// 	assert_neq("assert_eq(expl long)", (long)-42, (long)-1);
// 	assert_neq("assert_eq(expl signed long)", (signed long)-42, (signed long)-1);
// 	assert_neq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

// 	assert_neq("assert_eq(expl long long)", (long long)-42, (long long)-1);
// 	assert_neq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
// 	assert_neq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

// 	assert_neq("assert_eq(expl size_t)", (size_t)42, (size_t)1);

// 	int stack = 0;
// 	assert_neq("assert_eq(impl stack *)", &stack, NULL);
// 	assert_neq("assert_eq(expl stack int *)", (int *)&stack, (int *)NULL);
// 	assert_neq("assert_eq(expl stack void *)", (void *)&stack, (void *)NULL);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_neq("assert_eq(impl heap *)", &heap, NULL);
// 	assert_neq("assert_eq(expl heap int *)", (int *)&heap, (int *)NULL);
// 	assert_neq("assert_eq(expl heap void *)", (void *)&heap, (void *)NULL);
// 	free (heap);

// 	assert_neq("assert_eq(impl char *)", "42", "1");
// 	assert_neq("assert_eq(expl char *)", (char *)"42", (char *)"1");
// 	assert_neq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
// 	assert_neq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
// }

```

