#ifndef ULT_FORMAT_PRIV_H
#define ULT_FORMAT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "status_pub.h"

#define H2_CAP 128

const char	*format_addr(void *ptr);
const char	*format_status(t_status *status);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORMAT_PRIV_H */
