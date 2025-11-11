#include "ft_ultimate_tester.h"
#include "libftprintf.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: explore this:
// #define my_macro(fn) typeof(fn)
// #define func_type(fn) typeof(&fn)

Test(WithOUT_redirection, 1)
{
	int a;

	a = 0;
	printf("Oops...\n");
	while(true)
		a++;
	(void)a;
}

Test(With_redirection, 1)
{
	t_string	*output;

	output = NULL;
	printf("Hello, I'm still here\n");
	redirect_start(R_STDOUT);
	printf("===> Hello, I'm INVISIBLE\n");
	output = redirect_read();
	redirect_stop();
	printf("Hello, I'm back!\n");
	if (output)
		printf("Redirected output: |%s|\n", output->data);
	free(output->data);
	free(output);
}
