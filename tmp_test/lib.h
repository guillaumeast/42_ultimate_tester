typedef void (*t_test_fn)(void);

typedef struct s_set
{
	const char		*name;
	t_test_fn		func;
}	t_set;

void	set_register(t_set *set);

#define Test(name) 												\
	static void name(void); 									\
	static t_set _set_##name =									\
	{															\
		#name,													\
		name,													\
	};															\
	__attribute__((constructor(101)))							\
	static void _register_##name(void)							\
	{															\
		set_register(&_set_##name);								\
	}															\
	static void name(void)
