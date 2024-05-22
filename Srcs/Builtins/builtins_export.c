/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:55:30 by romina            #+#    #+#             */
/*   Updated: 2024/05/22 14:06:59 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	print_export(t_data *data)
{
	t_env	*tmp;
	t_env	*copy;

	tmp = NULL;
	copy = NULL;
	copy_t_env(data->env, &copy);
	copy = sort_list(copy);
	tmp = copy->next;
	while (tmp)
	{
		if (tmp->var_value && ft_strcmp(tmp->var_name, "_"))
			printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->var_value);
		else if (!tmp->var_value)
			printf("declare -x %s\n", tmp->var_name);
		tmp = tmp->next;
	}
	free_env(&copy);
	return (0);
}

static int	valid_id(char *str)
{
	int	i;

	i = 0;
	if (ft_str_cmp(str, "="))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (0);
		i += 1;
	}
	return (1);
}

static char	*catch_value(const char *str)
{
	char	*value;

	value = ft_strchr(str, '=');
	if (value)
	{
		*value = '\0';
		value++;
	}
	return (value);
}

static int	export_exec(char *cmd, t_env *env)
{
	char	*value;

	value = NULL;
	if (cmd[0] != '=' && ft_str_chr(cmd, '='))
	{
		value = catch_value(cmd);
		if (value)
			add_var_exec(env, cmd, value);
	}
	else if(cmd[0] == '=')
	{
		export_error(cmd);
		return (1);
	}
	else if (!ft_str_chr(cmd, '=') && ft_strcmp("export", cmd))
		add_var_exec(env, cmd, value);
	return (0);
}

int	builtin_export(char **cmd, t_data *data)
{
	int	status;
	int	i;

	i = 1;
	status = 0;
	if (!cmd[1])
		return (print_export(data));
	while (cmd[i])
	{
		if (!valid_id(cmd[i]))
		{
			export_error(cmd[i]);
			return (1);
		}
		status = export_exec(cmd[i], data->env);
		i++;
	}
	return (status);
}
