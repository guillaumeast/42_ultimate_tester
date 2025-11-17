#ifndef ULT_TIMEOUT_PRIV_H
#define ULT_TIMEOUT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include <signal.h>

extern volatile sig_atomic_t	g_timeout_triggered;

#endif /* __FUT_INSIDE__ */

#endif /* ULT_TIMEOUT_PRIV_H */
