#ifndef ULT_REDIRECT_INTERNAL_H
#define ULT_REDIRECT_INTERNAL_H

#ifndef __FUT_REDIRECT_INSIDE__
/*
**  Internal header for the redirect module.
**  Not available outside its compilation unit.
*/
#else

#include "redirect_priv.h"
#include "file_priv.h"

void	redirect_init(void);
void	redirect_save(void);
void	redirect_restore(void);
void	redirect_cleanup(void);

#endif /* __FUT_REDIRECT_INSIDE__ */

#endif /* ULT_REDIRECT_INTERNAL_H */
