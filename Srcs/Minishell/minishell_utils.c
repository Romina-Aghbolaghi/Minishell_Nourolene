/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:46:35 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:01:20 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/included.h"

void	invalid_arg_msg(int argc, char **argv)
{
	if (argc > 2 || argv[1])
	{
		ft_putendl_fd("You have to execute just ./minishell!", 1);
		exit(EXIT_FAILURE);
	}
}

static void	end_programe(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	exit(g_status);
}
static void	free_all(char *line, t_data *data)
{
	add_history(line);
	free_data(data);
	return ;
}

void	shell_exec(t_env *env, char *line, t_data *data)
{
	if (!line)
	{
		free_env(&env);
		end_programe();
	}
	else if (line[0])
	{
		data->tokens = tokening(env, line);
		if (!data->tokens)
			free_all(line, data);
		else
			data->parse_list = parsing(data->tokens);
		if (!data->parse_list)
			free_all(line, data);
		else
		{
			cl_exec(data);
			add_history(line);
		}
	}
}

