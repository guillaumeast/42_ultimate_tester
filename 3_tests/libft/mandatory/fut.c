#include "ft_ultimate_tester.h"
#include "libft.h"

#include <limits.h>
#include <stdlib.h>

/* --------------- helper --------------- */

static bool is_valid_pointer(void *ptr)
{
	bool	passed;

	passed = ptr != NULL;
	if (ptr)
		free(ptr);
	
	return passed;
}

// static inline void fill_pattern_1(unsigned char *buf, size_t n)
// {
// 	for (size_t i = 0; i < n; i++)
// 		buf[i] = (unsigned char)('a' + (i % 26));
// }

// static inline void fill_pattern_2(unsigned char *buf, size_t n)
// {
// 	for (size_t i = 0; i < n; i++)
// 		buf[i] = (unsigned char)('A' + (i % 26));
// }

/* --------------- atoi --------------- */

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

/* --------------- bzero --------------- */

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

	test_bzero(4096, 0);
	test_bzero(4096, 1);
	test_bzero(4096, 2048);
	test_bzero(4096, 4096);
}

/* --------------- calloc --------------- */

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
	test_calloc(4096, 1);
	test_calloc(1, 4096);
	test_calloc(1024, 1024);

	/* Zero-size (implementation-defined but must not crash) */
	test_calloc_dont_crash(0, 4096);
	test_calloc_dont_crash(4096, 0);

	/* Overflow (implementation-defined but must not crash) */
	test_calloc_dont_crash(SIZE_MAX, 2);
	test_calloc_dont_crash(2, SIZE_MAX);
}

/* --------------- is* --------------- */

Test(fut_isalnum, 0)
{
	for (int i = - 128; i < 256; i++)
		compare(RET, 1, ft_isalnum, isalnum, (i));

	compare(RET, 1, ft_isalnum, isalnum, (EOF));
}

Test(fut_isalpha, 0)
{
	for (int i = - 128; i < 256; i++)
		compare(RET, 1, ft_isalpha, isalpha, (i));

	compare(RET, 1, ft_isalpha, isalpha, (EOF));
}

Test(fut_isascii, 0)
{
	for (int i = -128; i < 256; i++)
		compare(RET, 1, ft_isascii, isascii, (i));

	compare(RET, 1, ft_isascii, isascii, (EOF));
}

Test(fut_isdigit, 0)
{
	for (int i = -128; i < 256; i++)
		compare(RET, 1, ft_isdigit, isdigit, (i));

	compare(RET, 1, ft_isdigit, isdigit, (EOF));
}

Test(fut_isprint, 0)
{
	for (int i = -128; i < 256; i++)
		compare(RET, 1, ft_isprint, isprint, (i));

	compare(RET, 1, ft_isprint, isprint, (EOF));
}

// /* --------------- atoi --------------- */

// static bool test_ft_itoa(int n, const char *exp)
// {
// 	bool	passed;
// 	char	*res;
	
// 	passed = true;
// 	res = ft_itoa(n);
// 	if (!res)
// 		return false;

// 	passed = strcmp(res, exp) == 0;

// 	free(res);
// 	return passed;
// }

// Test(fut_itoa, 0)
// {
// 	/* Basics */
// 	assert(1, test_ft_itoa(-1, "-1"));
// 	assert(1, test_ft_itoa(-0, "0"));
// 	assert(1, test_ft_itoa(0, "0"));
// 	assert(1, test_ft_itoa(+0, "0"));
// 	assert(1, test_ft_itoa(+1, "1"));
// 	assert(1, test_ft_itoa(42, "42"));

// 	/* Limits */
// 	assert(1, test_ft_itoa(INT_MIN, "-2147483648"));
// 	assert(1, test_ft_itoa(INT_MAX, "2147483647"));
// }

// /* --------------- memchr --------------- */

// Test(fut_memchr, 0)
// {
// 	/* Byte present before n */
// 	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'c', 6));

// 	/* Byte at very end of range */
// 	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'f', 6));

// 	/* Byte outside n → NULL */
// 	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'f', 5));

// 	/* Byte not present */
// 	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'x', 6));

// 	/* Search for NUL byte */
// 	compare(RET, 1, ft_memchr, memchr, ("abc\0def", '\0', 7));

// 	/* n = 0 → always NULL */
// 	compare(RET, 1, ft_memchr, memchr, ("abcdef", 'a', 0));

