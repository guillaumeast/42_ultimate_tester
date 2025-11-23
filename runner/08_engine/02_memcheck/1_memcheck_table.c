#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "error_priv.h"
#include "memcheck_int.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__
#include <stdlib.h>
#include <string.h>

#define TABLE_INITIAL_SIZE 1024
#define TABLE_GROWTH_RATIO 2

t_leak	*g_leaks_table = NULL;
size_t	g_leaks_count = 0;

static size_t	s_leaks_table_cap = 0;
static bool		s_memcheck_enabled = false;

void	register_alloc(void *ptr, size_t size, void *caller);
void	register_free(void *ptr);

void	_memcheck_enable(void)
{
	if (s_leaks_table_cap > 0)
		bzero(g_leaks_table, g_leaks_count * sizeof(t_leak));
	else
	{
		s_leaks_table_cap = TABLE_INITIAL_SIZE;
		s_memcheck_enabled = false;
		g_leaks_table = calloc(s_leaks_table_cap, sizeof(t_leak));
	}

	g_leaks_count = 0;
	s_memcheck_enabled = true;
}

void	memcheck_disable(void)
{
	s_memcheck_enabled = false;
}

void	register_alloc(void *ptr, size_t size, void *caller)
{
	if (!s_memcheck_enabled)
		return ;

	if (g_leaks_count == s_leaks_table_cap)
	{
		s_leaks_table_cap *= TABLE_GROWTH_RATIO;
		s_memcheck_enabled = false;
		g_leaks_table = realloc(g_leaks_table, s_leaks_table_cap * sizeof(t_leak));
		s_memcheck_enabled = true;
		exit_if(!g_leaks_table, NOT_ENOUGH_MEMORY);
	}

	g_leaks_table[g_leaks_count].ptr = ptr;
	g_leaks_table[g_leaks_count].size = size;
	g_leaks_table[g_leaks_count].caller = caller;
	g_leaks_count++;
}

void	register_free(void *ptr)
{
	size_t	i;

	if (!s_memcheck_enabled)
		return ;

	i = 0;
	while (i < g_leaks_count && g_leaks_table[i].ptr != ptr)
		i++;

	if (g_leaks_count == 0 || i >= g_leaks_count)
		return ;

	if (g_leaks_count == 1)
	{
		g_leaks_count--;
		g_leaks_table[0].ptr = NULL;
		g_leaks_table[0].size = 0;
		g_leaks_table[0].caller = NULL;
	}
	else
	{
		g_leaks_count--;
		g_leaks_table[i].ptr = g_leaks_table[g_leaks_count].ptr;
		g_leaks_table[i].size = g_leaks_table[g_leaks_count].size;
		g_leaks_table[i].caller = g_leaks_table[g_leaks_count].caller;
	}
}
