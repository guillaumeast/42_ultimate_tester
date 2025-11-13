#ifndef ULT_COMP_PUB_H
# define ULT_COMP_PUB_H

# include "print_pub.h"
# include "set_pub.h"
# include <stdlib.h>

typedef enum e_comp_mode
{
	COMP_RET,
	COMP_OUT,
	COMP_ERR,
	COMP_BOTH,
	COMP_RET_OUT,
	COMP_RET_ERR,
	COMP_RET_BOTH,
}	t_comp_mode;

typedef struct s_function
{
	char		*name;
	char		*args;
	intptr_t	ret;
	t_string	*out;
}	t_function;

typedef struct s_compare
{
	t_status	status;
	t_comp_mode	mode;
	t_function	fn1;
	t_function	fn2;
}	t_compare;

void	_run_compare_parent(pid_t pid);
void	_run_compare_child(t_compare *comp);

/*
** TODO: Don't fail if redirect_start() is called when redirect is already activ
**	INSTEAD: store old redirect and create a new one
**	THEN: restore previous redirect when the new one is stopped
**	(OR create tmp_redirect_start() / tmp_redirect_stop() funcs ?)
*/ 
# define _redirect_start()										\
	if (_comp.mode == COMP_OUT || _comp.mode == COMP_RET_OUT)	\
		redirect_start(R_STDOUT);								\
	if (_comp.mode == COMP_ERR || _comp.mode == COMP_RET_ERR)	\
		redirect_start(R_STDERR);								\
	if (_comp.mode == COMP_BOTH || _comp.mode == COMP_RET_BOTH)	\
		redirect_start(R_BOTH);

# define _get_values(fn_id, fn_name, fn_args)											\
	if (_comp.mode != COMP_OUT && _comp.mode != COMP_ERR && _comp.mode != COMP_BOTH)	\
		_comp.fn##fn_id.ret = (intptr_t)fn_name fn_args;								\
	if (_comp.mode != COMP_RET)															\
		_comp.fn##fn_id.out = redirect_read();

/*
** Usage: compare2(COMP_OUT, fn1, fn2, (fn1_args), (fn2_args));
**
** ⚠️ The argument(s) must always be enclosed in parentheses.
** Otherwise, the macro expansion will be invalid C syntax.
*/
# define compare2(cmp_mode, fn1_name, fn2_name, fn1_args, fn2_args)	\
	do																\
	{																\
		pid_t		pid;											\
		t_compare	_comp = {0};									\
																	\
		_comp.status = QUEUED;										\
		_comp.mode = cmp_mode;										\
		_comp.fn1.name = #fn1_name;									\
		_comp.fn2.name = #fn2_name;									\
		_comp.fn1.args = #fn1_args;									\
		_comp.fn2.args = #fn2_args;									\
																	\
		pid = fork();												\
		if (pid < 0)												\
		{															\
			ult_err_priv("Fork failed. Please report this issue.");		\
			exit(EXIT_FAILURE);										\
		}															\
																	\
		if (pid > 0)												\
			_run_compare_parent(pid);								\
		else														\
		{															\
			/* TODO: create pipe */									\
			_redirect_start()										\
			_get_values(1, fn1_name, fn1_args)						\
			_get_values(2, fn2_name, fn2_args)						\
			if (cmp_mode != COMP_RET) redirect_stop();				\
			_run_compare_child(&_comp);								\
		}															\
	} while (0)

/*
** Usage: compare(COMP_OUT, fn1, fn2, (arg1, arg2, ...));
**
** ⚠️ The argument(s) must always be enclosed in parentheses.
** Otherwise, the macro expansion will be invalid C syntax.
*/
# define compare(mode, fn1_name, fn2_name, fn_args)	\
	compare2(mode, fn1_name, fn2_name, fn_args, fn_args)

#endif
