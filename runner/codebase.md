./ft_ultimate_tester.h
```c
#ifndef FT_ULTIMATE_TESTER_H
# define FT_ULTIMATE_TESTER_H

# include "set_pub.h"
# include "redirect_pub.h"
# include "assert_pub.h"
# include "print_pub.h"

#endif

```

./print/includes/print_pub.h
```c
#ifndef ULT_PRINT_PUB_H
# define ULT_PRINT_PUB_H

# include "redirect_pub.h"

void	ult_fprintf(t_ult_fd fd, const char *fmt, ...);

#define ult_print(fmt, ...) \
	ult_fprintf(ULT_STDOUT, fmt "%s", ##__VA_ARGS__, NONE)

#endif

```

./print/includes/print_priv.h
```c
#ifndef ULT_PRINT_PRIV_H
# define ULT_PRINT_PRIV_H

# include "print_pub.h"
# include "set_priv.h"
# include <locale.h>
# include <string.h>
# include <unistd.h>

typedef struct s_tab_colors
{
	char	*borders;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed;
}	t_tab_colors;

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*green;
	char	*yellow;
	char	*blue;
	char	*none;
}	t_colors;

typedef struct s_emojis
{
	char	*error;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

extern t_colors	colors;
extern t_emojis	emojis;

# define GREY	colors.grey
# define RED	colors.red
# define GREEN	colors.green
# define YELLOW	colors.yellow
# define BLUE	colors.blue
# define NONE	colors.none

# define EMJ_ERR		(emojis.error)
# define EMJ_SUC_START	(emojis.success_title_start)
# define EMJ_SUC_END	(emojis.success_title_end)
# define EMJ_FAIL_START	(emojis.fail_title_start)
# define EMJ_FAIL_END	(emojis.fail_title_end)

#define ult_err(fmt, ...) \
	ult_fprintf(ULT_STDERR, "%s %s Error: " fmt "%s\n", RED, EMJ_ERR, ##__VA_ARGS__, NONE)

void	print_set_title(const t_set *set);
void	print_set_result(const t_result *result);
void	print_result(const t_result *result);

static inline void	print_init_format()
{
	bool		istty;
	bool		isutf8;
	const char	*locale;

	istty = isatty(STDOUT_FILENO);
	colors.grey =	istty ? "\033[90m" : "";
	colors.red =	istty ? "\033[31m" : "";
	colors.green =	istty ? "\033[32m" : "";
	colors.yellow =	istty ? "\033[33m" : "";
	colors.blue =	istty ? "\033[34m" : "";
	colors.none =	istty ? "\033[0m" : "";

	setlocale(LC_CTYPE, "");
	locale = setlocale(LC_CTYPE, NULL);
	isutf8 = locale && strstr(locale, "UTF-8");
	emojis.error =					isutf8 ? "❗️" : "✖";
	emojis.success_title_start =	isutf8 ? "🎉" : "✖";
	emojis.success_title_end =		isutf8 ? "🚀" : "✖";
	emojis.fail_title_start =		isutf8 ? "💥" : "✖";
	emojis.fail_title_end =			isutf8 ? "😈" : "✖";
}

#endif

```

