/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:13:09 by dgross            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/08 09:38:43 by jschneid         ###   ########.fr       */
=======
/*   Updated: 2022/12/08 14:57:02 by dgross           ###   ########.fr       */
>>>>>>> 5f3c3a5b01b087a24c24f0b5b87c89c75a95cf13
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> // dup access fork
#include <sys/wait.h> // waitpid
#include <stdio.h>
#include <stdlib.h> // exit

static void	open_pipe(t_koopa *shell)
{
	if (pipe(shell->fd) == -1)
	{
		printf("ERROR\n");
		return ;
	}
}

static void	close_pipe(t_koopa *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	close(shell->fd[0]);
	close(shell->fd[1]);
}

void	write_to(t_koopa *shell, t_data *data)
{
	if (data->next != NULL)
	{
		if (data->next->operator == OUT || data->next->operator == APPEND)
		{
			dup2(shell->out, STDOUT_FILENO);
			close(shell->out);
		}
		else if (data->operator == PIPE)
			dup2(shell->fd[1], STDOUT_FILENO);
	}
	else
		dup2(shell->stdout1, STDOUT_FILENO);
}

static void	pipe_cmd(t_koopa *shell, t_data *data)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_execute_builtin(shell, data) == 1)
			ft_cmd(shell, data);
		exit(0);
	}
}

int	ft_execute(t_koopa *shell, t_data *data)
{
	shell->stdout1 = dup(STDOUT_FILENO);
	ft_redirection(shell, data);
	while (data != NULL)
	{
		if (data->operator == PIPE)
		{
			open_pipe(shell);
			write_to(shell, data);
			pipe_cmd(shell, data);
			close_pipe(shell);
		}
		else if (data->operator == CMD)
		{
			write_to(shell, data);
			if (ft_execute_builtin(shell, data) == 1)
				ft_execute_cmd(shell, data);
		}
		data = data->next;
	}
	while (waitpid(0, &shell->exit_status, 0) > 0)
		;
	close(shell->out);
	return (0);
}
