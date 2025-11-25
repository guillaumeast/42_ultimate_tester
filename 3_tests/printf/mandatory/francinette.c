#include "ft_ultimate_tester.h"
#include "libftprintf.h"

#include <stdio.h>
#include <limits.h>

Test(francinette_basics, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, (""));
	compare(RET_OUT, 1, printf, ft_printf, ("\n"));
	compare(RET_OUT, 1, printf, ft_printf, ("\x01\x02\a\v\b\f\r\n"));
	compare(RET_OUT, 1, printf, ft_printf, ("This is a simple test."));
	compare(RET_OUT, 1, printf, ft_printf, ("This is a simple test.\nSecond sentence.\n"));
}

Test(francinette_percent, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%%"));
	compare(RET_OUT, 1, printf, ft_printf, (" %%"));
	compare(RET_OUT, 1, printf, ft_printf, (" %% "));
	compare(RET_OUT, 1, printf, ft_printf, (" %%%% "));
	compare(RET_OUT, 1, printf, ft_printf, (" %% %% %% "));
	compare(RET_OUT, 1, printf, ft_printf, (" %%  %%  %% "));
	compare(RET_OUT, 1, printf, ft_printf, (" %%   %%   %% "));
	compare(RET_OUT, 1, printf, ft_printf, ("%%"));
	compare(RET_OUT, 1, printf, ft_printf, ("%% %%"));
	compare(RET_OUT, 1, printf, ft_printf, ("%%c"));
	compare(RET_OUT, 1, printf, ft_printf, ("aa%%bb"));
	compare(RET_OUT, 1, printf, ft_printf, ("%%%%%%%%%%"));
	compare(RET_OUT, 1, printf, ft_printf, (".%%.%%.%%.%%.%%.%%.%%.%%."));
}

Test(francinette_c, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%c", 'x'));
	compare(RET_OUT, 1, printf, ft_printf, (" %c", 'x'));
	compare(RET_OUT, 1, printf, ft_printf, ("%c ", 'x'));
	compare(RET_OUT, 1, printf, ft_printf, ("%cs%cs%c", 'c', 'b', 'a'));
	compare(RET_OUT, 1, printf, ft_printf, ("%c%c%c", 'a', '\t', 'b'));
	compare(RET_OUT, 1, printf, ft_printf, ("c%cc%cc%cc", 'a', '\t', 'b'));
	compare(RET_OUT, 1, printf, ft_printf, ("%c", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%c", 200));
}

Test(francinette_s, 0)
{
	static char *s_hidden = "null char inside string \0don't print me lol\0";
	static char *s_long = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";

	compare(RET_OUT, 1, printf, ft_printf, ("%s", ""));
	compare(RET_OUT, 1, printf, ft_printf, ("{%s}", ""));
	compare(RET_OUT, 1, printf, ft_printf, (" %s", ""));
	compare(RET_OUT, 1, printf, ft_printf, ("%s ", ""));
	compare(RET_OUT, 1, printf, ft_printf, (" %s ", ""));
	compare(RET_OUT, 1, printf, ft_printf, (" %s ", "-"));
	compare(RET_OUT, 1, printf, ft_printf, (" %s %s ", "", "-"));
	compare(RET_OUT, 1, printf, ft_printf, (" %s %s ", " - ", ""));
	compare(RET_OUT, 1, printf, ft_printf, (" %s %s %s %s %s ", " - ", "", "4", "", "2 "));
	compare(RET_OUT, 1, printf, ft_printf, (" %s %s %s %s %s", " - ", "", "4", "", s_long));
	compare(RET_OUT, 1, printf, ft_printf, ("%s", "some string with %s hehe"));
	compare(RET_OUT, 1, printf, ft_printf, (" %s", "can it handle \t and \n?"));
	compare(RET_OUT, 1, printf, ft_printf, ("%sx", "} { al$#@@@^&$$^#^@@^$*((&"));
	compare(RET_OUT, 1, printf, ft_printf, ("%s", "abc"));
	compare(RET_OUT, 1, printf, ft_printf, ("%s333", "222"));
	compare(RET_OUT, 1, printf, ft_printf, ("111%s", "222"));
	compare(RET_OUT, 1, printf, ft_printf, ("111%s333", "222"));
	compare(RET_OUT, 1, printf, ft_printf, ("111%s333%s555", "222", "444"));
	compare(RET_OUT, 1, printf, ft_printf, ("111%s333%s555%saaa%sccc", "222", "444", "666", "bbb"));
	compare(RET_OUT, 1, printf, ft_printf, ("%s%s%s", "And ", "some", "joined"));
	compare(RET_OUT, 1, printf, ft_printf, ("%ss%ss%ss", "And ", "some other", "joined"));
	compare(RET_OUT, 1, printf, ft_printf, ("%s%s%s%s%s", "1", "2", "3", "4", "5"));
	compare(RET_OUT, 1, printf, ft_printf, ("%s", s_hidden));
	compare(RET_OUT, 1, printf, ft_printf, ("NULL ->%s<- NULL", (char *)NULL));
}

Test(francinette_d, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%d", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", -10));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", -42));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", -200000));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", -6000023));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", 10000));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", 100023));
	compare(RET_OUT, 1, printf, ft_printf, ("dgs%dxx", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("before %d after", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%d%dd%d", 1, 2, -3));
	compare(RET_OUT, 1, printf, ft_printf, ("%d%d%d%d%d", 1, -2, 3, -4, 5));
	compare(RET_OUT, 1, printf, ft_printf, ("d%dd%dd%dd", 1, -2, 3));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", INT_MIN));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", INT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%d", UINT_MAX));
}

Test(francinette_i, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%i", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", -10));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", -42));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", -200000));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", -6000023));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", 10000));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", 100023));
	compare(RET_OUT, 1, printf, ft_printf, ("dgs%ixx", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("before %i after", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%i%id%i", 1, 2, -3));
	compare(RET_OUT, 1, printf, ft_printf, ("%i%i%i%i%i", 1, -2, 3, -4, 5));
	compare(RET_OUT, 1, printf, ft_printf, ("d%id%id%id", 1, -2, 3));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", INT_MIN));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", INT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%i", UINT_MAX));
}

Test(francinette_u, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%u", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", -10));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", -42));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", -200000));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", -6000023));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", 10000));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", 100023));
	compare(RET_OUT, 1, printf, ft_printf, ("dgs%uxx", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("before %u after", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%u%uu%u", 1, 2, -3));
	compare(RET_OUT, 1, printf, ft_printf, ("u%uu%uu%uu", 0, 55555, 100000));
	compare(RET_OUT, 1, printf, ft_printf, ("%u%u%u%u%u", 1, 100, 999, 42, 999988888));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", INT_MIN));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", INT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", UINT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%u", UINT_MAX + 1));
	compare(RET_OUT, 1, printf, ft_printf, (" %u ", (unsigned int)9223372036854775807LL));
}

