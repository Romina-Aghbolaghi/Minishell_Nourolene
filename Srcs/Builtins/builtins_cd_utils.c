/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:51:01 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 15:59:23 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

int	home_dir_exec(char *cmd, t_env *env, char *str)
{
	char	*home;
	int		ret;

	home = find_directory(str, env);
	if (!home)
		return (-1);
	ret = change_directory(home, env, cmd);
	return (ret);
}

char	*find_directory(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, str))
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	swap_pwd_old(t_env *env)
{
	char	*tmp;
	t_env	*tmp_env;

	tmp_env = env->next;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->var_name, "PWD"))
		{
			tmp = ft_strdup(tmp_env->var_value);
			free(tmp_env->var_value);
			tmp_env->var_value = getcwd(NULL, 0);
		}
		tmp_env = tmp_env->next;
	}
	tmp_env = env->next;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->var_name, "OLDPWD"))
		{
			free(tmp_env->var_value);
			tmp_env->var_value = ft_strdup(tmp);
		}
		tmp_env = tmp_env->next;
	}
	free(tmp);
}

void	print_pwd(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, str, ft_strlen(str)))
			printf("%s\n", tmp->var_value);
		tmp = tmp->next;
	}
}
