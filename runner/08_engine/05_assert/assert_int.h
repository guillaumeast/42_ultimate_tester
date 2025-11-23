#ifndef ULT_ASSERT_INTERNAL_H
#define ULT_ASSERT_INTERNAL_H

#ifndef __FUT_ASSERT_INSIDE__
/*
**  Internal header for the assert module.
**  Not available outside its compilation unit.
*/
#else

#include "assert_pub.h"
#include "status_pub.h"

t_status	assert_check_eq(t_assert *assert);
t_status	assert_check_neq(t_assert *assert);

#endif /* __FUT_ASSERT_INSIDE__ */

#endif /* ULT_ASSERT_INTERNAL_H */
