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
	char		*name;
	size_t		timeout;
	t_test_fn	func;
	t_result	result;
}	t_set;

// Usage: Test(const char *name, size_t timeout)
#define Test(name, timeout) 							\
	static void name(void); 							\
	static t_set ULT_SECTION _##name##__##__COUNTER__ =	\
	{													\
		#name,											\
		timeout,										\
		QUEUED,											\
		name,											\
		{0, 0, 0, 0, 0}									\
	};													\
	static void name(void)

#endif
