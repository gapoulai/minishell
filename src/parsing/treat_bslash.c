#include "../../includes/minishell.h"

char	*bslash_nquotes(char *word, int i, int r_back)
{
	int		f_quotes;
	int		l_quotes;
	int		size;
	char	*new;

	f_quotes = 0;
	l_quotes = 0;
	while (word[i] == '\"')
	{
		i += 1;
		f_quotes++;
	}
	if (g_shell.had_bslash)
		f_quotes--;
	size = ft_strlen(word + i);
	printf("size LA : %d\n", size);
	while (word[size] == '\"' && size)
	{
		l_quotes++;
		size--;
	}
	printf("before sub : [%s]\n", word);
	new = ft_substr(word, f_quotes + r_back - 1,
			ft_strlen(word + i) + 1 - l_quotes);
	printf("substr part [%s]\n", new);
	// new = parse_tokens(new + i);
	printf("after parse inside slash : [%s]\n", new);
	return (new);
}

char	*bslash_filled(char *word, int *i, int *trans, int back)
{
	char	*new;
	int		r_back;
	int		tmp;

	r_back = back / 2;
	if (g_shell.is_in_quotes == false)
		r_back++;
	new = ft_calloc_char(r_back, '\\');
	new = ft_strjoin(new, word + back + *i);
	printf("NEW [%s]\nWORD [%s]\n", new, word);
	tmp = r_back - 1;
	if (back % 4 == 1 || back % 4 == 3)
		*trans = 1;
	else
		*trans = 0;
	// if (*i >= (int)ft_strlen(new))
	// 	*i = tmp + r_back;
	printf("i [%d]\n", tmp);
	printf("new i [%c]\n", new[tmp]);
	if (new[tmp] == '\"')
	{
		g_shell.had_bslash = true;
		new = bslash_nquotes(new, tmp, r_back);
		*trans = 0;
		// if (*i >= (int)ft_strlen(new))
			// *i = (int)ft_strlen(new);
		// printf("i after modif %d\n", *i);
	}
	*i += tmp;
	printf("i value before :%d\nstrlen :%zu\n", *i, ft_strlen(new));
	g_shell.is_in_quotes = false;
	return (new);
}

// *i += r_back;
// 	if (back % 4 == 1 || back % 4 == 3)
// 		*trans = 1;
// 	else
// 		*trans = 0;
// 	if (*i == (int)ft_strlen(word))
// 		*i = tmp;
// 	if (word[*i] == '\"')
// 	{
// 		new = bslash_nquotes(word, i, r_back);
// 		new = parse_tokens(new);
// 	}
// 	g_shell.is_in_quotes = false;
// 	return (new);

char	*error_bslash(int *i)
{
	*i = 0;
	ft_putstr_fd(2, "Syntax error\n");
	ft_lstclear(&g_shell.tokens);
	g_shell.last_return = 1;
	g_shell.error = true;
	return ("");
}
