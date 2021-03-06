#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	else if (!s1 && !s2)
		return (0);
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}
