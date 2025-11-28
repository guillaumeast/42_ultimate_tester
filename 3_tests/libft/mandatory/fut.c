#include "ft_ultimate_tester.h"
#include "libft.h"

#include <limits.h>
#include <stdlib.h>

/* ------- helper ------- */

#define STRESS_TEST_SIZE 4096

static bool is_valid_pointer(void *ptr)
{
	bool	passed;

	passed = ptr != NULL;
	if (ptr)
		free(ptr);
	
	return passed;
}

static inline void fill_pattern_1(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('a' + (i % 26));
}

static inline void fill_pattern_2(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('A' + (i % 26));
}

/* ------- atoi ------- */

Test(fut_atoi, 0)
{
	/* Basics */
	compare(RET, 1, atoi, ft_atoi, ("-1"));
	compare(RET, 1, atoi, ft_atoi, ("-0"));
	compare(RET, 1, atoi, ft_atoi, ("0"));
	compare(RET, 1, atoi, ft_atoi, ("+0"));
	compare(RET, 1, atoi, ft_atoi, ("+1"));
	compare(RET, 1, atoi, ft_atoi, ("42"));
	compare(RET, 1, atoi, ft_atoi, ("+42"));

	/* Spaces */
	compare(RET, 1, atoi, ft_atoi, ("   123"));
	compare(RET, 1, atoi, ft_atoi, ("123   "));
	compare(RET, 1, atoi, ft_atoi, ("   123   "));

	/* Special chars */
	compare(RET, 1, atoi, ft_atoi, ("${(-!@&;:/,?.=%`€456"));
	compare(RET, 1, atoi, ft_atoi, ("\t\n\r\v\f\n\t\n\r\v\f\n456"));
	compare(RET, 1, atoi, ft_atoi, ("\t\n\r\v\f\n\t\n\r\v\f\n ${(-!@&;:/,?.=%`€   789"));

	/* Leading signs and zeros */
	compare(RET, 1, atoi, ft_atoi, ("+0064578"));
	compare(RET, 1, atoi, ft_atoi, ("-0064578"));

	/* Stops at first non-digit */
	compare(RET, 1, atoi, ft_atoi, ("123abc"));

	/* Non digits first */
	compare(RET, 1, atoi, ft_atoi, ("abc123"));

	/* Sign without digit */
	compare(RET, 1, atoi, ft_atoi, ("+"));
	compare(RET, 1, atoi, ft_atoi, ("-"));

	/* Multiple signs */
	compare(RET, 1, atoi, ft_atoi, ("--5"));
	compare(RET, 1, atoi, ft_atoi, ("+-5"));
	compare(RET, 1, atoi, ft_atoi, ("-+5"));

	/* Limits */
	compare(RET, 1, atoi, ft_atoi, ("-2147483648"));
	compare(RET, 1, atoi, ft_atoi, ("2147483647"));
}

/* ------- bzero ------- */

#define test_bzero(buff_size, n)											\
	do {																	\
		unsigned char buffer_1[buff_size];									\
		unsigned char buffer_2[buff_size];									\
																			\
		memset(buffer_1, 'A', buff_size);									\
		memset(buffer_2, 'A', buff_size);									\
																			\
		assert_label(1, "ft_bzero(s, " #n ") with s of size " #buff_size, (	\
			bzero(buffer_1, n),												\
			ft_bzero(buffer_2, n),											\
			memcmp(buffer_1, buffer_2, buff_size) == 0						\
		));																	\
	}	while (0)

Test(fut_bzero, 0)
{
	test_bzero(1, 0);
	test_bzero(1, 1);

	test_bzero(128, 0);
	test_bzero(128, 1);
	test_bzero(128, 64);
	test_bzero(128, 128);

	test_bzero(STRESS_TEST_SIZE, 0);
	test_bzero(STRESS_TEST_SIZE, 1);
	test_bzero(STRESS_TEST_SIZE, 2048);
	test_bzero(STRESS_TEST_SIZE, STRESS_TEST_SIZE);
}