// 	/* Empty string but n > 0 */
// 	compare(RET, 1, ft_memchr, memchr, ("", 'a', 5));
// }

// /* --------------- memcmp --------------- */

// Test(fut_memcmp, 0)
// {
// 	/* n = 0 -> always equal */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abc", "xyz", 0) > 0) - (ft_memcmp("abc", "xyz", 0) < 0),
// 		(memcmp("abc", "xyz", 0) > 0) - (memcmp("abc", "xyz", 0) < 0)
// 	);

// 	/* Identical memory */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abcdef", "abcdef", 6) > 0) - (ft_memcmp("abcdef", "abcdef", 6) < 0),
// 		(memcmp("abcdef", "abcdef", 6) > 0) - (memcmp("abcdef", "abcdef", 6) < 0)
// 	);

// 	/* Differ at first byte */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abc", "xbc", 3) > 0) - (ft_memcmp("abc", "xbc", 3) < 0),
// 		(memcmp("abc", "xbc", 3) > 0) - (memcmp("abc", "xbc", 3) < 0)
// 	);

// 	/* Differ later (c < z) */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abcd", "abzd", 4) > 0) - (ft_memcmp("abcd", "abzd", 4) < 0),
// 		(memcmp("abcd", "abzd", 4) > 0) - (memcmp("abcd", "abzd", 4) < 0)
// 	);

// 	/* One shorter, but n limits comparison: equal for first 3 */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abc", "abcd", 3) > 0) - (ft_memcmp("abc", "abcd", 3) < 0),
// 		(memcmp("abc", "abcd", 3) > 0) - (memcmp("abc", "abcd", 3) < 0)
// 	);

// 	/* Diff within n */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("abc", "abd", 3) > 0) - (ft_memcmp("abc", "abd", 3) < 0),
// 		(memcmp("abc", "abd", 3) > 0) - (memcmp("abc", "abd", 3) < 0)
// 	);

// 	/* Binary data including NULs: identical */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("ab\0cd", "ab\0cd", 5) > 0) - (ft_memcmp("ab\0cd", "ab\0cd", 5) < 0),
// 		(memcmp("ab\0cd", "ab\0cd", 5) > 0) - (memcmp("ab\0cd", "ab\0cd", 5) < 0)
// 	);

// 	/* Binary data including NULs: diff after NUL */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("ab\0cd", "ab\0cD", 5) > 0) - (ft_memcmp("ab\0cd", "ab\0cD", 5) < 0),
// 		(memcmp("ab\0cd", "ab\0cD", 5) > 0) - (memcmp("ab\0cd", "ab\0cD", 5) < 0)
// 	);

// 	/* Empty strings (n > 0, compare '\0') */
// 	assert_eq(RET, 1,
// 		(ft_memcmp("", "", 1) > 0) - (ft_memcmp("", "", 1) < 0),
// 		(memcmp("", "", 1) > 0) - (memcmp("", "", 1) < 0)
// 	);
// }

// /* --------------- memcpy --------------- */

// Test(fut_memcpy, 0)
// {
// 	unsigned char src[4096];
// 	unsigned char dst1[4096];
// 	unsigned char dst2[4096];

// 	/* Source always fully initialized */
// 	fill_pattern(src, sizeof src);	// TODO: don't fill src with same pattern !

// 	/* --- len = 0 (no-op) --- */
// 	fill_pattern(dst1, sizeof dst1);
// 	fill_pattern(dst2, sizeof dst2);

// 	assert(1, ft_memcpy(dst1, src, 0) == dst1);
// 	assert(1, memcmp(dst1, dst2, sizeof dst1) == 0);

// 	/* --- small copy (5) --- */
// 	fill_pattern(dst1, sizeof dst1);
// 	fill_pattern(dst2, sizeof dst2);
// 	memcpy(dst2, src, 5);

// 	assert(1, ft_memcpy(dst1, src, 5) == dst1);
// 	assert(1, memcmp(dst1, dst2, sizeof dst1) == 0);

// 	/* --- medium copy (16) --- */
// 	fill_pattern(dst1, sizeof dst1);
// 	fill_pattern(dst2, sizeof dst2);
// 	memcpy(dst2, src, 16);

// 	assert(1, ft_memcpy(dst1, src, 16) == dst1);
// 	assert(1, memcmp(dst1, dst2, sizeof dst1) == 0);

