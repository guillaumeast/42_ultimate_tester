#include <stdlib.h>
#include "pb_types.h"
#include "pb_parse.h"

static inline bool	read_file(const char *path, t_string *output);

bool	init_run(t_run *run, char **argv)
{
	run->input.data = NULL;
	run->target.start.data = NULL;
	run->template.data = NULL;
	run->tmp_template.data = NULL;
	if (!parse_target(&(run->target), argv[1]))
	{
		fprintf(stderr, "Unable to parse target: %s\n", argv[1]);
		return (false);
	}
	if (!read_file(argv[2], &(run->template)))
	{
		fprintf(stderr, "Unable to read file: %s\n", argv[2]);
		return (false);
	}
	if (!read_file(argv[3], &(run->input)))
	{
		fprintf(stderr, "Unable to read file: %s\n", argv[3]);
		return (false);
	}
	run->output_path = argv[4];
	return (true);
}

static inline bool	read_file(const char *path, t_string *output)
{
    FILE	*file;
	size_t	nread;
	
	file= fopen(path, "rb");
    if (!file)
        return false;

    fseek(file, 0, SEEK_END);
    output->len = ftell(file);
    rewind(file);

    output->data = malloc(output->len + 1);
    if (!output->data)
    {
        fclose(file);
        return false;
    }

    nread = fread(output->data, 1, output->len, file);
    output->data[nread] = '\0';
	output->len = nread;
    fclose(file);

    return true;
}
