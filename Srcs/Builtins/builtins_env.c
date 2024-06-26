/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:40:51 by nouabdul          #+#    #+#             */
/*   Updated: 2024/05/22 16:01:59 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	print_env(t_env *env)
{
	t_env	*tmp_env;

	if (!env)
		exit(1);
	tmp_env = env->next;
	while (tmp_env)
	{
		if (tmp_env->var_value)
			printf("%s=%s\n", tmp_env->var_name, tmp_env->var_value);
		tmp_env = tmp_env->next;
	}
	return ;
}

int	builtin_env(t_env *env)
{
	if (env)
		print_env(env);
	else
		return (1);
	return (0);
}
