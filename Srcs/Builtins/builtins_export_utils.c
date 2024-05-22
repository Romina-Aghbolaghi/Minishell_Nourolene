/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:59:13 by romina            #+#    #+#             */
/*   Updated: 2024/05/22 14:05:08 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static t_env	*find_env_var(t_env *env, const char *name)
{
	t_env	*tmp;

	if (!name || !env)
		return (NULL);
	tmp = env->next;
	while (tmp)
	{
		if (tmp->var_name && !ft_strcmp(tmp->var_name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_env	*create_var(const char *name, const char *value)
{
	t_env	*new_var;
	char	*tmp;

	tmp = NULL;
	new_var = (t_env *)malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("export: malloc failed");
		return (NULL);
	}
	new_var->var_name = ft_strdup(name);
	new_var->var_value = ft_strdup(value);
	if (value)
	{
		tmp = ft_strjoin(new_var->var_name, "=");
		new_var->str = ft_strjoin(tmp, new_var->var_value);
		free(tmp);
	}
	else
		new_var->str = ft_strjoin(new_var->var_name, "=");
	new_var->next = NULL;
	return (new_var);
}

static void	add_new_var(t_env *env, t_env *new_var)
{
	t_env	*last;
	t_env	*head;

	if (!env)
		env = new_var;
	else
	{
		head = env;
		while (head->next)
			head = head->next;
		last = head;
		last->next = new_var;
		new_var->next = NULL;
	}
}

void	add_var_exec(t_env *env, char *cmd, char *value)
{
	t_env	*var;
	t_env	*new_var;

	var = find_env_var(env, cmd);
	if (var && ft_strcmp(cmd, "_"))
	{
		free(var->var_value);
		var->var_value = ft_strdup(value);
	}
	else if (!var && cmd[0] != '=' && ft_strcmp(cmd, "_"))
	{
		new_var = create_var(cmd, value);
		add_new_var(env, new_var);
	}
}

int	ft_str_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
