#include "../../includes/minishell.h"

t_ptoken	*replace_env_var(t_ptoken *token)
{
	char	*doll;
	int		i;

	doll = ft_strchr(token->str, '$');
	i = doll - token->str;
	while (!token->is_in_squotes && doll)
	{
		doll = treat_doll(token, &i);
		doll = ft_strchr(doll + i, '$');
	}
	return (token);
}

void	check_op_omg(t_command **actual, t_ptoken *argv, int *i, t_list **lst)
{
	if ((argv + (*i + 1))->str && is_operator((argv + (*i + 1))->str)
		&& ft_strlen((argv + (*i + 1))->str)
		== (size_t)is_operator((argv + (*i + 1))->str)
		&& !(argv + (*i + 1))->is_escaped && !(argv + (*i + 1))->is_in_quotes
		&& !(argv + (*i + 1))->is_in_squotes)
	{
		(argv + *i)->str = ft_strjoin((argv + *i)->str,
				(argv + (*i + 1))->str);
		check_operator(*actual, argv, *i);
		*i += 1;
	}
	else
		check_operator(*actual, argv, *i);
	ft_lstadd_back(lst, ft_lstnew(*actual));
	*actual = init_command_struct();
}

void	super_check_quotes(t_command **actual, t_ptoken *argv, int *i)
{
	if ((*actual)->qcheck.s || (*actual)->qcheck.d)
	{
		if ((argv + *i)->str[0] == '\'' && !(*actual)->qcheck.d)
			(*actual)->qcheck.s = !(*actual)->qcheck.s;
		else if ((argv + *i)->str[0] == '\"' && !(*actual)->qcheck.s)
			(*actual)->qcheck.d = !(*actual)->qcheck.d;
	}
	if ((*actual)->qcheck.s || (*actual)->qcheck.d)
		(*actual)->token = toktab_add((*actual)->token, *(argv + *i));
	else if ((argv + (*i + 1))->str && (((argv + *i)->str[0] == '\''
				&& (argv + (*i + 1))->str[0] == '\'')
				|| ((argv + *i)->str[0] == '\"'
			&& (argv + (*i + 1))->str[0] == '\"')))
	{
		if ((argv + *i)->str[0] == '\'')
		{
			if (!(*actual)->qcheck.s && !(*actual)->qcheck.d)
			{
				(argv + *i)->str = ft_strdup("");
				(*actual)->token = toktab_add((*actual)->token, *(argv + *i));
			}
		}
		else if ((argv + *i)->str[0] == '\"')
		{
			if (!(*actual)->qcheck.s && !(*actual)->qcheck.d)
			{
				(argv + *i)->str = ft_strdup("");
				(*actual)->token = toktab_add((*actual)->token, *(argv + *i));
			}
		}
	}
	if (!(*actual)->qcheck.s && !(*actual)->qcheck.d)
	{
		if ((argv + *i)->str[0] == '\'' && !(*actual)->qcheck.d)
			(*actual)->qcheck.s = !(*actual)->qcheck.s;
		else if ((argv + *i)->str[0] == '\"' && !(*actual)->qcheck.s)
			(*actual)->qcheck.d = !(*actual)->qcheck.d;
	}
}
