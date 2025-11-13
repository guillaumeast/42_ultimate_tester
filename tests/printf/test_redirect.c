#include "ft_ultimate_tester.h"
#include "libftprintf.h"
#include <stdlib.h>

Test(Redirect_stdout, 0)
{
	t_string	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	ult_print("3\n");
	ult_print_err("4\n");

	redirect_start(R_STDOUT);

	printf("12\n");
	fprintf(stderr, "5\n");
	ult_print("6\n");
	ult_print_err("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	ult_print("10\n");
	ult_print_err("11\n");
	if (output)
	{
		printf("(1) %s", output->data);
		fprintf(stderr, "(2) %s", output->data);
		ult_print("(3) %s", output->data);
		ult_print_err("(4) %s", output->data);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	ult_print("(3) No output\n");
		ult_print_err("(4) No output\n");
	}
	if (output)
	{
		if (output->data)
			free(output->data);
		free(output);
	}
}

Test(Redirect_stderr, 0)
{
	t_string	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	ult_print("3\n");
	ult_print_err("4\n");

	redirect_start(R_STDERR);

	printf("5\n");
	fprintf(stderr, "12\n");
	ult_print("6\n");
	ult_print_err("7\n");

	output = redirect_read();
	redirect_stop();

	printf("8\n");
	fprintf(stderr, "9\n");
	ult_print("10\n");
	ult_print_err("11\n");
	if (output)
	{
		printf("(1) %s", output->data);
		fprintf(stderr, "(2) %s", output->data);
		ult_print("(3) %s", output->data);
		ult_print_err("(4) %s", output->data);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	ult_print("(3) No output\n");
		ult_print_err("(4) No output\n");
	}
	if (output)
	{
		if (output->data)
			free(output->data);
		free(output);
	}
}

Test(Redirect_both, 0)
{
	t_string	*output;

	output = NULL;

	printf("1\n");
	fprintf(stderr, "2\n");
	ult_print("3\n");
	ult_print_err("4\n");

	redirect_start(R_BOTH);

	printf("11\n");
	fprintf(stderr, "12\n");
	ult_print("5\n");
	ult_print_err("6\n");

	output = redirect_read();
	redirect_stop();

	printf("7\n");
	fprintf(stderr, "8\n");
	ult_print("9\n");
	ult_print_err("10\n");
	if (output)
	{
		printf("(1) %s", output->data);
		fprintf(stderr, "(2) %s", output->data);
		ult_print("(3) %s", output->data);
		ult_print_err("(4) %s", output->data);
	}
	else
	{
	 	printf("(1) No output\n");
	 	fprintf(stderr, "(2) No output\n");
	 	ult_print("(3) No output\n");
		ult_print_err("(4) No output\n");
	}
	if (output)
	{
		if (output->data)
			free(output->data);
		free(output);
	}
}
