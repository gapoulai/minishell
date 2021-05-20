#include "../includes/minishell.h"

int	quotes_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	while (line[i])
	{
		if (line[i] == '"')
		{
			lexer->had_quotes = true;
			return (len	+ 1);
		}
		i++;
		len++;
	}
	return (-1);
}