/* ------- calloc ------- */

static bool test_ft_calloc(size_t count, size_t size)
{
	void	*p;
	bool	passed;

	p = ft_calloc(count, size);
	if (!p)
		return (false);

	passed = true;
	for (size_t i = 0; i < count * size; i++)
	{
		if (((unsigned char *)p)[i] != 0)
		{
			passed = false;
			break;
		}
	}
	
	free(p);
	return (passed);
}

#define test_calloc(count, size)										\
	do {																\
		assert_label(1,													\
			"ft_calloc(" #count ", " #size ") returned valid pointer",	\
			is_valid_pointer(ft_calloc(count, size)) == true			\
		);																\
																		\
		assert_label(1,													\
			"ft_calloc(" #count ", " #size ")",							\
			test_ft_calloc(count, size)	== true							\
		);																\
	}	while (0)

static bool test_ft_calloc_dont_crash(size_t count, size_t size)
{
	void	*p;

	p = ft_calloc(count, size);
	if (!p)
		free(p);

	return (true);
}

#define test_calloc_dont_crash(count, size)								\
	do {																\
		assert_label(1,													\
			"ft_calloc(" #count ", " #size ")",							\
			test_ft_calloc_dont_crash(count, size) == true				\
		);																\
	}	while (0)

Test(fut_calloc, 0)
{
	/* Basic allocations */
	test_calloc(1, sizeof(int));
	test_calloc(STRESS_TEST_SIZE, 1);
	test_calloc(1, STRESS_TEST_SIZE);
	test_calloc(1024, 1024);

	/* Zero-size (implementation-defined but must not crash) */
	test_calloc_dont_crash(0, STRESS_TEST_SIZE);
	test_calloc_dont_crash(STRESS_TEST_SIZE, 0);

	/* Overflow (implementation-defined but must not crash) */
	test_calloc_dont_crash(SIZE_MAX, 2);
	test_calloc_dont_crash(2, SIZE_MAX);
}

/* ------- is* ------- */

Test(fut_isalnum, 0)
{
	char	label[64];
	
	for (int i = - 128; i < 128; i++)
	{
		snprintf(label, sizeof label, "ft_isalnum(%d)", i);
		compare_label(RET, 1, label, ft_isalnum, isalnum, (i));
	}

	compare_label(RET, 1, "ft_isalnum(EOF)", ft_isalnum, isalnum, (EOF));
}

Test(fut_isalpha, 0)
{
	char	label[64];
	
	for (int i = - 128; i < 128; i++)
	{
		snprintf(label, sizeof label, "ft_isalpha(%d)", i);
		compare_label(RET, 1, label, ft_isalpha, isalpha, (i));
	}

	compare_label(RET, 1, "ft_isalpha(EOF)", ft_isalpha, isalpha, (EOF));
}

Test(fut_isascii, 0)
{
	char	label[64];
	
	for (int i = - 128; i < 256; i++)
	{
		snprintf(label, sizeof label, "ft_isascii(%d)", i);
		compare_label(RET, 1, label, ft_isascii, isascii, (i));
	}

	compare_label(RET, 1, "ft_isascii(EOF)", ft_isascii, isascii, (EOF));
}

Test(fut_isdigit, 0)
{
	char	label[64];
	
	for (int i = - 128; i < 128; i++)
	{
		snprintf(label, sizeof label, "ft_isdigit(%d)", i);
		compare_label(RET, 1, label, ft_isdigit, isdigit, (i));
	}

	compare_label(RET, 1, "ft_isdigit(EOF)", ft_isdigit, isdigit, (EOF));
}

Test(fut_isprint, 0)
{
	char	label[64];
	
	for (int i = - 128; i < 128; i++)
	{
		snprintf(label, sizeof label, "ft_isprint(%d)", i);
		compare_label(RET, 1, label, ft_isprint, isprint, (i));
	}

	compare_label(RET, 1, "ft_isprint(EOF)", ft_isprint, isprint, (EOF));
}

