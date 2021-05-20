#include "../includes/minishell.h"

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = '$'
//	token 3 = '\'
//	token 4 = '"'
*/

static int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '$')
		return (set_dollar_type(token, line, start));
	else if (token->str[0] == '\\')
		token->type = 3;
	else if (token->str[0] == '"')
		token->type = 4;
	else if (token->str[0] == '/')
		token->type = 5;
	else
		token->type = 0;
	return (0);
}

void	handle_single_token(char *line, t_token *token, t_lexer *lexer)
{
	if (line[lexer->i - 1])
	{
		token->id = lexer->id++;
		if (get_token_info(token, line, lexer->j, lexer->i) != 2)
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	}
}

int	get_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 0;
	i = lexer->i;
	if (line[i] == '"')
		return (quotes_token_len(line, lexer));
	else
	{
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == '"')
				return (len);
			i++;
			len++;
		}
		return (len);
	}
}

void	handle_space(char *line, t_token *token, t_lexer *lexer)
{
	int	token_l;

	if (lexer->had_quotes)
		lexer->had_quotes = false;
	while (line[lexer->i] == ' ')
		lexer->i++;
	token_l = get_token_len(line, lexer);
	if (token_l == -1)
	{
		ft_putstr_fd(2, "Syntax error\n");
		ft_lstclear(&g_shell.tokens);
		lexer->i = ft_strlen(line);
		g_shell.last_return = 1;
		return ;
	}
	token->id = lexer->id++;
	get_token_info(token, line, lexer->i, lexer->i + token_l);
	ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	lexer->i += token_l;
	if (lexer->i > (int)ft_strlen(line))
		lexer->i = ft_strlen(line);
	printf("actual rest [%s]\n", line + lexer->i);
}

void	get_lexer(char *line)
{
	t_lexer	lexer;
	t_token	*token;

	init_lexer(&lexer);
	while (lexer.i < (int)ft_strlen(line))
	{
		token = gc_malloc(sizeof(t_token));
		if (line[lexer.i] == ' ' || line[lexer.i] == '"'
			|| lexer.i == 0 || lexer.had_quotes)
			handle_space(line, token, &lexer);
		if (line[lexer.i] != '"' && line[lexer.i] != ' ' && !lexer.had_quotes)
			lexer.i++;
	}
	if (DEBUG)
		display_tokens();
}
