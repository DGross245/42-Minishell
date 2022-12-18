/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:43:44 by dgross            #+#    #+#             */
/*   Updated: 2022/12/18 15:09:54 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> // chdir
#include <stdlib.h> // getenv
#include <limits.h> // [PATH_MAX]
#include "libft.h"
#include <stdio.h>

static void	check_path(t_koopa *shell, char **path, int *check)
{
	if (*path == NULL)
		return ;
	printf("%zu\n", ft_strlen(*path));
	if (ft_strcmp(*path, "-") == 0 || ft_strcmp(*path, "~-") == 0)
	{
		free(*path);
		*path = ft_strdup(ft_getenv(shell, "OLDPWD") + 7);
		*check = 1;
	}
	else if (ft_strcmp(*path, "~") == 0)
	{
		free(*path);
		*path = ft_strdup(getenv("HOME"));
	}
}

static int	update_pwd(t_koopa *shell, int check)
{
	char	buf[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (pwd == NULL)
		return (1);
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", ft_getenv(shell, "PWD") + 4);
		ft_export(shell, oldpwd);
		pwd = ft_strjoin("PWD=", buf);
		ft_export(shell, pwd);
		free(oldpwd);
		free(pwd);
		oldpwd = NULL;
		pwd = NULL;
		if (check == 1)
			ft_pwd();
		return (0);
	}
	return (1);
}

int	ft_cd(t_koopa *shell, char *path)
{
	int	check;

	check = 0;
	check_path(shell, &path, &check);
	if (path == NULL)
	{
		if (chdir(ft_getenv(shell, "HOME") + 5))
		{
			perror("minishell : cd");
			return (1);
		}		
	}
	else
	{	
		if (chdir(path))
		{
			perror("minishell : cd");
			return (1);
		}	
	}
	update_pwd(shell, check);
	return (0);
}
