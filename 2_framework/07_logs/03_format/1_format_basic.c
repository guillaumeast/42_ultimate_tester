#define __FUT_INSIDE__
#define __FUT_IO_INSIDE__
#define __FUT_LOGS_INSIDE__
#include "colors_priv.h"
#include "emojis_priv.h"
#include "format_logs.h"
#include "status_pub.h"
#undef __FUT_INSIDE__
#undef __FUT_IO_INSIDE__
#undef __FUT_LOGS_INSIDE__

#include <stdarg.h>
#include <stdio.h>

#define H1_CAP 256
#define INDICATOR_CAP 16

const char	*format_h1(const char *fmt, va_list args)
{
	static char	buff[H1_CAP];
	size_t	offset;

	offset = snprintf(buff, sizeof buff, " %s%s%s ", GREY, EMJ_ARW_RIGHT, BBLUE);
	offset += vsnprintf(buff + offset, sizeof buff - offset, fmt, args);
	(void)snprintf(buff + offset, sizeof buff - offset, "%s", NONE);

	return (buff);
}

const char	*format_indicator(t_status *status)
{
	static char buff[INDICATOR_CAP];

	switch (status->type)
	{
		case PASSED:	snprintf(buff, sizeof buff, "%s%s%s ", GREEN, EMJ_PASS, NONE); break;
		case FAILED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_FAIL, NONE); break;
		case TIMED:		snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_TIMD, NONE); break;
		case CRASHED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_CRSH, NONE); break;
		case LEAKED:	snprintf(buff, sizeof buff, "%s%s%s ", RED, EMJ_LEAK, NONE); break;
		default:		buff[0] = '\0'; break;
	}
	return (buff);
}

const char	*format_h2(const char *fmt, va_list args)
{
	static char	buff[H2_CAP];
	size_t	offset;

	offset = snprintf(buff, sizeof buff, "    %s%s%s ", GREY, EMJ_ARW_DR, NONE);
	offset += vsnprintf(buff + offset, sizeof buff - offset, fmt, args);

	return (buff);
}
