#ifndef LIB_ULTIMATE_TESTER_RUN_H
# define LIB_ULTIMATE_TESTER_RUN_H

# include "types.h"
# include "utils.h"
# include "redirect.h"

t_set	*get_current_set();
void	set_current_set(t_set *set);
void	test_init(t_set *set, t_test *test);
void	test_check(t_test *test);

#endif
