/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:10:13 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:23:59 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	open_output_file(t_type type, char *file_name)
{
	int	fd;

	fd = 0;
	if (type == REDIR_OUT)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
	{
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd <= 0)
		return (perror(file_name), 1);
	return (fd);
}

int	redirection_output(t_parse *parse_list)
{
	int		fd_output;
	t_redir	*redirect_output;

	fd_output = 1;
	redirect_output = parse_list->red_out;
	while (redirect_output)
	{
		if (redirect_output->type == REDIR_OUT)
		{
			ft_close(&fd_output);
			fd_output = open_output_file(redirect_output->type,
					redirect_output->file_name);
		}
		else if (redirect_output->type == APPEND)
		{
			ft_close(&fd_output);
			fd_output = open_output_file(redirect_output->type,
					redirect_output->file_name);
		}
		redirect_output = redirect_output->next;
	}
	return (fd_output);
}
