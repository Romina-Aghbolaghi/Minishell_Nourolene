/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:22:18 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:17:52 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

t_env	*add_env_node(char *str)
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
	new->var_name = ft_substr(str, 0, env_var_len(str));
	if (!index)
		new->var_value = NULL;
	else
		new->var_value = ft_substr(str, index + 1, ft_strlen(str));
	new->next = NULL;
	return (new);
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

char	*find_path(t_env *env)
{
	char	*path;
	t_env	*head;

	path = NULL;
	if (!env)
		return (NULL);
	head = env->next;
	while (head)
	{
		if (ft_strcmp(head->var_name, "PATH") == 0)
		{
			if (head->str)
				path = head->str;
			else
				path = ft_strdup("\0");
		}
		head = head->next;
	}
	return (path);
}

void	copy_t_env(t_env *src, t_env **dest)
{
	t_env	*new_node;
	t_env	*current;

	while (src)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (perror("malloc"));
		new_node->var_name = ft_strdup(src->var_name);
		new_node->var_value = ft_strdup(src->var_value);
		new_node->str = ft_strdup(src->str);
		new_node->next = NULL;
		if (*dest == NULL)
			*dest = new_node;
		else
		{
			current = *dest;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
		src = src->next;
	}
}
