/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:18:49 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:28:32 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static void	default_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_ctrlc2(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	sig_ctrlc(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handle(int state)
{
	if (state == SIG_DEFAULT)
	{
		signal(SIGINT, &default_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (state == SIG_HEREDOC)
	{
		signal(SIGINT, sig_ctrlc);
		signal(SIGQUIT, SIG_IGN);
	}
}
