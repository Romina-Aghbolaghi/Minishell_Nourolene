/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:57:10 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:20:44 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

int	create_pipes(t_data *data, t_cl_info *exec, int i)
{
	if (exec->next)
	{
		if (pipe(data->pipes[i % 2]) == -1)
			return (error_msg("pipe", strerror(errno), errno));
	}
	return (0);
}

static void	ft_redir_pipe(t_data *data, t_cl_info *exec, int i)
{
	if (i == 0)
	{
		if (dup2(data->pipes[0][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else if (i)
	{
		if (dup2(data->pipes[(i + 1) % 2][0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	if (exec->next)
	{
		if (dup2(data->pipes[i % 2][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
}

static void	ft_redir_files(t_data *data, t_cl_info *exec)
{
	if (exec->file_failed)
		safe_exit(data, 1);
	if (exec->red_input > 2)
	{
		if (dup2(exec->red_input, STDIN_FILENO) == -1)
			perror("dup2");
	}
	if (exec->red_output > 2)
	{
		if (dup2(exec->red_output, STDOUT_FILENO) == -1)
			perror("dup2");
	}
}

void	child_exec(t_data *data, t_cl_info *exec, int i)
{
	ft_redir_pipe(data, exec, i);
	if (!exec->argv)
	{
		if (exec->file_failed)
			safe_exit(data, 1);
		safe_exit(data, 0);
	}
	ft_redir_files(data, exec);
	close_all(data, exec, i);
	if (is_built_in(exec->argv[0]))
	{
		ft_builtin(exec, data->env, data);
		safe_exit(data, 0);
	}
	else
		other_cmds_exec(data, exec);
}

void	close_in_parent(t_data *data, t_cl_info *exec, int i)
{
	if (!exec->next)
	{
		ft_close(&data->pipes[(i + 1) % 2][0]);
		ft_close(&data->pipes[(i + 1) % 2][1]);
		ft_close(&data->pipes[i % 2][0]);
		ft_close(&data->pipes[i % 2][1]);
	}
	if (i)
	{
		ft_close(&data->pipes[(i + 1) % 2][0]);
		ft_close(&data->pipes[(i + 1) % 2][1]);
	}
	ft_close(&exec->red_input);
	ft_close(&exec->red_output);
	return ;
}
