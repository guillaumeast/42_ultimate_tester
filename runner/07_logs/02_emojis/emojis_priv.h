#ifndef ULT_EMOJIS_PRIV_H
#define ULT_EMOJIS_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

/* Generate emojis getter prototypes */
#define X_EMOJI(emoji_name)	\
    const char *emojis_get_##emoji_name(void);
#include "emojis.x"
#undef X_EMOJI

#define EMJ_ARW_DR		emojis_get_arrow_down_right()
#define EMJ_ARW_RIGHT	emojis_get_arrow_right()
#define EMJ_PASS		emojis_get_passed()
#define EMJ_FAIL		emojis_get_failed()
#define EMJ_TIMD		emojis_get_timed()
#define EMJ_CRSH		emojis_get_crashed()
#define EMJ_LEAK		emojis_get_leaked()
#define EMJ_ERR			emojis_get_error()
#define EMJ_TEST		emojis_get_test()
#define EMJ_SUC_START	emojis_get_success_title_start()
#define EMJ_SUC_END		emojis_get_success_title_end()
#define EMJ_FAIL_START	emojis_get_fail_title_start()
#define EMJ_FAIL_END	emojis_get_fail_title_end()

#endif /* __FUT_INSIDE__ */

#endif /* ULT_EMOJIS_PRIV_H */
