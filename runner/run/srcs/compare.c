#include "comp_pub.h"

/*---------- TMP: HEADER START ----------*/
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
			_redirect_start()										\
			_get_values(1, fn1_name, fn1_args)						\
			_get_values(2, fn2_name, fn2_args)						\
			if (cmp_mode != COMP_RET) redirect_stop();				\
			_run_compare_child(&_comp);								\
		}															\
	} while (0)
/*---------- TMP: HEADER END ----------*/

void	_run_compare_parent(pid_t pid)
{
	// TODO: make handle_alarm() shared to use the same in set fork and compare fork ?
	// TODO: set alarm + handler
	// TODO: wait child
	// TODO: read pipe
	// TODO: close pipe
	// TODO: process result
	// TODO: print result (except for success)
}

void	_run_compare_child(t_compare *comp)
{

}
