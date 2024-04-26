/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:42:21 by romina            #+#    #+#             */
/*   Updated: 2024/04/25 17:26:40 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	parantes_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	g_status = 1;
}

void	unclosed_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error: unclosed ", 2);
	ft_putendl_fd(str, 2);
	g_status = 1;
}

void	*syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	g_status = 2;
	return (NULL);
}
void	*chdir_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_status = 2;
	return (NULL);
}

void	not_valid_error(char *name)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}

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