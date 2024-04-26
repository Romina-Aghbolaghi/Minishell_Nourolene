/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:20:40 by romina            #+#    #+#             */
/*   Updated: 2024/04/24 09:56:43 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	create_env(t_env *head, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		manipulate_env(head, envp[i]);
		i++;
	}
}

static t_env	*copy_env(t_env *env, char *str)
{
	t_env	*start;
	char	*var_name;
	int		var_name_len;

	var_name = env_var_name(str);
	var_name_len = ft_strlen(var_name);
	start = env->next;
	while (start)
	{
		if (!ft_strncmp(start->var_name, var_name, var_name_len + 1))
		{
			free(var_name);
			return (start);
		}
		start = start->next;
	}
	free(var_name);
	return (NULL);
}

static t_env	*add_env_node(char *str)
{
	t_env	*new;
	int		index;

	index = ft_strchr(str, '=') - str;
	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->str = ft_strdup(str);
	new->var_name = ft_substr(str, 0, env_var_name_len(str));
	if (!index)
		new->var_value = NULL;
	else
		new->var_value = ft_substr(str, index + 1, ft_strlen(str));
	new->next = NULL;
	return (new);
}

void	manipulate_env(t_env *head, char *str)
{
	t_env	*tmp;
	t_env	*copy;
	int		index;

	tmp = head;
	copy = copy_env(head, str);
	index = ft_strchr(str, '=') - str + 1;
	if (copy)
	{
		if ((size_t)env_var_name_len(str) == ft_strlen(str))
			return ;
		free(copy->str);
		if (copy->var_value)
			free(copy->var_value);
		copy->str = ft_strdup(str);
		copy->var_value = ft_substr(str, index + 1, ft_strlen(str));
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_env_node(str);
}

