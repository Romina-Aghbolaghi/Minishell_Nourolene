/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:53:41 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:26:59 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	write_to_heredoc(int fd, char *eof)
{
	char	*user_input;
	int		stdin_tmp;

	sig_handle(SIG_HEREDOC);
	stdin_tmp = dup(STDIN_FILENO);
	user_input = readline(HEREDOC_CMD);
	if (!user_input)
		err_msg_heredoc("warning", eof, 0);
	while (user_input && ft_strcmp(user_input, eof))
	{
		if (g_status == 130)
			break ;
		write(fd, user_input, ft_strlen(user_input));
		write(fd, "\n", 1);
		free(user_input);
		user_input = readline(HEREDOC_CMD);
		if (!user_input)
			err_msg_heredoc("warning", eof, 0);
	}
	dup2(stdin_tmp, STDIN_FILENO);
	close(stdin_tmp);
	free(user_input);
}

int	open_heredoc_file(char *heredoc_file, char *eof)
{
	int	heredoc_fd;

	heredoc_fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (heredoc_fd == -1)
	{
		unlink(heredoc_file);
		ft_putendl_fd("no such file or directory", 2);
		exit(1);
	}
	write_to_heredoc(heredoc_fd, eof);
	close(heredoc_fd);
	return (fd_open_file(heredoc_file));
}
