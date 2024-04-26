/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:22:18 by romina            #+#    #+#             */
/*   Updated: 2024/04/25 19:37:32 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

char	*env_var_name(char *str)
{
	char	*var_name;

	var_name = ft_substr(str, 0, env_var_name_len(str));
	if (var_name == NULL)
		return (NULL);
	return (var_name);
}

int	env_var_name_len(char *var_name)
{
	int	i;

	i = 0;
	if (*var_name == '?' || ft_isdigit(*var_name))
		return (1);
	while (var_name[i] == '_' || ft_isalpha(var_name[i])
		|| ft_isdigit(var_name[i]))
		i++;
	return (i);
}

char	*env_var_value(t_env *env, char *var_name)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env->next;
	while (head)
	{ 
		if (var_name[0] == '?')
			return (ft_itoa(g_status));
		else if (!ft_strcmp(var_name, head->var_name))
		{
			if (!head->var_value)
				return (ft_strdup("\0"));
			return (ft_strdup(head->var_value));
		}
		head = head->next;
	}
	return (ft_strdup("\0"));
}
