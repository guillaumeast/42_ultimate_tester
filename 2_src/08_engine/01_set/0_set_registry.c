#include "set_pub.h"
#include <stddef.h>
#include <stdio.h>

static t_set	*g_registry_head = NULL;
static t_set	*g_registry_tail = NULL;
static size_t	g_registry_count = 0;

void	set_register(t_set *set)
{
	fprintf(stderr, "[DEBUG] set_register appelé avec set=%p, name=%s\n", (void*)set, set ? set->name : "NULL");
	if (!set)
		return ;
	set->next = NULL;
	if (!g_registry_head)
	{
		g_registry_head = set;
		g_registry_tail = set;
	}
	else
	{
		g_registry_tail->next = set;
		g_registry_tail = set;
	}
	g_registry_count++;
}

t_set	*set_get_first(void)
{
	return (g_registry_head);
}

size_t	set_get_count(void)
{
	return (g_registry_count);
}
