/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:18:49 by romina            #+#    #+#             */
/*   Updated: 2024/04/21 16:19:29 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/included.h"

static void	default_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	ft_putstr_fd(BLUE_COLOR, 1);
	ft_putstr_fd("MINISHELL >>", 1);
	ft_putstr_fd(RESET_BLUE_COLOR, 1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_handle(int state)
{
	if (state == SIG_DEFAULT)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
}



/////////////////////////////////////////////////////////////////////////////////////


// static void	sig_handler(int signum)
// {
//		if (signum == SIGINT)
// 		{
// 			g_status = 130;
	
// 			ft_putstr_fd("^C\n", STDERR_FILENO);
// 			rl_on_new_line();
// 			ft_putstr_fd(BLUE_COLOR, 1);
// 			ft_putstr_fd("MINISHELL >>", 1);
// 			ft_putstr_fd(RESET_BLUE_COLOR, 1);
// 			rl_replace_line("", 1);
// 			rl_redisplay();
// 		}
// }

// void	sig_handle(int state)
// {
// 	struct sigaction	sa;

// 	rl_catch_signals = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = &sig_handler;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGTERM, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 
// }