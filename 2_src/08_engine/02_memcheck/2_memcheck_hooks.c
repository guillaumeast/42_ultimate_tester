#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "memcheck_int.h"
#include "error_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <dlfcn.h>

static void	*(*real_malloc)(size_t) = NULL;
static void	*(*real_calloc)(size_t count, size_t) = NULL;
static void	*(*real_realloc)(void *ptr, size_t) = NULL;
static void	(*real_free)(void *) = NULL;

static inline void	init_hooks(void)
{
	if (!real_malloc)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		real_calloc = dlsym(RTLD_NEXT, "calloc");
		real_realloc = dlsym(RTLD_NEXT, "realloc");
		real_free = dlsym(RTLD_NEXT, "free");
	}

	exit_if( \
		!real_malloc || !real_calloc || !real_realloc || !real_free,\
		UNABLE_TO_FETCH_REAL_ALLOCATORS \
	);
}

void	*malloc(size_t size)
{
	void	*ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
		return (NULL);

	ptr = real_malloc(size);
	caller = __builtin_return_address(0);
	register_alloc(ptr, size, caller);

	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
		return (NULL);

	ptr = real_calloc(count, size);
	caller = __builtin_return_address(0);
	register_alloc(ptr, size, caller);

	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	void	*caller;

	init_hooks();

	if (g_mem_mode == SAFETY)
	{
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}

	if (size == 0)
		register_free(ptr);
	
	new_ptr = real_realloc(ptr, size);

	if (size > 0 && new_ptr)
	{
		register_free(ptr);
		caller = __builtin_return_address(0);
		register_alloc(new_ptr, size, caller);
	}
	return (new_ptr);
}

void	free(void *ptr)
{
	init_hooks();
	register_free(ptr);
	real_free(ptr);
}
