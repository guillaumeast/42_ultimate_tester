#ifndef ULT_COLORS_PRIV_H
#define ULT_COLORS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

/* Generate colors getter prototypes */
#define X_COLOR(color_name)	const char *colors_get_##color_name(void);
#include "colors.x"
#undef X_COLOR

#define GREY	colors_get_grey()
#define RED		colors_get_red()
#define BRED	colors_get_bred()
#define GREEN	colors_get_green()
#define BGREEN	colors_get_bgreen()
#define YELLOW	colors_get_yellow()
#define BLUE	colors_get_blue()
#define BBLUE	colors_get_bblue()
#define CYAN	colors_get_cyan()
#define NONE	colors_get_none()

#endif /* __FUT_INSIDE__ */

#endif /* ULT_COLORS_PRIV_H */
