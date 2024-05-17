/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:14:57 by dgross            #+#    #+#             */
/*   Updated: 2024/05/17 23:25:39 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> 

void	open_pipe(t_koopa *shell)
{
	if (pipe(shell->fd) == -1)
	{
		print_error("Pipe", NULL, "Not enough space/cannot \
		allocate memory");
		return ;
	}
}

void	close_pipe(t_koopa *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	close(shell->fd[1]);
	close(shell->fd[0]);
}

void	close_fd(t_koopa *shell)
{
	close(shell->out);
	shell->out = -1;
	dup2(shell->tmp_stdin, STDIN_FILENO);
	close(shell->tmp_stdin);
	dup2(shell->tmp_stdout, STDOUT_FILENO);
	close(shell->tmp_stdout);
}
