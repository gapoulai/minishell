#include "../includes/minishell.h"

void	set_env(char *key, char *value)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key))
		{
			content->value = value;
			return ;
		}
		actual = actual->next;
	}
	content = gc_malloc(sizeof(t_env));
	content->key = key;
	content->value = value;
	ft_lstadd_back(&g_shell.env, ft_lstnew(content));
}

void	unset_env(char *key)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key) && content->value)
		{
			gc_free(content->value);
			content->value = NULL;
			return ;
		}
		actual = actual->next;
	}
}

char	*get_env(char *key)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key) && content->value)
			return (content->value);
		actual = actual->next;
	}
	return (NULL);
}

void	init_env(char **envp)
{
	char	**env;
	char	**spres;

	env = (char **)envp;
	while (*env)
	{
		spres = ft_split(*env, '=');
		set_env(spres[0], *env + (ft_strlen(spres[0]) + 1));
		env++;
	}
	set_env("SHLVL", ft_itoa(ft_atoi(get_env("SHLVL")) + 1));
	set_env("OLDPWD", get_env("PWD"));
	if (!get_env("TERM"))
		set_env("TERM", "dumb");
	if (!get_env("PATH"))
		set_env("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

char	**get_envp(void)
{
	char	**envp;
	t_list	*actual;
	t_env	*content;
	int		pos;

	envp = ft_calloc(sizeof(char *) * (ft_envlstsize(g_shell.env) + 1));
	pos = 0;
	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (content && content->value)
			envp[pos++] = ft_strjoin(content->key,
					ft_strjoin("=", content->value));
		actual = actual->next;
	}
	return (envp);
}
