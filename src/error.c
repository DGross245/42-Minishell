/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:18:31 by dgross            #+#    #+#             */
/*   Updated: 2022/11/29 10:50:17 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> //perror	

// gucken wie wir ne überall ausführbare error function hinbekommen
int	print_error(char *failed_cmd, char *reason)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(failed_cmd, 2);
	perror(reason);
	return (0);
}
