#include "ft_ultimate_tester.h"
#include "libftprintf.h"

typedef struct s_compare
{
	char		*fn1_name;
	char		*fn2_name;
	char		*args;
	intptr_t	fn1_ret;
	intptr_t	fn2_ret;
	t_string	*fn1_out;
	t_string	*fn2_out;
}	t_compare;

// TMP for tests
#include "print_priv.h"		// TODO !!
#include <stdlib.h>
void	_run_compare_parent(pid_t pid);			// TODO
void	_run_compare_child(t_compare *comp);	// TODO

/*
** Usage:
**		compare(R_STDOUT, fn1, fn2, (arg1, arg2));
**		compare(R_STDOUT, fn1, fn2, ("simple_arg"));
**
** ⚠️ The argument(s) must always be enclosed in parentheses.
** Otherwise, the macro expansion will be invalid C syntax.
*/
#define compare(ult_fd, fn1, fn2, fn_args)						\
	do															\
	{															\
		pid_t		pid;										\
		t_compare	_comp = {0};								\
																\
		_comp.fn1_name = #fn1;									\
		_comp.fn2_name = #fn2;									\
		_comp.args = #fn_args;									\
																\
		pid = fork();											\
		if (pid < 0)											\
		{														\
			ult_err("Fork failed. Please report this issue.");	\
			exit(EXIT_FAILURE);									\
		}														\
																\
		if (pid > 0)											\
			_run_compare_parent(pid);							\
		else													\
		{														\
			redirect_start(ult_fd);								\
			_comp.fn1_ret = (intptr_t)fn1 fn_args;				\
			_comp.fn1_out = redirect_read();					\
			_comp.fn2_ret = (intptr_t)fn2 fn_args;				\
			_comp.fn2_out = redirect_read();					\
			redirect_stop();									\
			_run_compare_child(&_comp);							\
		}														\
	} while (0)

// TODO: also do `compare2_*(fn1(args1), fn2(args2))` ?

Test(comparison, 0)
{
	// Naming: compare_* / comp_* / cmp_* / ult_comp_* / ultcmp_* ?

	// Usage: compare_ret(fn1, fn2, args...)
	// Usage: compare_out(fn1, fn2, args...)
	// Usage: compare_err(fn1, fn2, args...)
	// + Combinaisons (ret + out / ret + err / ret + out + err / out + err)

	compare(R_BOTH, printf, ft_printf, ("42"));
}