Test(francinette_x, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", -10));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", -200000));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", -6000023));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 10000));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 100023));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 0xabcdef));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", 0x7fedcba1));
	compare(RET_OUT, 1, printf, ft_printf, ("dgs%xxx", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("before %x after", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%x%xx%x", 1, 2, -3));
	compare(RET_OUT, 1, printf, ft_printf, ("%x%x%x%x%x", 1, 100, 999, 42, 999988888));
	compare(RET_OUT, 1, printf, ft_printf, ("a%xb%xc%xd", 0, 55555, 100000));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", INT_MIN));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", INT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%x", UINT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%x, %x", 0, UINT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, (" %x ", (unsigned int)9223372036854775807LL));
}

Test(francinette_X, 0)
{
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 0));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", -10));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", -200000));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", -6000023));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 10000));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 100023));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 0xabcdef));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", 0x7fedcba1));
	compare(RET_OUT, 1, printf, ft_printf, ("dgs%Xxx", 10));
	compare(RET_OUT, 1, printf, ft_printf, ("before %X after", 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%X%Xx%X", 1, 2, -3));
	compare(RET_OUT, 1, printf, ft_printf, ("%X%X%X%X%X", 1, 100, 999, 42, 999988888));
	compare(RET_OUT, 1, printf, ft_printf, ("a%Xb%Xc%Xd", 0, 55555, 100000));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", INT_MIN));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", INT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%X", UINT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%X, %X", 0, UINT_MAX));
	compare(RET_OUT, 1, printf, ft_printf, (" %X ", (unsigned int)9223372036854775807LL));
}

Test(francinette_p, 0)
{
	int				i;
	unsigned long	l;
	char			*str;

	compare(RET_OUT, 1, printf, ft_printf, ("%p", (void *)-1));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", (void *)1));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", &i));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", &l));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", &str));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", &strlen));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", ""));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", NULL));
	compare(RET_OUT, 1, printf, ft_printf, ("%p", (void *)-14523));
	compare(RET_OUT, 1, printf, ft_printf, ("0x%p-", (void *)ULONG_MAX));
	compare(RET_OUT, 1, printf, ft_printf, (" %p %p ", (void *)-ULONG_MAX, (void *)ULONG_MAX));
	compare(RET_OUT, 1, printf, ft_printf, ("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX));
}

Test(francinette_mix, 0)
{
	int	i;

	compare(RET_OUT, 1, printf, ft_printf, ("%%%c", 'x'));
	compare(RET_OUT, 1, printf, ft_printf, ("s: %s, p: %p, d:%d", "a string", &i, 42));
	compare(RET_OUT, 1, printf, ft_printf, ("%s%p%d%d%p%s%p%p%s", "a", &free, 1, 2, &malloc, "b", &free, &malloc, "c"));
	compare(RET_OUT, 1, printf, ft_printf, ("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0));
}
