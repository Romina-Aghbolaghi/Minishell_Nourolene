/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:40:01 by nouabdul          #+#    #+#             */
/*   Updated: 2024/05/22 16:10:27 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	unset_exec(char *variable, t_env *env)
{
	t_env	*tmp;
	t_env	*prev_tmp;

	tmp = env;
	prev_tmp = NULL;
	while (tmp)
	{
		if (ft_str_cmp(variable, tmp->var_name))
		{
			if (prev_tmp)
				prev_tmp->next = tmp->next;
			else
				tmp = tmp->next;
			free_env_unset(tmp);
			return ;
		}
		prev_tmp = tmp;
		tmp = tmp->next;
	}
}

static int	is_valid(char *variable)
{
	if (ft_strchr(variable, '='))
		return (0);
	return (1);
}

int	builtin_unset(char **cmd, t_env *env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!is_valid(cmd[i]))
			return (1);
		unset_exec(cmd[i], env);
		i++;
	}
	return (0);
}
