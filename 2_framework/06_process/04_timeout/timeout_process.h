#ifndef ULT_TIMEOUT_PROCESS_H
#define ULT_TIMEOUT_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

void	timeout_init(size_t timeout);
void	timeout_start(void);
void	timeout_cancel(void);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_TIMEOUT_PROCESS_H */
