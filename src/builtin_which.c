#include "../includes/minishell.h"

bool	is_a_file(char *path)
{
	struct stat	path_stat;
	int			ret;

	ret = stat(path, &path_stat);
	return (ret == 0 && S_ISREG(path_stat.st_mode));
}

static bool	is_builtin(char *prog)
{
	return (!ft_strcmp(prog, "echo")
		|| !ft_strcmp(prog, "cd")
		|| !ft_strcmp(prog, "pwd")
		|| !ft_strcmp(prog, "export")
		|| !ft_strcmp(prog, "unset")
		|| !ft_strcmp(prog, "env")
		|| !ft_strcmp(prog, "exit")
		|| !ft_strcmp(prog, "which"));
}

char	*which(char *prog)
{
	char	**path;
	char	*prog_path;
	int		i;

	if (is_builtin(prog))
		return ("builtin");
	else if (!ft_isalnum(*prog) && is_a_file(prog))
		return (prog);
	else if (get_env("PATH"))
	{
		path = ft_split(get_env("PATH"), ':');
		i = 0;
		while (path[i])
		{
			prog_path = ft_strjoin(path[i], ft_strjoin("/", prog));
			if (is_a_file(prog_path))
				return (prog_path);
			gc_free(prog_path);
			i++;
		}
	}
	return (NULL);
}

int	builtin_which(char **argv)
{
	char	*prog_path;

	if (!argv[1])
		return (1);
	prog_path = which(argv[1]);
	if (prog_path)
	{
		ft_putstr_fd(STDOUT_FILENO, prog_path);
		ft_putstr_fd(STDOUT_FILENO, "\n");
		return (0);
	}
	else
	{
		ft_putstr_fd(STDERR_FILENO, argv[1]);
		ft_putstr_fd(STDERR_FILENO, " not found\n");
		return (1);
	}
}
