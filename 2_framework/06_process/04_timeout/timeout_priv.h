#ifndef ULT_TIMEOUT_PRIV_H
#define ULT_TIMEOUT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <stdbool.h>

bool	timeout_is_triggered(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */
