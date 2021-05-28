#include "../../includes/minishell.h"

char	**tab_add(char **argv, char *str)
{
	char	**res;
	char	**save;

	res = ft_calloc(sizeof(char *) * (ft_tab_len(argv) + 2));
	save = res;
	if (argv)
		while (*argv)
			*res++ = ft_strdup(*argv++);
	*res = ft_strdup(str);
	return (save);
}

bool	is_operator(char *c)
{
	return (!ft_strcmp(c, ";") || !ft_strcmp(c, ">") || !ft_strcmp(c, ">>")
		|| !ft_strcmp(c, "|") || !ft_strcmp(c, "<"));
}

t_command	*init_command_struct(void)
{
	t_command	*cmd;

	cmd = gc_malloc(sizeof(t_command));
	cmd->operator = NULL;
	cmd->listen_stdout = true;
	cmd->listen_stderr = false;
	cmd->need_pipe = false;
	cmd->need_redirect = false;
	cmd->path = NULL;
	cmd->prog = NULL;
	cmd->redirect_append = false;
	cmd->redirect_path = NULL;
	cmd->argv = NULL;
	cmd->skip_exec = false;
	return (cmd);
}

void	fill_cmd_structs(t_list *lst)
{
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->content;
		cmd->prog = cmd->argv[0];
		cmd->path = which(cmd->prog);
		if (!ft_strcmp(cmd->operator, ";"))
		{
		}
		if (!ft_strcmp(cmd->operator, "|"))
		{
			cmd->need_pipe = true;
		}
		else if (!ft_strcmp(cmd->operator, ">"))
		{
			((t_command *)lst->next)->skip_exec = true;
			cmd->need_redirect = true;
		}
		else if (!ft_strcmp(cmd->operator, ">>"))
		{
			((t_command *)lst->next)->skip_exec = true;
			cmd->need_redirect = true;
			cmd->redirect_append = true;
		}
		else if (!ft_strcmp(cmd->operator, "<"))
		{
			((t_command *)lst->next)->skip_exec = true;
		}
		lst = lst->next;
	}
}

bool	check_struct(t_list	*lst)
{
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->operator && ft_strcmp(cmd->operator, ";") && !lst->next)
			return (false);
		lst = lst->next;
	}
	return (true);
}

t_list	*get_commands(char **argv)
{
	t_list		*lst;
	t_command	*actual;
	int			i;

	lst = NULL;
	i = 0;
	actual = init_command_struct();
	while (argv[i])
	{
		if (is_operator(argv[i]))
		{
			actual->operator = ft_strdup(argv[i]);
			ft_lstadd_back(&lst, ft_lstnew(actual));
			actual = init_command_struct();
		}
		else
			actual->argv = tab_add(actual->argv, argv[i]);
		i++;
	}
	if (actual->argv)
		ft_lstadd_back(&lst, ft_lstnew(actual));
	if (!check_struct(lst))
		return (NULL);
	fill_cmd_structs(lst);
	return (lst);
}
