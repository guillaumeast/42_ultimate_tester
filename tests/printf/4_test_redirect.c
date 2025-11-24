#include "ft_ultimate_tester.h"
#include "libftprintf.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// TODO: test multiple redirection handling

Test(Redirect_stdout, 0)
{
	char	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_STDOUT);

	printf("12\n");
	fprintf(stderr, "5\n");
	print_stdout("6\n");
	print_stderr("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	print_stdout("10\n");
	print_stderr("11\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Redirect_stderr, 0)
{
	char	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_STDERR);

	printf("5\n");
	fprintf(stderr, "12\n");
	print_stdout("6\n");
	print_stderr("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	print_stdout("10\n");
	print_stderr("11\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Redirect_both, 0)
{
	char	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_BOTH);

	printf("11\n");
	fprintf(stderr, "12\n");
	print_stdout("5\n");
	print_stderr("6\n");

	output = redirect_read();
	redirect_stop();

	printf("7\n");
	fprintf(stderr, "8\n");
	print_stdout("9\n");
	print_stderr("10\n");
	if (output)
	{
		printf("(1) %s", output);
		fprintf(stderr, "(2) %s", output);
		print_stdout("(3) %s", output);
		print_stderr("(4) %s", output);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	print_stdout("(3) No output\n");
		print_stderr("(4) No output\n");
	}
	if (output)
		free(output);
}

Test(Stacked_redirections, 0)
{
	char	*output1;
	char	*output2;

	output1 = NULL;
	output2 = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	print_stdout("3\n");
	print_stderr("4\n");

	redirect_start(R_BOTH);
	printf("14\n");

	redirect_start(R_STDERR);
	fprintf(stderr, "13\n");

	print_stdout("5\n");
	print_stderr("6\n");

	output1 = redirect_read();
	redirect_stop();

	print_stdout("7\n");
	print_stderr("8\n");

	output2 = redirect_read();
	redirect_stop();

	printf("9\n");
	fprintf(stderr, "10\n");
	print_stdout("11\n");
	print_stderr("12\n");

	if (output1)
		printf("%s", output1);
	else
	 	printf("No output1\n");
	if (output2)
		printf("%s", output2);
	else
	 	printf("No output2\n");
	
	if (output1)
		free(output1);
	if (output2)
		free(output2);
}
