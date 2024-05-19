/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:42:21 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:27:55 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

void	error_numeric(char *str, char *cmd_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	g_status = 2;
}

void	error_many_args(char *cmd_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
	g_status = 1;
}

void	export_error(char *name)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

int	error_msg(char *cmd, char *detail, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, detail);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}

int	err_msg_heredoc(char *cmd, char *delim, int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg,
			"here-document at line 1 delimited by end-of-file, wanted ");
	msg = join_strs(msg, delim);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (error_nb);
}
