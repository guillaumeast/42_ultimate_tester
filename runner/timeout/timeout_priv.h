#ifndef ULT_TIMEOUT_PRIV_H
# define ULT_TIMEOUT_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "error_pub.h"
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>

t_error	setup_timeout(pid_t target_pid, unsigned int time);
t_error	cancel_timeout(void);

volatile sig_atomic_t	g_timeout_triggered;

#endif
