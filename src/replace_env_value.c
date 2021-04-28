#include "../includes/minishell.h"

char	*get_word(char *line, char end, int i)
{
	int		j;
	int		len;
	char	*word;

	j = i;
	while (line[j] != end && line[j])
		j++;
	len = j - i;
	word = ft_calloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len)
		word[j++] = line[i++];
	return (word);
}

size_t	get_word_len(char *line, char end, int i)
{
	int	j;

	j = i;
	while (line[j] && line[j] != end)
		j++;
	return (j - i);
}

char	*set_env_line(char *line, char *env_value, int i)
{
	char *first_part;
	char *final_part;

	first_part = get_word(line, '$', 0);
	final_part = ft_strjoin(first_part, env_value);
	final_part = ft_strjoin(final_part, line + i + get_word_len(line, ' ', i));
	return (final_part);
}

char	*replace_env_line(char *line)
{
	int		i;
	char	*env_value;
	char	*new_line;

	i = 0;
	new_line = line;
	while (new_line[i])
	{
		if (new_line[i] == '$')
		{
			printf("one dollar\n");
			env_value = get_env(get_word(new_line, ' ', i + 1));
			new_line = set_env_line(new_line, env_value, i);
		}
		i++;
	}
	ft_putstr(new_line);
	ft_putstr("\n");
	return (new_line);
}