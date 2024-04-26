/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:42:21 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 13:05:34 by romina           ###   ########.fr       */
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

