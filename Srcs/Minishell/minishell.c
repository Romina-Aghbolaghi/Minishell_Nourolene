/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:12:26 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:23:55 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

int			g_status;

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_data	data;
	t_env	*env;
	// t_arg	arg;//exec part

	invalid_arg_msg(argc, argv);
	g_status = 0;
	sig_handle(SIG_DEFAULT);
	env = init_env(envp);
	init_data(&data, env);
	// init_execve_args(&arg, data.env);// exec part
	// data.arg = &arg;// exec part
	while (1)
	{
		sig_handle(SIG_DEFAULT);
		ft_putstr_fd(BLUE_COLOR, 1);
		ft_putstr_fd("MINISHELL >>", 1);
		ft_putstr_fd(RESET_BLUE_COLOR, 1);
		prompt = readline(" ");
		shell_exec(data.env, prompt, &data);
	}
	safe_exit(&data);
	exit(g_status);
}


