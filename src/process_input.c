/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:12:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/27 13:54:29 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	preexec(char *cmd)
{
	(void)cmd;
	return ;
}

static void	precmd(void)
{
	return ;
}

void	process_input(char *line)
{
	preexec(line);
	replace_env_line(line);
	if (ft_strlen(line) < 1)
		return ;
	if (!ft_strcmp(line, "exit"))
		close_shell(NULL);
	else if (!ft_strcmp(line, "test"))
		exec_test();
	else if (!ft_strcmp(line, "cd"))
		g_shell.last_return = builtin_cd("/bin");
	else if (!ft_strcmp(line, "pwd"))
		g_shell.last_return = builtin_pwd();
	else if (!ft_strcmp(line, "env"))
		g_shell.last_return = builtin_env();
	else
	{
		ft_putstr_fd(2, "minishell: command not found: ");
		ft_putstr_fd(2, line);
		ft_putstr_fd(2, "\n");
		g_shell.last_return = 127;
	}
	precmd();
}
