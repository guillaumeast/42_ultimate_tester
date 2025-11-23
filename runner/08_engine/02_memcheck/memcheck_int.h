#ifndef ULT_MEMCHECK_INTERNAL_H
#define ULT_MEMCHECK_INTERNAL_H

#ifndef __FUT_MEMCHECK_INSIDE__
/*
**  Internal header for the memcheck module.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"
#include <stddef.h>

typedef struct s_leak
{
	void	*ptr;
	size_t	size;
	void	*caller;
}	t_leak;

extern t_leak	*g_leaks_table;
extern size_t	g_leaks_count;

void	memcheck_enable(void);
void	memcheck_disable(void);
void	register_alloc(void *ptr, size_t size, void *caller);
void	register_free(void *ptr);

#endif /* __FUT_MEMCHECK_INSIDE__ */

#endif /* ULT_MEMCHECK_INTERNAL_H */
