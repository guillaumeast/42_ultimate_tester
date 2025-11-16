#ifndef ULT_PRINT_PRIV_H
#define ULT_PRINT_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "print_pub.h"

//-------------------- COLORS --------------------//

#define COLOR_LEN 5

/* Generate colors getter prototypes */
#define X_COLOR(color_name)	\
    const char *print_color_##color_name(void);
#include "colors.x"
#undef X_COLOR

#define GREY	print_color_grey()
#define RED		print_color_red()
#define GREEN	print_color_green()
#define YELLOW	print_color_yellow()
#define BLUE	print_color_blue()
#define NONE	print_color_none()

//-------------------- EMOJIS --------------------//

/* Generate emojis getter prototypes */
#define X_EMOJI(emoji_name)	\
    const char *print_emoji_##emoji_name(void);
#include "emojis.x"
#undef X_EMOJI

#define EMJ_ARW_DR		print_emoji_arrow_down_right()
#define EMJ_ARW_RIGHT	print_emoji_arrow_right()
#define EMJ_PASS		print_emoji_passed()
#define EMJ_FAIL		print_emoji_failed()
#define EMJ_TIMD		print_emoji_timed()
#define EMJ_CRSH_Y		print_emoji_crashed_y()
#define EMJ_CRSH_N		print_emoji_crashed_n()
#define EMJ_ERR		print_emoji_error()
#define EMJ_TEST		print_emoji_test()
#define EMJ_SUC_START	print_emoji_success_title_start()
#define EMJ_SUC_END	print_emoji_success_title_end()
#define EMJ_FAIL_START	print_emoji_fail_title_start()
#define EMJ_FAIL_END	print_emoji_fail_title_end()

#endif /* __FUT_INSIDE__ */

#endif /* ULT_PRINT_PRIV_H */
