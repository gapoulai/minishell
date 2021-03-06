#include "../includes/minishell.h"

t_minishell	g_shell;

static void	init_shell(void)
{
	g_shell.gc = NULL;
	g_shell.workdir = gc_malloc(FILENAME_MAX);
	g_shell.last_return = 0;
	g_shell.env = NULL;
	g_shell.history.lst = NULL;
	ft_lstadd_front(&g_shell.history.lst, ft_lstnew(NULL));
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &g_shell.save);
	g_shell.use_termcaps = false;
	g_shell.child = 0;
	g_shell.outputmngr = 0;
	g_shell.pipes.to_father[0] = -1;
	g_shell.pipes.to_father[1] = -1;
	g_shell.pipes.to_son[0] = -1;
	g_shell.pipes.to_son[1] = -1;
	g_shell.need_pipe = false;
	g_shell.saved_stdout = dup(STDOUT_FILENO);
	g_shell.saved_stderr = dup(STDERR_FILENO);
	g_shell.is_running = false;
}

void	pre_prompt(void)
{
	if (get_env("USER"))
	{
		if (g_shell.last_return != 0)
		{
			ft_putcolor(get_env("USER"), _YELLOW);
			ft_putcolor(" in ", _DARKGRAY);
			ft_putcolor(ft_strreplace(get_pwd(),
					get_env("HOME"), "~"), _YELLOW);
		}
		else
		{
			ft_putcolor(get_env("USER"), _CYAN);
			ft_putcolor(" in ", _DARKGRAY);
			ft_putcolor(ft_strreplace(get_pwd(), get_env("HOME"), "~"), _CYAN);
		}
		ft_putstr("\n");
	}
	if (g_shell.last_return != 0)
	{
		ft_putcolor(ft_itoa(g_shell.last_return), _RED);
		ft_putcolor(" ᐅ", _RED);
	}
	else
		ft_putcolor("ᐅ", _GREEN);
	ft_putstr(" ");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_shell();
	init_env(envp);
	set_input_mode();
	add_signals_listeners();
	if (argc >= 2 && !ft_strcmp(argv[1], "-c"))
		process_input(argv[2]);
	else if (isatty(STDIN_FILENO))
	{
		while (true)
		{
			pre_prompt();
			g_shell.history.act_pos = 0;
			process_input(ft_strtrim_spaces(read_term()));
		}
	}
	else
		process_input(ft_strtrim_spaces(read_term()));
	close_shell(g_shell.last_return);
}
