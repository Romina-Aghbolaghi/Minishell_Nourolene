/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:08:18 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:18:54 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

void	unclosed_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error: unclosed ", 2);
	ft_putendl_fd(str, 2);
	g_status = 2;
}

void	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	g_status = 2;
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