// /* ------- itoa ------- */

#define test_itoa(nbr)						\
	snprintf(exp, sizeof exp, "%d", nbr);	\
	assert_label(1, "ft_itoa(" #nbr ")", strcmp(ft_itoa(nbr), exp) == 0)

Test(fut_itoa, 0)
{
	char	exp[32];

	/* Basics */
	test_itoa(-1);
	test_itoa(-0);
	test_itoa(0);
	test_itoa(+0);
	test_itoa(+1);
	test_itoa(42);

	/* Limits */
	test_itoa(INT_MIN);
	test_itoa(INT_MAX);
}

/* ------- memchr ------- */

Test(fut_memchr, 0)
{
	/* Byte present before n */
	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'c', 6));

	/* Byte at very end of range */
	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'f', 6));

	/* Byte outside n → NULL */
	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'f', 5));

	/* Byte not present */
	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'x', 6));

	/* Search for NUL byte */
	compare(RET, 1, ft_memchr, memchr, ("abc\0def", '\0', 7));

	/* n = 0 → always NULL */
	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'a', 0));

	/* Empty string but n > 0 */
	compare(RET, 1, ft_memchr, memchr, ("", 'a', 5));
}

/* ------- memcmp ------- */

static char	*format_memcmp_return(int (*fn)(const void *s1, const void *s2, size_t n), const char *s1, const char *s2, size_t n)
{
	if (fn(s1, s2, n) < 0)
		return ("< 0");
	else if (fn(s1, s2, n) > 0)
		return ("> 0");
	return ("0");
}
#define test_memcmp(s1, s2, n)										\
	assert_eq_label(RET, 1, "ft_memcmp(" #s1 ", " #s2 ", " #n ")",	\
		format_memcmp_return(ft_memcmp, s1, s2, n),					\
		format_memcmp_return(memcmp, s1, s2, n)						\
	)

Test(fut_memcmp, 0)
{
	/* n = 0 -> always equal */
	test_memcmp("abc", "123", 0);
	test_memcmp("123", "abc", 0);

	/* Identical memory */
	test_memcmp("abcdef", "abcdef", 6);

	/* Differ at first byte */
	test_memcmp("1bc", "2bc", 3);
	test_memcmp("2bc", "1bc", 3);

	/* Differ later */
	test_memcmp("ab1cd", "ab2cd", 4);
	test_memcmp("ab2cd", "ab1cd", 4);

	/* Differ at last byte */
	test_memcmp("ab1", "ab2", 3);
	test_memcmp("ab2", "ab1", 3);

	/* One shorter */
	test_memcmp("abc", "abc1", 3);
	test_memcmp("abc1", "abc", 3);
	test_memcmp("abc", "abc1", 4);
	test_memcmp("abc1", "abc", 4);

	/* Diff within n */
	test_memcmp("ab1", "ab2", 3);
	test_memcmp("ab2", "ab1", 3);

	/* Including NULs */
	test_memcmp("ab\0cd", "ab\0cd", 4);
	test_memcmp("ab\0c1", "ab\0c2", 4);
	test_memcmp("ab\0c2", "ab\0c1", 4);
	test_memcmp("ab\0cd", "ab\0cd", 5);
	test_memcmp("ab\0c1", "ab\0c2", 5);
	test_memcmp("ab\0c2", "ab\0c1", 5);

	/* Empty strings */
	test_memcmp("", "", 1);
	test_memcmp("a", "", 1);
	test_memcmp("", "a", 1);
	test_memcmp("a", "", 2);
	test_memcmp("", "a", 2);
}

/* ------- memcpy ------- */

