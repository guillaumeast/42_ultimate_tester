#define __FUT_ENGINE_INSIDE__
#include "compare_int.h"
#undef __FUT_ENGINE_INSIDE__

#include <stdbool.h>
#include <string.h>

bool	compare_status(t_status *s1, t_status *s2)
{
	if (s1->type == CRASHED && s2->type == CRASHED)
		return (s1->sig == s2->sig);
	else
	 	return (s1->type == s2->type);
}

bool	compare_strings(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (!s1 && !s2);

	return (strcmp(s1, s2) == 0);
}

bool	compare_intptr_t(intptr_t i1, intptr_t i2)
{
	return (i1 == i2);
}

bool	compare_structs(void *s1, void *s2, size_t struct_size)
{
	if (!s1 || !s2)
		return (!s1 && !s2);
	
	return (memcmp(s1, s2, struct_size) == 0);
}
