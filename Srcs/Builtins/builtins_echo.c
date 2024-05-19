/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:39:28 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 15:59:34 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	is_dash_n(char *str, char n)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != n)
			return (0);
		i++;
	}
	return (1);
}

static int	dash_n(char *cmd)
{
	if (cmd[0] != '-')
		return (0);
	if (is_dash_n(&cmd[1], 'n'))
		return (1);
	return (0);
}

static void	print_echo(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	builtin_echo(char **cmd)
{
	int	n_flag;
	int	i;

	i = 0;
	n_flag = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i++;
	while (cmd[i])
	{
		if (dash_n(cmd[i]))
		{
			n_flag = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(&cmd[i]);
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