static void	test_memcpy(size_t nbytes)
{
	unsigned char	src[STRESS_TEST_SIZE];
	unsigned char	exp[STRESS_TEST_SIZE];
	unsigned char	dst[STRESS_TEST_SIZE];
	char			label[64];

	fill_pattern_1(src, STRESS_TEST_SIZE);
	fill_pattern_2(exp, STRESS_TEST_SIZE);
	memcpy(dst, exp, sizeof dst);

	if (nbytes <= 10)
		snprintf(label, sizeof label, "ft_memcpy(\"%.*s\", \"%.*s\", %zu)", 10, dst, 10, src, nbytes);
	else
		snprintf(label, sizeof label, "ft_memcpy(dst, src, %zu)", nbytes);

	memcpy(exp, src, nbytes);
	assert_eq_label(RET, 1, label, ft_memcpy(dst, src, nbytes), (void *)dst);
	assert_label(1, label, 
		(
			ft_memcpy(dst, src, nbytes),
			memcmp(dst, exp, STRESS_TEST_SIZE) == 0
		)
	);
}

Test(fut_memcpy, 0)
{
	test_memcpy(0);
	test_memcpy(1);
	test_memcpy(5);
	test_memcpy(1024);
	test_memcpy(STRESS_TEST_SIZE);
}

/* ------- memmove ------- */

static void	test_memmove(size_t offset_dst, size_t offset_src, size_t len)
{
	unsigned char	got[STRESS_TEST_SIZE];
	unsigned char	exp[STRESS_TEST_SIZE];
	char			label[64];

	fill_pattern_1(got, STRESS_TEST_SIZE);
	memcpy(exp, got, STRESS_TEST_SIZE);
	snprintf(label, sizeof label, "ft_memmove(buff + %zu, buff + %zu, %zu)", offset_dst, offset_src, len);

	assert_eq_label(RET, 1, label, 
		ft_memmove(got + offset_dst, got + offset_src, len), (void *)(got + offset_dst)
	);

	memmove(exp + offset_dst, exp + offset_src, len);
	assert_label(1, label, 
		(
			ft_memmove(got + offset_dst, got + offset_src, len),
			memcmp(got, exp, STRESS_TEST_SIZE) == 0
		)
	);
}

Test(fut_memmove, 0)
{
	/*  len = 0 (no-op)  */
	test_memmove(100, 200, 0);

	/*  non-overlapping  */
	test_memmove(0, 2048, 1024);

	/*  overlap: dst < src  */
	test_memmove(128, 256, 1024);

	/*  overlap: dst > src  */
	test_memmove(1024, 512, 2048);

	/*  large move (full STRESS_TEST_SIZE bytes)  */
	test_memmove(0, 1, STRESS_TEST_SIZE - 1);
}

/* ------- memset ------- */

static void	test_memset(int c, size_t len)
{
	unsigned char	got[STRESS_TEST_SIZE];
	unsigned char	exp[STRESS_TEST_SIZE];
	char			label[64];

	fill_pattern_2(exp, STRESS_TEST_SIZE);
	memcpy(got, exp, sizeof got);

	if (len <= 10)
		snprintf(label, sizeof label, "ft_memset(\"%.*s\", '%c', %zu)", 10, got, c, len);
	else
		snprintf(label, sizeof label, "ft_memset(buff, '%c', %zu)", c, len);

	memset(exp, c, len);
	assert_eq_label(RET, 1, label, ft_memset(got, c, len), (void *)got);
	assert_label(1, label, 
		(
			ft_memset(got, c, len),
			memcmp(got, exp, STRESS_TEST_SIZE) == 0
		)
	);
}

Test(fut_memset, 0)
{
	/* len = 0 (no-op) */
	test_memset('X', 0);

	/* single-byte (only first byte touched) */
	test_memset('Z', 1);

	/* fill 16 bytes with NUL */
	test_memset(0, 16);

	/* fill -128 → 128 */
	test_memset(-128, 32);

	/* fill -1 → 255 */
	test_memset(-1, 64);

	/* fill 300 → 44 (mod 256) */
	test_memset(300, 128);

	/* large fill (stress test whole buffer) */
	test_memset('!', STRESS_TEST_SIZE);
}

