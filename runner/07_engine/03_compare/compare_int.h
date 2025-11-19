#ifndef ULT_COMPARE_INTERNAL_H
#define ULT_COMPARE_INTERNAL_H

#ifndef __FUT_ENGINE_INSIDE__
/*
**  Internal header for the engine subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool	compare_status(t_status *s1, t_status *s2);
bool	compare_strings(char *s1, char *s2);
bool	compare_intptr_t(intptr_t i1, intptr_t i2);
bool	compare_structs(void *s1, void *s2, size_t struct_size);

#endif /* __FUT_ENGINE_INSIDE__ */

#endif /* ULT_CHECK_INTERNAL_H */