./print/srcs/print.c
```c
#include "print_priv.h"
#include "redirect_priv.h"
#include <stdarg.h>

#define TITLE_MAX_LEN 29
#define SCORE_LEN 3
#define size_t_to_string(nb, var)										\
	char	var[(SCORE_LEN) + 1] = {0};									\
	snprintf(var, sizeof(var), "%*zu", (int)(SCORE_LEN), (size_t)(nb))

static inline void	get_tab_colors(const t_result *result, t_tab_colors *tab_colors);

/*-------------- TODO SECTION (START) --------------*/

// TODO: update all printf()/fprintf() calls to ult_fprintf() calls

// Make it visible to user
void	ult_fprintf(t_ult_fd fd, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	if (fd == ULT_STDOUT)
		vdprintf(g_output.real_stdout_fd, fmt, args);
	else
		vdprintf(g_output.real_stderr_fd, fmt, args);
	va_end(args);
}

void	print_set_title(const t_set *set)
{
	char	title[TITLE_MAX_LEN + 1];
	size_t	i;

	i = 0;
	while (i < TITLE_MAX_LEN && set->name[i])
	{
		title[i] = set->name[i];
		i++;
	}
	while (i < TITLE_MAX_LEN)
		title[i++] = ' ';
	title[i] = '\0';
	printf(" %s┌-------------------------------┐%s\n", BLUE, NONE);
	printf(" %s|%s %s %s|%s\n", BLUE, BLUE, title, BLUE, NONE);
	printf(" %s├-------------------------------┘%s\n", BLUE, NONE);
}

void	print_result(const t_result *result)
{
	t_tab_colors	tab_colors;

	size_t_to_string(result->passed, passed);
	size_t_to_string(result->failed, failed);
	size_t_to_string(result->timed, timed);
	size_t_to_string(result->crashed, crashed);
	get_tab_colors(result, &tab_colors);
	printf("\n %s┌-----------------------------------┐%s\n", tab_colors.borders, NONE);
	if (result->total == result->passed)
		printf(" %s|          %s YOU WON! %s           |%s\n", \
			tab_colors.borders, EMJ_SUC_START, EMJ_SUC_END, NONE);
	else
		printf(" %s|          %s TRY AGAIN %s          |%s\n", \
			tab_colors.borders, EMJ_FAIL_START, EMJ_FAIL_END, NONE);
	printf(" %s├--------┬--------┬-------┬---------┤%s\n", tab_colors.borders, NONE);
	printf(" %s|%s PASSED %s|%s FAILED %s|%s TIMED %s|%s CRASHED %s|%s\n", \
		tab_colors.borders, tab_colors.passed, tab_colors.borders, \
		tab_colors.failed, tab_colors.borders, tab_colors.timed, \
		tab_colors.borders, tab_colors.crashed, tab_colors.borders, NONE);
	printf(" %s├--------┼--------┼-------┼---------┤%s\n", tab_colors.borders, NONE);
	printf(" %s|%s ✔  %s %s|%s ✖  %s %s|%s ⊘ %s %s|%s ☠   %s %s|%s\n", \
		tab_colors.borders, tab_colors.passed, passed, tab_colors.borders, \
		tab_colors.failed, failed, tab_colors.borders, tab_colors.timed, \
		timed, tab_colors.borders, tab_colors.crashed, crashed, tab_colors.borders, NONE);
	printf(" %s└--------┴--------┴-------┴---------┘%s\n", tab_colors.borders, NONE);
}

static inline void	get_tab_colors(const t_result *result, t_tab_colors *tab_colors)
{
	if (!result || !tab_colors)
		return ;
	tab_colors->borders = GREY;
	tab_colors->passed = GREY;
	tab_colors->failed = GREY;
	tab_colors->timed = GREY;
	tab_colors->crashed = GREY;
	if (result->total == result->passed)
	{
		tab_colors->borders = GREEN;
		tab_colors->passed = GREEN;
	}
	else
		tab_colors->borders = RED;
	if (result->failed > 0)
		tab_colors->failed = RED;
	if (result->timed > 0)
		tab_colors->timed = RED;
	if (result->crashed > 0)
		tab_colors->crashed = RED;
}

/*-------------- TODO SECTION (END) --------------*/

```

./redirect/includes/fd_priv.h
```c
#ifndef ULT_FD_PRIV_H
# define ULT_FD_PRIV_H

#include <stdbool.h>

bool	switch_file_descriptors(void);
void	reset_file_descriptor(int *original_fd, int target_fd);

#endif

```

./redirect/includes/redirect_pub.h
```c
#ifndef ULT_REDIRECT_PUB_H
# define ULT_REDIRECT_PUB_H

# include <stdbool.h>
# include <stdio.h>

typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

typedef enum e_ult_fds
{
	ULT_STDOUT,
	ULT_STDERR,
}	t_ult_fd;

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH,
	R_NULL,
}	t_redirect_mode;

typedef struct s_redirect	t_redirect;

bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read();
void		redirect_stop(void);

#endif

```

