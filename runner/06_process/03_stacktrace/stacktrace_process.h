#ifndef ULT_STACKTRACE_PROCESS_H
#define ULT_STACKTRACE_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

void	stacktrace_init(int fd_to_parent);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_STACKTRACE_PROCESS_H */
