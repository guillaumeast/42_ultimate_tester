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

bool	compare_status(const t_status *s1, const t_status *s2);
bool	compare_strings(const char *s1, const char *s2);
bool	compare_intptr_t(intptr_t i1, intptr_t i2);
bool	compare_structs(const void *s1, const void *s2, size_t struct_size);

#endif /* __FUT_ENGINE_INSIDE__ */

#endif /* ULT_CHECK_INTERNAL_H */