./redirect/includes/file_priv.h
```c
#ifndef ULT_FILE_PRIV_H
# define ULT_FILE_PRIV_H

#include <stdbool.h>
#include <stdio.h>

bool	create_tmp_file(void);
ssize_t	file_get_len(FILE *f);
bool	file_reset(FILE *f);
void	flush_all();

#endif

```

./redirect/includes/redirect_priv.h
```c
#ifndef ULT_REDIRECT_PRIV_H
# define ULT_REDIRECT_PRIV_H

# include "redirect_pub.h"

typedef struct s_redirect
{
	bool			activ;
	t_redirect_mode mode;
	int				real_stdout_fd;
	int				real_stderr_fd;
	FILE			*out_file;
	int				out_fd;
}	t_redirect;

extern t_redirect	g_output;

bool	redirect_init(void);

#endif

```

./redirect/srcs/fd.c
```c
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

```

./redirect/srcs/redirect.c
```c
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

```

./redirect/srcs/file.c
```c
#include "file_priv.h"
#include "redirect_priv.h"
#include <unistd.h>

bool	create_tmp_file(void)
{
	if (!(g_output.out_file = tmpfile()))
		return (false);
	g_output.out_fd = fileno(g_output.out_file);
	return (g_output.out_fd != -1);
}

ssize_t file_get_len(FILE *f)
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

bool	file_reset(FILE *f)
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

// Delete because all I/0 are already unbuffered ?
void	flush_all()
{
	fflush(stdout);
	fflush(stderr);
	if (g_output.activ)
		fflush(g_output.out_file);
}

```

./run/includes/assert_pub.h
```c
#ifndef ULT_ASSERT_PUB_H
# define ULT_ASSERT_PUB_H

# include <stdbool.h>
# include <stdint.h>

typedef enum e_format {
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING
}	t_format;

void	ult_assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);

#define ult_assert(should_be_equal, name, got, expected) \
	ult_assert_run(should_be_equal, name, (intptr_t)(got), (intptr_t)(expected), \
		_Generic((expected), \
			char: F_CHAR, \
			signed char: F_SIGNED, \
			short: F_SIGNED, \
			int: F_SIGNED, \
			long: F_SIGNED, \
			long long: F_SIGNED, \
			unsigned char: F_UNSIGNED, \
			unsigned short: F_UNSIGNED, \
			unsigned int: F_UNSIGNED, \
			unsigned long: F_UNSIGNED, \
			unsigned long long: F_UNSIGNED, \
			char *: F_STRING, \
			const char *: F_STRING, \
			default: F_HEX))
#define assert_eq(name, got, expected) _ult_assert(true, name, got, expected)
#define assert_neq(name, got, expected) _ult_assert(false, name, got, expected)

#endif

```

./run/includes/set_pub.h
```c
#ifndef ULT_SET_PUB_H
# define ULT_SET_PUB_H

# include <stddef.h>

#if defined(__APPLE__)
	# define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	# define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

typedef void (*t_test_fn)(void);

typedef enum e_status
{
	QUEUED,
	RUNNING,
	DONE,
}	t_status;

typedef struct s_set
{
	char		*name;
	size_t		timeout;
	t_status	status;
	t_test_fn	func;
}	t_set;

// Usage: Test(const char *name, size_t timeout)
# define Test(name, timeout) 				\
	static void name(void); 				\
	static t_set ULT_SECTION t_##name =		\
	{										\
		#name,								\
		timeout,							\
		QUEUED,								\
		name,								\
	};										\
	static void name(void)

#endif

```

./run/includes/set_priv.h
```c
#ifndef ULT_SET_PRIV_H
# define ULT_SET_PRIV_H

# include "set_pub.h"

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

void	run_set(t_set *set);

extern t_result	g_result;

#endif

```

