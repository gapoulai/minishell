#include "../includes/minishell.h"

char	*treat_doll_slash(char *word, int i, int back)
{
	char	*env_value;
	char	*ret;

	env_value = get_env(ft_strndup(word + i + 1, back));
	back++;
	if (env_value)
	{
		ret = ft_strndup(word, i);
		ret = ft_strjoin(ret, env_value);
		ret = ft_strjoin(ret, word + i + back);
	}
	else
	{
		ret = ft_strndup(word, i);
		ret = ft_strjoin(ret, word + i + back);
	}
	return (ret);
}

char	*replace_dolls(char *word, int i)
{
	char	*ret;
	char	*env_value;
	int		len;

	ret = ft_strndup(word, i);
	len = get_word_len(word, ft_strlen(ret) + 1);
	if (word[i + 1] == '?')
		env_value = ft_itoa(g_shell.last_return);
	else
		env_value = get_env(ft_strndup(word + i + 1, len));
	ret = ft_strjoin(ret, env_value);
	ret = ft_strjoin(ret, word + i + len + 1);
	printf("dollars ret [%s]\n", ret);
	return (ret);
}

int	check_slash(char *word, int i)
{
	int	j;

	j = i;
	while (word[i])
	{
		if (word[i] == '$')
			return (0);
		else if (word[i] == '/')
			return (i - j);
		i++;
	}
	return (0);
}

char	*treat_doll(char *word, int *i, int *trans)
{
	int		slash;

	printf("trans during treatment : %d\n", *trans);
	if (*trans == 1)
	{
		*trans = 0;
		*i += 1;
		return (word);
	}
	if (DEBUG)
		printf("word [%s]\n", word);
	if (word[(*i) + 1] == '/')
		return (word);
	slash = check_slash(word, (*i) + 1);
	if (slash)
		return (treat_doll_slash(word, (*i), slash));
	else
		return (replace_dolls(word, (*i)));
	return (word);
}

char	*treat_quotes(char *word, int *i)
{
	int	first;
	int	lasts;
	int	size;

	first = 0;
	lasts = 0;
	size = ft_strlen(word + *i);
	while (word[*i] == '\"')
	{
		*i += 1;
		first++;
	}
	while (word[--size] == '\"')
		lasts++;
	if (first != lasts)
	{
		printf("yo je usis ici\n");
		ft_putstr_fd(2, "Syntax error\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return (NULL);
	}
	word = ft_substr(word, first, size + 1 - lasts);
	word = parse_tokens(word);
	return (word);
}

char	*parse_tokens(char *word)
{
	int		i;
	int		trans;
	char	*new;

	i = 0;
	trans = 0;
	new = word;
	printf("word before treat [%s]\n", word);
	while (new[i])
	{
		if (new[i] == '\\')
			new = treat_backslash(new, &i, &trans);
		if (new[i] == '$')
			new = treat_doll(new, &i, &trans);
		if (new[i] == '\"')
			treat_quotes(new, &i);
		if ((new[i] && new[i] != '$')
			|| (new[i] && new[i] == '$' && new[i + 1] == '/'))
			i++;
	}
	if (DEBUG)
		printf("retun new : [%s]\n", new);
	return (new);
}
