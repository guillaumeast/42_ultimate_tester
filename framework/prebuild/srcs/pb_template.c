#include <stdlib.h>
#include <string.h>
#include "pb_types.h"
#include "pb_parse.h"
#include "pb_template.h"

static inline size_t	count_substr(const char *str, const char *sub);
static inline void		replace_substr(t_string *input, t_string *rem, t_string *add, t_string *output);

ssize_t	build_tmp_template(t_run *run, const char *str)
{
	t_string	pattern;
	t_string	args;
	size_t		args_count;

	if (!parse_args(&(run->target), str, &args))
	{
		fprintf(stderr, "Error: Unable to parse args: %s\n", str);
		return (-1);
	}
	pattern.data = PATTERN_TO_REPLACE;
	pattern.len = strlen(PATTERN_TO_REPLACE);
	args_count = count_substr(run->template.data, PATTERN_TO_REPLACE);
	run->tmp_template.len = run->template.len \
		- (args_count * strlen(PATTERN_TO_REPLACE)) \
		+ (args_count * args.len);
	run->tmp_template.data = malloc(run->tmp_template.len + 1);
	if (!run->tmp_template.data)
	{
		fprintf(stderr, "Error: Not enough memory\n");
		return (-1);
	}
	replace_substr(&(run->template), &pattern, &args, &(run->tmp_template));
	free(args.data);
	args.data = NULL;
	return (args.len);
}

static inline void replace_substr(t_string *input, t_string *rem, t_string *add, t_string *output)
{
    size_t i = 0, j = 0;
    char *next_rem;

    if (rem->len == 0)
	{
        memcpy(output->data, input->data, input->len);
        j = input->len;
        output->data[j] = '\0';
        return;
    }

    while (i < input->len)
	{
        next_rem = strstr(input->data + i, rem->data);
        if (!next_rem)
		{
            size_t tail = input->len - i;
            memcpy(output->data + j, input->data + i, tail);
            j += tail;
            break;
        }

        size_t before = (size_t)(next_rem - (input->data + i));
        memcpy(output->data + j, input->data + i, before);
        j += before;
        i += before;

        memcpy(output->data + j, add->data, add->len);
        j += add->len;
        i += rem->len;
    }

    output->data[j] = '\0';
}

static inline size_t	count_substr(const char *str, const char *sub)
{
    size_t		count = 0;
    const char *p = str;

    if (!*sub)
        return (0);
    while ((p = strstr(p, sub)))
    {
        count++;
        p += strlen(sub);
    }
    return (count);
}
