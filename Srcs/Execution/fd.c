/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:53:13 by romina            #+#    #+#             */
/*   Updated: 2024/05/22 15:34:36 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	ft_close(int *fd)
{
	if (fd && *fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_all(t_data *data, t_cl_info *temp, int i)
{
	t_cl_info	*exec_tmp;

	exec_tmp = data->exec;
	while (exec_tmp)
	{
		ft_close(&exec_tmp->red_input);
		ft_close(&exec_tmp->red_output);
		exec_tmp = exec_tmp->next;
	}
	ft_close(&data->pipes[(i + 1) % 2][0]);
	ft_close(&data->pipes[(i + 1) % 2][1]);
	ft_close(&data->pipes[i % 2][0]);
	ft_close(&data->pipes[i % 2][1]);
	ft_close(&temp->red_input);
	ft_close(&temp->red_output);
}

void	copy_std_files(t_data *data)
{
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	return ;
}

void	red_std_to_io(t_data *data, t_cl_info *exec)
{
	if (exec->red_input > 2)
	{
		if (dup2(exec->red_input, STDIN_FILENO) == -1)
			return (perror("dup2"));
	}
	else
		ft_close(&data->fd[0]);
	if (exec->red_output > 2)
	{
		if (dup2(exec->red_output, STDOUT_FILENO) == -1)
			return (perror("dup2"));
	}
	else
		ft_close(&(data->fd[1]));
	return ;
}

void	back_to_original_io(t_data *data, t_cl_info *exec)
{
	if (exec->red_input > 2)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			return (perror("dup2"));
		ft_close(&exec->red_input);
		ft_close(&data->fd[0]);
	}
	if (exec->red_output > 2)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"));
		ft_close(&exec->red_output);
		ft_close(&data->fd[1]);
	}
	return ;
}
