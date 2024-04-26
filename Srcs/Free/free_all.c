/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:36:48 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:24:20 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	free_exec(t_data *data)
{
	// free_p_env(data); // exec
	free_data(data);
	// free_cmd_args(data->arg->argv); //exec
}
void	safe_exit(t_data *data)
{
	rl_clear_history();
	free_env(&data->env);
	free_exec(data);
	// safe_exit_heredoc(&data->here_doc, 0);
}
