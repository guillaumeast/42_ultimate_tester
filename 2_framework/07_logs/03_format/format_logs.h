#ifndef ULT_FORMAT_LOGS_H
#define ULT_FORMAT_LOGS_H

#ifndef __FUT_LOGS_INSIDE__
/*
**  Private header for the LOGS module.
**  Not available outside its compilation unit.
*/
#else

#include "format_priv.h"
#include "status_pub.h"
#include <stdarg.h>

const char	*format_h1(const char *fmt, va_list args);
const char	*format_h2(const char *fmt, va_list args);
const char	*format_indicator(t_status *status);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORMAT_LOGS_H */
