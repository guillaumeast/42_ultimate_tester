#include "test.h"

void expect_init(void)
{
    g_passed = g_failed = g_total = 0;
}

t_bool expect_eq_int(int got, int expected, const char *input_format, const char *input_value)
{
    if (got == expected)
        return (TRUE);
    else
    {
        fprintf(stderr, "  Different %sreturn value%s\n", YELLOW, NONE);
        fprintf(stderr, "  ├── %sft_printf(\"%s\", %s) = %d%s\n", RED, input_format, input_value, got, NONE);
        fprintf(stderr, "  └───── %sprintf(\"%s\", %s) = %d%s\n\n", RED, input_format, input_value, expected, NONE);
        return (FALSE);
    }
}

t_bool expect_str_eq(const char *got, const char *expected, const char *input_format, const char *input_value)
{
    if (strcmp(got, expected) == 0)
        return (TRUE);
    else
    {
        fprintf(stderr, "  Different %soutput%s\n", YELLOW, NONE);
        fprintf(stderr, "  ├── %sft_printf(\"%s\", %s) => \"%s\"%s\n", RED, input_format, input_value, got, NONE);
        fprintf(stderr, "  └───── %sprintf(\"%s\", %s) => \"%s\"%s\n\n", RED, input_format, input_value, expected, NONE);
        return (FALSE);
    }
}

void print_results(void)
{
    if (g_failed == 0)
        printf("%s===> ✅ %d / %d tests PASSED%s\n", GREEN, g_passed, g_total, NONE);
    else
        printf("%s===> ❌ %d / %d tests FAILED%s\n", RED, g_failed, g_total, NONE);
}