./run/srcs/set.c
```c
#include "print_priv.h"
#include <signal.h>
#include <stdlib.h>

static inline void	run_parent(t_set *set, pid_t pid);
static inline void	run_child(t_set *set);
static inline void	handle_timeout(int sig);

static pid_t					current_child_pid = -1;
static volatile sig_atomic_t	timeout_triggered = false;

void	run_set(t_set *set)
{
	print_set_title(set);
	set->status = RUNNING;
	current_child_pid = fork();
	if (current_child_pid < 0)
		fprintf(stderr, " %s|%s ❗️ Internal error: Fork failed%s\n", GREY, RED, NONE);
	else if (current_child_pid == 0)
		run_child(set);
	else
		run_parent(set, current_child_pid);
	set->status = DONE;
}

static inline void	run_parent(t_set *set, pid_t pid)
{
	int	status;

	timeout_triggered = false;
	signal(SIGALRM, handle_timeout);
	alarm(set->timeout);

	waitpid(pid, &status, 0);
	alarm(0);

	if (timeout_triggered)
		g_result.timed++;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		g_result.passed++;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		g_result.failed++;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)
		g_result.timed++;
	else if (WIFSIGNALED(status))
		g_result.crashed++;

	g_result.total++;

	signal(SIGALRM, SIG_DFL);
	current_child_pid = -1;
}

static inline void	run_child(t_set *set)
{
	set->func();
	exit(EXIT_SUCCESS);
}

static inline void	handle_timeout(int sig)
{
	(void)sig;
	timeout_triggered = true;
    kill(current_child_pid, SIGKILL);
}

```

./run/srcs/assert.c
```c
#include "assert_pub.h"
#include "set_priv.h"
#include "file_priv.h"
#include <inttypes.h>
#include <string.h>

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format fmt);
static inline void	log_fail(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);

void	ult_assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	if (ult_check(got, exp, fmt) == eq)
		g_result.passed++;
	else
	{
	 	g_result.failed++;
		log_fail(eq, name, got, exp, fmt);
	}
}

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format format)
{
	if (format != F_STRING)
	 	return (got == exp);
	if (!got || !exp)
		return (!got && !exp);
	return (strcmp((const char *)got, (const char *)exp) == 0);
}

static inline void	log_fail(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	const char	*format;

	if (fmt == F_SIGNED)			format = "%" PRIdPTR;
	else if (fmt == F_UNSIGNED)	format = "%" PRIuPTR;
	else if (fmt == F_HEX)		format = "%" PRIxPTR;
	else if (fmt == F_CHAR)		format = "%c";
	else if (fmt == F_STRING)	format = "%s";
	else							format = "%" PRIxPTR;

	flush_all();
	fprintf(stderr, " |   ⤷ ✖ %s = ", name);
	fprintf(stderr, format, got);
	fprintf(stderr, eq ? " (expected " : " (expected ≠ ");
	fprintf(stderr, format, exp);
	fprintf(stderr, ")\n");
	flush_all();
}

```

./main/main.c
```c
#include "print_priv.h"
#include "redirect_priv.h"
#include "set_priv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__)
    extern t_set __data_ult_tester_start[] __asm("section$start$__DATA$__ult_tester");
    extern t_set __data_ult_tester_end[]   __asm("section$end$__DATA$__ult_tester");
    # define START_SET __data_ult_tester_start
    # define STOP_SET  __data_ult_tester_end
#else
    extern t_set __start_ult_tester;
    extern t_set __stop_ult_tester;
    # define START_SET  &__start_ult_tester
    # define STOP_SET   &__stop_ult_tester
#endif

__attribute__((constructor))
static void	ult_main(void)
{
	t_set	*set;

	if (START_SET >= STOP_SET)
	{
		fprintf(stderr, "No tests to run\n");
		exit (0);
	}

	if (!redirect_init())
	{
		fprintf(stderr, "Error: Unable to initialize output redirection: please report this issue.");
		exit (1);
	}
	print_init_format();

    for (set = START_SET; set < STOP_SET; set++)
		run_set(set);
	redirect_stop();

	print_result(&g_result);
	exit (0);
}

__attribute__((weak))
int	main(void)
{
	fprintf(stderr, "This message should not appear: please report this issue.\n");
	return (0);
}

```

