/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:15:09 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:22:03 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

t_redir	*init_redir(t_type type, char *file_name)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (new);
	new->type = type;
	new->file_name = file_name;
	new->next = NULL;
	return (new);
}

static int	env_size(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**duplicate_envp(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*head;

	i = 0;
	envp = NULL;
	if (!env)
		return (NULL);
	head = env->next;
	envp = (char **)malloc((env_size(env) + 2) * sizeof(char *));
	if (!envp)
		return (perror("malloc failed"), NULL);
	while (head)
	{
		envp[i] = ft_strdup(head->str);
		head = head->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

t_cl_info	*init_cl_info(t_env *env, t_parse *parse_list)
{
	t_cl_info	*exec;

	if (!parse_list)
		return (NULL);
	exec = malloc(sizeof(t_cl_info));
	if (!exec)
		return (perror("malloc"), NULL);
	exec->heredoc_file = NULL;
	exec->file_failed = NULL;
	exec->exec_path = NULL;
	exec->path = NULL;
	exec->argv = NULL;
	exec->envp = NULL;
	exec->red_input = 0;
	exec->red_output = 1;
	exec->next = NULL;
	if (parse_list && parse_list->cmd && parse_list->cmd->str)
		exec->argv = get_cmd_args(parse_list);
	exec->envp = duplicate_envp(env);
	exec->red_input = redirection_input(exec, parse_list);
	exec->red_output = redirection_output(parse_list);
	return (exec);
}
