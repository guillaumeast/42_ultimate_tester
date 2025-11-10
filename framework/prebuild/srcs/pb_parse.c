#include "pb_types.h"
#include <string.h>
#include <stdlib.h>

static inline size_t	get_args_len(t_target *target, const char *str);

bool	parse_target(t_target *target, char *raw)
{
	char	*found;

	target->raw.data = raw;
	target->raw.len = strlen(raw);
	found = strstr(raw, "(...)");
	if (!found)
	{
		fprintf(stderr, "Error: Unable to find pattern '(...)' in target '%s'\n", target->raw.data);
		return (false);
	}
	target->start.len = found - raw;
	target->start.data = malloc(target->start.len + 1);
	if (!target->start.data)
		return false;
	memcpy(target->start.data, raw, target->start.len);
	target->start.data[target->start.len] = '\0';
	return true;
}

bool	parse_args(t_target *target, const char *str, t_string *output)
{
	size_t	i;
	size_t	j;

	output->len = get_args_len(target, str);
	output->data = NULL;
	output->data = malloc(output->len + 1);
	if (!output->data)
		return false;
	i = strstr(str, target->start.data) - str;
	while (str[i] && str[i] != '(')
		i++;
	i++;
	j = 0;
	while (j < output->len)
	{
		output->data[j] = str[i];
		i++;
		j++;
	}
	output->data[j] = '\0';
	return true;
}

static inline size_t	get_args_len(t_target *target, const char *str)
{
	size_t	i;
	size_t	start;
	size_t	par_count;
	bool	inside_double_quotes = false;
	bool	inside_single_quotes = false;

	i = strstr(str, target->start.data) - str;
	while (str[i] && str[i] != '(')
		i++;
	start = ++i;
	par_count = 1;
	while (str[i])
	{
		if (str[i] == '"' && str[i - 1] != '\\' && ! inside_single_quotes)
			inside_double_quotes = ! inside_double_quotes;
		else if (str[i] == '\'' && str[i - 1] != '\\' && ! inside_double_quotes)
			inside_single_quotes = ! inside_single_quotes;
		else if (str[i] == '(' && ! inside_double_quotes && ! inside_single_quotes)
			par_count++;
		else if (str[i] == ')' && ! inside_double_quotes && ! inside_single_quotes)
			par_count--;
		if (par_count == 0) break;
		i++;
	}
	return (i - start);
}
