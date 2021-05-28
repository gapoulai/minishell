#include "../../includes/minishell.h"

int	exec(t_command cmd)
{
	execve(cmd.path, cmd.argv, get_envp());
	return (errno);
}

int	commant_not_found(char *cmd)
{
	ft_putstr_fd(2, "minishell: command not found: ");
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, "\n");
	return (127);
}

static void	subprocess(t_command cmd, int *status)
{
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
	{
		signal(SIGQUIT, close_subprocess);
		signal(SIGINT, close_subprocess);
		exec(cmd);
	}
	else
	{
		signals_listeners_to_child();
		wait(status);
		*status = (((*status) & 0xff00) >> 8);
	}
}

int	run_command(char **argv)
{
	t_command	cmd;
	int			status;

	cmd = init_cmd_struct(argv);
	status = 0;
	reset_input_mode();
	wait_outputmanager(cmd);
	if (!ft_strcmp(cmd.path, "builtin"))
		status = exec_builtin(cmd.prog, argv);
	else
	{
		if (!cmd.path)
			status = commant_not_found(cmd.prog);
		else
			subprocess(cmd, &status);
	}
	reset_pipe_output();
	if (cmd.need_pipe || cmd.need_redirect)
		close_pipe();
	g_shell.child = 0;
	add_signals_listeners();
	set_input_mode();
	return (status);
}
