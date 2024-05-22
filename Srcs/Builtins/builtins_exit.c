/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:42:22 by nouabdul          #+#    #+#             */
/*   Updated: 2024/05/22 16:03:37 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	ft_llong(unsigned long long res, int neg)
{
	if ((res > LLONG_MAX && neg > 0) || ((long long)(res * neg) < (LLONG_MIN)
		&& neg == -1))
		return (1);
	else
		return (0);
}

static long long	ft_atoi_max(char *str)
{
	int					neg;
	int					i;
	unsigned long long	res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i++] - '0');
		if (ft_llong(res, neg))
		{
			error_numeric(str, "exit");
			return (g_status);
		}
	}
	return ((long long)res * neg);
}

static void	exit_exec(t_data *data, char **cmd)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1] && !is_all_digit(cmd[1]))
		error_numeric(cmd[1], cmd[0]);
	else if (cmd[1] && !cmd[2])
		g_status = ft_atoi_max(cmd[1]);
	free_data(data);
	exit(g_status);
}

int	builtin_exit(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd[1])
		exit_exec(data, cmd);
	else if (cmd[1])
	{
		if (!cmd[2])
			exit_exec(data, cmd);
		else
		{
			ft_putendl_fd("exit", STDIN_FILENO);
			error_many_args(cmd[0]);
		}
	}
	return (g_status);
}
