#ifndef ULT_COMP_PUB_H
# define ULT_COMP_PUB_H

# include "fork_pub.h"
# include "error_pub.h"
# include "set_pub.h"
# include <stdlib.h>
# include <signal.h>

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

t_error	comp_init_priv(t_context *cxt, size_t to, t_compare *cmp, t_comp_mode md, char *f1, char *f2, char *a1, char *a2);
t_error	comp_parent_priv(t_context *context, t_compare *data);
t_error	comp_init_child_priv(t_context *context, t_compare *data);
void	comp_child_priv(t_context *context, t_compare *data);

# define cmp_try(call)																		\
	error = (call);																			\
	if (error != NO_ERROR)																	\
	{																						\
		if (cxt.child_pid > 0)																\
			kill(cxt.child_pid, SIGKILL);													\
		ult_print_err_priv(error);															\
		break;																				\
	}

# define get_values_priv(fn_id, fn_name, fn_args)											\
	if (cmp.mode != COMP_OUT && cmp.mode != COMP_ERR && cmp.mode != COMP_BOTH)				\
		cmp.fn##fn_id.ret = (intptr_t)fn_name fn_args;										\
	if (cmp.mode != COMP_RET)																\
		cmp.fn##fn_id.out = redirect_read();

/*
** Usage: compare2(COMP_OUT, 1, fn1, fn2, (fn1_args), (fn2_args));
**
** ⚠️ The argument(s) must always be enclosed in parentheses.
** Otherwise, the macro expansion will be invalid C syntax.
*/
# define compare2(mode, timeout, fn1_name, fn2_name, fn1_args, fn2_args)					\
	do																						\
	{																						\
		t_error		error;																	\
		t_compare	cmp;																	\
		t_context	cxt;																	\
																							\
		cmp_try(comp_init_priv(&cxt, timeout, &cmp, mode, #fn1_name, #fn2_name, #fn1_args, #fn2_args))	\
		if (cxt.child_pid > 0)																\
			cmp_try(comp_parent_priv(&cxt, &cmp))											\
		if (cxt.child_pid == 0)																\
		{																					\
			error = comp_init_child_priv(&cxt, &cmp);										\
			if (error != NO_ERROR)															\
			{																				\
				ult_print_err_priv(error);													\
				exit(EXIT_FAILURE);															\
			}																				\
			get_values_priv(1, fn1_name, fn1_args)											\
			get_values_priv(2, fn2_name, fn2_args)											\
			comp_child_priv(&cxt, &cmp);													\
		}																					\
	} while (0)

/*
** Usage: compare(COMP_OUT, 1, fn1, fn2, (arg1, arg2, ...));
**
** ⚠️ The argument(s) must always be enclosed in parentheses.
** Otherwise, the macro expansion will be invalid C syntax.
*/
# define compare(mode, timeout, fn1_name, fn2_name, fn_args)	\
	compare2(mode, timeout, fn1_name, fn2_name, fn_args, fn_args)

#endif
