/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:11:40 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:21:41 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*saved;

	if (!env && !(*env))
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

void	free_env_unset(t_env *env)
{
	if (!env)
		return ;
	if (env->var_name && env->var_value)
	{
		free(env->var_name);
		env->var_name = NULL;
		free(env->var_value);
		env->var_value = NULL;
		free(env->str);
		env->str = NULL;
	}
	else if (env->var_name && !env->var_value)
	{
		free(env->var_name);
		env->var_name = NULL;
	}
	free(env);
	env = NULL;
}

void	free_darray(char **darray)
{
	int	i;

	i = 0;
	if (!darray)
		return ;
	while (darray[i])
	{
		free(darray[i]);
		darray[i] = NULL;
		i++;
	}
	free(darray);
	darray = NULL;
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	size_t	size;
	size_t	j;
	char	*ret;

	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(((size) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	size = 0;
	while (s1[size])
	{
		ret[size] = s1[size];
		size++;
	}
	while (s2[j])
	{
		ret[size + j] = s2[j];
		j++;
	}
	ret[size + j] = '\0';
	free(s1);
	return (ret);
}