// 	/* --- copy 26 bytes --- */
// 	fill_pattern(dst1, sizeof dst1);
// 	fill_pattern(dst2, sizeof dst2);
// 	memcpy(dst2, src, 26);

// 	assert(1, ft_memcpy(dst1, src, 26) == dst1);
// 	assert(1, memcmp(dst1, dst2, sizeof dst1) == 0);

// 	/* --- stress test (full 4096 bytes) --- */
// 	fill_pattern(dst1, sizeof dst1);
// 	fill_pattern(dst2, sizeof dst2);
// 	memcpy(dst2, src, sizeof src);

// 	assert(1, ft_memcpy(dst1, src, sizeof src) == dst1);
// 	assert(1, memcmp(dst1, dst2, sizeof dst1) == 0);
// }

// /* --------------- memmove --------------- */

// Test(fut_memmove, 0)
// {
// 	unsigned char buffer_1[4096];
// 	unsigned char buffer_2[4096];

// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);

// 	/* -------- len = 0 (no-op) -------- */
// 	assert(1,
// 		(
// 			ft_memmove(buffer_1, buffer_1 + 100, 0),
// 			memcpy(buffer_2, buffer_2 + 100, 0),
// 			memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0
// 		)
// 	);

// 	/* -------- non-overlapping -------- */
// 	for (int len = 1; len <= 32; len += 7)
// 	{
// 		/* reset buffers */
// 		fill_pattern(buffer_1, sizeof buffer_1);
// 		fill_pattern(buffer_2, sizeof buffer_2);

// 		ft_memmove(buffer_1 + 100, buffer_1 + 200, len);
// 		memmove(buffer_2 + 100, buffer_2 + 200, len);

// 		assert(1, memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);
// 	}

// 	/* -------- overlap: dst < src -------- */
// 	for (int len = 1; len <= 32; len += 7)
// 	{
// 		/* reset buffers */
// 		fill_pattern(buffer_1, sizeof buffer_1);
// 		fill_pattern(buffer_2, sizeof buffer_2);

// 		ft_memmove(buffer_1, buffer_1 + 5, len);
// 		memmove(buffer_2, buffer_2 + 5, len);

// 		assert(1, memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);
// 	}

// 	/* -------- overlap: dst > src -------- */
// 	for (int len = 1; len <= 32; len += 7)
// 	{
// 		/* reset buffers */
// 		fill_pattern(buffer_1, sizeof buffer_1);
// 		fill_pattern(buffer_2, sizeof buffer_2);

// 		ft_memmove(buffer_1 + 5, buffer_1, len);
// 		memmove(buffer_2 + 5, buffer_2, len);

// 		assert(1, memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);
// 	}

// 	/* -------- large move (full 4096 bytes) -------- */
// 	/* reset buffers */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);

// 	ft_memmove(buffer_1, buffer_1 + 128, sizeof buffer_1 - 128);
// 	memmove(buffer_2, buffer_2 + 128, sizeof buffer_2 - 128);

// 	assert(1, memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);
// }

// /* --------------- memset --------------- */

// Test(fut_memset, 0)
// {
// 	unsigned char	buffer_1[4096];
// 	unsigned char	buffer_2[4096];

// 	/* --- len = 0 (no-op) --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);

// 	assert(1, ft_memset(buffer_1, 'X', 0) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- partial fill (5) --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, 'A', 5);

// 	assert(1, ft_memset(buffer_1, 'A', 5) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- fill 16 bytes with NUL --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, 0, 16);

// 	assert(1, ft_memset(buffer_1, 0, 16) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- fill -1 → 255 --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, -1, 8);

// 	assert(1, ft_memset(buffer_1, -1, 8) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- fill 300 → 44 (mod 256) --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, 300, 7);

// 	assert(1, ft_memset(buffer_1, 300, 7) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- single-byte (only first byte touched) --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, 'Z', 1);

// 	assert(1, ft_memset(buffer_1, 'Z', 1) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);

// 	/* --- large fill (stress test whole buffer) --- */
// 	fill_pattern(buffer_1, sizeof buffer_1);
// 	fill_pattern(buffer_2, sizeof buffer_2);
// 	memset(buffer_2, 'Q', sizeof buffer_2);

// 	assert(1, ft_memset(buffer_1, 'Q', sizeof buffer_1) == buffer_1 && memcmp(buffer_1, buffer_2, sizeof buffer_1) == 0);
// }

