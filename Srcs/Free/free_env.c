/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:11:40 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:25:16 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*saved;

	if (!env  && !(*env))
		return ;
	tmp = *env;
	saved = NULL;
	while (tmp)
	{
		saved = tmp->next;
		free(tmp->var_name);
		tmp->var_name = NULL;
		free(tmp->var_value);
		tmp->var_value = NULL;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = saved;
	}
	*env = NULL;
}
