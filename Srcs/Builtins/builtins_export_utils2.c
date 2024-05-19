/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:21:59 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 15:59:50 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	swaping(t_env **tmp, t_env **next_tmp, t_env *env)
{
	if ((ft_strcmp((*tmp)->var_name, (*next_tmp)->var_name)) > 0)
	{
		ft_swap(&(*tmp)->var_name, &(*next_tmp)->var_name);
		ft_swap(&(*tmp)->var_value, &(*next_tmp)->var_value);
		*tmp = env;
	}
	else
		*tmp = (*tmp)->next;
}

t_env	*sort_list(t_env *env)
{
	t_env	*tmp;
	t_env	*next_tmp;

	tmp = env;
	while (tmp)
	{
		while (tmp && !tmp->var_name)
			tmp = tmp->next;
		if (tmp)
			next_tmp = tmp->next;
		else
			break ;
		while (next_tmp && next_tmp->var_name == NULL)
			next_tmp = next_tmp->next;
		if (next_tmp)
			swaping(&tmp, &next_tmp, env);
		else
			break ;
	}
	return (env);
}
