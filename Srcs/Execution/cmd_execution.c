/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:24:44 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:03:23 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/included.h"

void	cl_exec(t_data *data)
{
	t_cmd_line	cmd_info;
    t_parse     *parse_list;
    
    parse_list = data->parse_list;
	init_cmd_line(&cmd_info, parse_list);
	data->cl_info = &cmd_info;
	if (cmd_info.cmds_num == 1)
	{
		if (is_built_in(parse_list->cmd))
			builtin_exec(parse_list, data);
	}
	return ;
}
