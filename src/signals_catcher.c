#include "../includes/minishell.h"

void	SIGINT_catcher(int code)
{
	(void)code;
	if (!isatty(STDIN_FILENO))
		close_subprocess(130);
	signal(SIGINT, SIGINT_catcher);
	g_shell.actual_str = ft_calloc(sizeof(char *));
	ft_putstr("^C\n");
	g_shell.last_return = 130;
	g_shell.history.act_pos = 0;
	g_shell.reader.pos = 0;
	g_shell.reader.size = 0;
	if (!g_shell.is_running)
	{
		pre_prompt();
	}
	close_pipe();
	set_input_mode();
}

void	SIGQUIT_catcher(int code)
{
	(void)code;
	if (!isatty(STDIN_FILENO))
		close_subprocess(131);
	signal(SIGQUIT, SIGQUIT_catcher);
}

void	redir_sig_to_child(int code)
{
	if (code == SIGINT)
		g_shell.last_return = 130;
	else if (code == SIGQUIT)
		g_shell.last_return = 131;
	if (g_shell.child)
		kill(g_shell.child, code);
	if (g_shell.outputmngr)
		kill(g_shell.outputmngr, SIGUSR1);
}

void	signals_listeners_to_child(void)
{
	signal(SIGINT, redir_sig_to_child);
	signal(SIGQUIT, redir_sig_to_child);
}

void	add_signals_listeners(void)
{
	signal(SIGINT, SIGINT_catcher);
	signal(SIGQUIT, SIGQUIT_catcher);
}
