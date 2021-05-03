#include "../includes/minishell.h"

void	exec_subprocess(char *path, char *argv[])
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		close_shell("error while forking subprocess");
	else if (pid == 0)
	{
		execve(path, argv, get_envp());
		gc_clean();
		exit(errno);
	}
	else
		wait(&status);
	g_shell.last_return = (((status) & 0xff00) >> 8);
}
