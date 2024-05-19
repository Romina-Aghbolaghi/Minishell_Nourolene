/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:24:44 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:19:12 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

int	cl_exec(t_data *data)
{
	t_cl_info	*new;
	t_cl_info	*tmp_exec;
	t_parse		*tmp_parse;

	tmp_exec = NULL;
	if (!data || !data->parse_list)
		return (1);
	tmp_parse = data->parse_list;
	while (tmp_parse)
	{
		new = init_cl_info(data->env, tmp_parse);
		if (!data->exec)
			data->exec = new;
		else
		{
			tmp_exec = data->exec;
			while (tmp_exec->next)
				tmp_exec = tmp_exec->next;
			tmp_exec->next = new;
		}
		tmp_parse = tmp_parse->next;
	}
	free_lexer(data);
	return (0);
}

static int	multi_cmds_exec(t_data *data)
{
	int			i;
	pid_t		pid;
	t_cl_info	*tmp;

	i = 0;
	tmp = data->exec;
	while (tmp)
	{
		if (create_pipes(data, tmp, i))
			return (1);
		pid = fork();
		if (pid == -1)
			return (error_msg("fork", strerror(errno), 1));
		if (!pid)
			child_exec(data, tmp, i);
		else
		{
			close_in_parent(data, tmp, i);
			tmp = tmp->next;
			i++;
		}
	}
	return (global_status(pid));
}

static int	multi_cmds(t_data *data)
{
	data->pipes[0][0] = 0;
	data->pipes[0][1] = 1;
	data->pipes[1][0] = 0;
	data->pipes[1][1] = 1;
	return (multi_cmds_exec(data));
}

static int	one_cmd(t_data *data, t_cl_info *temp)
{
	int	status;

	status = 127;
	copy_std_files(data);
	back_red_io_to_original_io(data, temp);
	status = ft_builtin(data->exec, data->env, data);
	back_to_original_io(data, temp);
	return (status);
}

int	execute(t_data *data)
{
	int			status;
	t_cl_info	*temp;

	status = g_status;
	temp = data->exec;
	if (temp)
	{
		signal(SIGINT, sig_ctrlc2);
		if (!temp->argv && !temp->next)
		{
			if (temp->file_failed)
				status = 1;
			else if (g_status != 130)
				status = 0;
		}
		else if (!temp->next && is_built_in(data->exec->argv[0]))
			status = one_cmd(data, temp);
		else
			status = multi_cmds(data);
		ft_close(&temp->red_input);
	}
	return (status);
}
