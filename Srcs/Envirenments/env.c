/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:20:40 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:16:18 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

int	env_var_len(char *var_name)
{
	int	i;

	i = 0;
	if (*var_name == '?' || ft_isdigit(*var_name))
		return (1);
	while (var_name[i] == '_' || var_name[i] == '*' || ft_isalpha(var_name[i])
		|| ft_isdigit(var_name[i]))
		i++;
	return (i);
}

static void	manipulate_env(t_env *head, char *str)
{
	t_env	*tmp;
	int		index;

	tmp = head;
	index = (ft_strchr(str, '=') - str) + 1;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_env_node(str);
}

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

char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free(tmp);
	return (str);
}
