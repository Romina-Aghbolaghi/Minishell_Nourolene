/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:35:33 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:23:56 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

int	fd_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

static char	*create_heredoc_file(int i)
{
	char	*file_nb;
	char	*file_name;

	file_nb = NULL;
	file_name = NULL;
	file_nb = ft_itoa(i);
	file_name = ft_strjoin("heredoc_file_", file_nb);
	free(file_nb);
	return (file_name);
}

static int	open_input_file(t_cl_info *exec, t_redir *redir_in, int i,
		int old_fd)
{
	int	fd;

	fd = -1;
	if (redir_in->type == HEREDOC)
	{
		ft_close(&old_fd);
		exec->heredoc_file = create_heredoc_file(i);
		fd = open_heredoc_file(exec->heredoc_file, redir_in->file_name);
		if (redir_in->next)
		{
			unlink(exec->heredoc_file);
			if (exec->heredoc_file)
				free(exec->heredoc_file);
		}
	}
	else if (redir_in->type == REDIR_IN)
	{
		ft_close(&old_fd);
		fd = fd_open_file(redir_in->file_name);
		if (fd == -1 && !exec->file_failed)
			exec->file_failed = ft_strdup(redir_in->file_name);
	}
	return (fd);
}

int	redirection_input(t_cl_info *exec, t_parse *parse_list)
{
	int		fd_input;
	int		i;
	t_redir	*redirect_input;

	fd_input = 0;
	i = 0;
	redirect_input = parse_list->red_in;
	while (redirect_input)
	{
		fd_input = open_input_file(exec, redirect_input, i, fd_input);
		redirect_input = redirect_input->next;
		i++;
	}
	if (exec->file_failed)
		return (error_msg(exec->file_failed, "no such file or directory", -1));
	return (fd_input);
}
