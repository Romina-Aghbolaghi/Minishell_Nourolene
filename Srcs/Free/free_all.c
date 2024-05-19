/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:36:48 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:21:38 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	free_exec_2(t_cl_info *tmp)
{
	t_cl_info	*saved;

	saved = NULL;
	while (tmp)
	{
		saved = tmp->next;
		if (tmp->file_failed)
			free(tmp->file_failed);
		if (tmp->heredoc_file)
		{
			unlink(tmp->heredoc_file);
			free(tmp->heredoc_file);
		}
		ft_close(&tmp->red_input);
		ft_close(&tmp->red_output);
		if (tmp->exec_path)
			free(tmp->exec_path);
		if (tmp->argv)
			free_darray(tmp->argv);
		if (tmp->envp)
			free_darray(tmp->envp);
		free(tmp);
		tmp = saved;
	}
}

void	free_exec(t_cl_info **exec)
{
	t_cl_info	*tmp;

	if (!exec && !(*exec))
		return ;
	tmp = *exec;
	free_exec_2(tmp);
	*exec = NULL;
}

void	free_data(t_data *data)
{
	rl_clear_history();
	if (data)
	{
		if (data->env)
			free_env(&data->env);
		if (data->exec)
			free_exec(&data->exec);
		if (data->prompt)
			free(data->prompt);
		free_lexer(data);
		free(data);
		data = NULL;
	}
}

void	free_all(char *line, t_data *data)
{
	add_history(line);
	free_lexer(data);
	return ;
}

void	safe_exit(t_data *data, long long int i)
{
	if (data)
	{
		if (data->env)
			free_env(&data->env);
		if (data->exec)
			free_exec(&data->exec);
		if (data->prompt)
			free(data->prompt);
		free_lexer(data);
		free(data);
		data = NULL;
	}
	exit(i);
}
