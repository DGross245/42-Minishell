/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:13:09 by dgross            #+#    #+#             */
/*   Updated: 2023/01/02 11:58:57 by dgross           ###   ########.fr       */
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
		printf("Pipe ERROR\n");
		return ;
	}
}

static void	close_pipe(t_koopa *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	close(shell->fd[0]);
	close(shell->fd[1]);
}

void	write_to(t_koopa *shell, t_data *tabel)
{
	if (tabel->next != NULL)
	{
		if (tabel->next->operator == OUT || tabel->next->operator == APPEND)
		{
			if (shell->skip == 1)
				return ;
			dup2(shell->out, STDOUT_FILENO);
			close(shell->out);
		}
		else if (tabel->operator == PIPE)
			dup2(shell->fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(shell->out, STDOUT_FILENO);
		close(shell->out);
	}
}

static	void	close_fd(t_koopa *shell)
{
	close(shell->out);
	close(shell->in);
	dup2(shell->tmp_stdin, STDIN_FILENO);
	close(shell->tmp_stdin);
	dup2(shell->tmp_stdout, STDOUT_FILENO);
	close(shell->tmp_stdout);
}

int	ft_execute(t_koopa *shell, t_data *tabel)
{
	shell->head = tabel;
	shell->skip = 0;
	if (check_for_heredoc(shell, tabel) == ERROR)
		return (ERROR);
	while (tabel != NULL)
	{
		ft_redirection(shell, tabel);
		if (tabel->operator == PIPE)
		{
			open_pipe(shell);
			pipe_cmd(shell, tabel);
			close_pipe(shell);
		}
		else if (tabel->operator == CMD)
		{
			write_to(shell, tabel);
			if (ft_execute_builtin(shell, tabel) == 1)
				ft_execute_cmd(shell, tabel);
		}
		tabel = tabel->next;
	}
	close_fd(shell);
	while (waitpid(0, &shell->exit_status, 0) > 0)
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (shell->skip == 1)
		shell->exit_status = 1;
	return (0);
}
