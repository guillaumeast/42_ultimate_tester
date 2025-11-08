#include "test.h"

void	test_c(void)
{
	printf(" %s⏱%s Testing %s'%%c'%s with %sprintable chars%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%c", 33);
	run_test_long("%c", 'A');
	run_test_long("%c", 'z');
	run_test_long("%c", 126);

	printf(" %s⏱%s Testing %s'%%c'%s with %snon-printable chars%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%c", 0);   // NUL
	run_test_long("%c", 7);   // BEL
	run_test_long("%c", 9);   // TAB
	run_test_long("%c", 10);  // LF
	run_test_long("%c", 13);  // CR
	run_test_long("%c", 31);  // Unit separator
	run_test_long("%c", 127); // DEL

	printf(" %s⏱%s Testing %s'%%c'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%c", -1);
	run_test_long("%c", -42);
	run_test_long("%c", -128); // min for signed char

	printf(" %s⏱%s Testing %s'%%c'%s with %sunsigned overflow%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	// Values beyond 255 are wrapped modulo 256
	run_test_long("%c", 255);
	run_test_long("%c", 256);
	run_test_long("%c", 257);
	run_test_long("%c", 512);
	run_test_long("%c", 1024);

	printf(" %s⏱%s Testing %s'%%c'%s with %sint limits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	// Extremes of the int range (they’ll be truncated to a single byte)
	run_test_long("%c", INT_MAX);
	run_test_long("%c", INT_MIN);

	printf("\n");
}
