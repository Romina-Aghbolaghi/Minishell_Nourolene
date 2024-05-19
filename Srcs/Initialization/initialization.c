/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:35:52 by romina            #+#    #+#             */
/*   Updated: 2024/05/17 17:27:52 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static t_env	*init_env(char **envp)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var_name = NULL;
	new->var_value = NULL;
	new->str = NULL;
	new->next = NULL;
	create_env(new, envp);
	return (new);
}

void	init_data(t_data *data, char **envp)
{
	data->env = init_env(envp);
	data->prompt = NULL;
	data->tokens = NULL;
	data->parse_list = NULL;
	data->exec = NULL;
}

t_token	*init_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = 0;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

t_parse	*init_parse(void)
{
	t_parse	*new;

	new = malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->red_in = NULL;
	new->red_out = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*init_cmd(char *str)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}
