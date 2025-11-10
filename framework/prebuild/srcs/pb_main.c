#include <stdlib.h>
#include <string.h>
#include "pb_types.h"
#include "pb_init.h"
#include "pb_template.h"

static inline bool	process(t_run *run);
static inline void	free_run(t_run *run);

int main(int argc, char **argv)
{
	t_run	run;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: ./%s <target> <template_path> <input_path> <output_path>\n", argv[0]);
		return (1);
	}
	if (!init_run(&run, argv) || !process(&run))
	{
		free_run(&run);
		return (1);
	}
	free_run(&run);
	return (0);
}

static inline bool	process(t_run *run)
{
	FILE		*output;
	size_t		bytes_to_write;
	char		*p;
	char		*next;
	ssize_t		args_len;
	
	output = fopen(run->output_path, "wb");
	if (!output)
	{
		fprintf(stderr, "Error: Unable to open output file %s\n", run->output_path);
		return (false);
	}
	p = run->input.data;
	while ((next = strstr(p, run->target.start.data)))
	{
		bytes_to_write = next - p;
		p += fwrite(p, 1, bytes_to_write, output);
		if ((args_len = build_tmp_template(run, next)) == -1)
			return (false);
		fwrite(run->tmp_template.data, 1, run->tmp_template.len, output);

		p = next + run->target.raw.len - 3 + args_len; // TODO: fix: should jump to real pattern len 'Try("It's way longer!")' not basic pattern len 'Try(...)'!
		free(run->tmp_template.data);
		run->tmp_template.data = NULL;
	}
	fwrite(p, 1, run->input.data + run->input.len - p, output);
	fclose(output);
	return (true);
}

static inline void	free_run(t_run *run)
{
	if (run->target.start.data)
		free(run->target.start.data);
	if (run->input.data)
		free(run->input.data);
	if (run->template.data)
		free(run->template.data);
	if (run->tmp_template.data)
		free(run->tmp_template.data);
}
