/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:12:26 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 15:58:49 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

int				g_status;

static void	invalid_arg_msg(int argc, char **argv)
{
	if (argc > 2 || argv[1])
	{
		ft_putstr_fd(RED_COLOR, 1);
		ft_putstr_fd("You have to execute just ./minishell!", 1);
		ft_putendl_fd(RESET_RED_COLOR, 1);
		exit(1);
	}
}

static t_parse	*lexer(char *prompt, t_data *data)
{
	if (prompt && *prompt)
	{
		add_history(prompt);
		data->tokens = tokening(data->env, prompt);
		if (!data->tokens)
			free_lexer(data);
		else
			data->parse_list = parsing(data->tokens);
		if (!data->parse_list)
			free_lexer(data);
	}
	return (data->parse_list);
}

static int	shell_exec(char *prompt, t_data *data)
{
	if (lexer(prompt, data))
	{
		if (!cl_exec(data))
			g_status = execute(data);
		free_exec(&data->exec);
	}
	return (g_status);
}

static int	shell_loop(t_data *data)
{
	char	*user_input;

	user_input = NULL;
	while (1)
	{
		sig_handle(SIG_DEFAULT);
		if (data->prompt)
			free(data->prompt);
		data->prompt = prompt_in_color(ft_prompt(data->env));
		user_input = readline(data->prompt);
		if (!user_input)
			break ;
		else if (*user_input)
			g_status = shell_exec(user_input, data);
	}
	return (g_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	g_status = 0;
	invalid_arg_msg(argc, argv);
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_msg("malloc", strerror(errno), errno));
	sig_handle(SIG_DEFAULT);
	init_data(data, envp);
	g_status = shell_loop(data);
	free_data(data);
	return (g_status);
}
