#ifndef FT_ULTIMATE_TESTER_H
# define FT_ULTIMATE_TESTER_H

/*
bool		redirect_start(t_redirect_mode mode);
t_string	*redirect_read();
void		redirect_stop();
*/
# include "redirect.h"

#if defined(__APPLE__)
	# define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	# define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

// Test(const char *name, size_t timeout)
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
