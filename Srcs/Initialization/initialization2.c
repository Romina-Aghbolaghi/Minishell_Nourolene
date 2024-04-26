/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:15:09 by romina            #+#    #+#             */
/*   Updated: 2024/04/25 18:29:07 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

t_redir	*init_redir(t_type type, char *file_name)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (new);
	new->type = type;
	new->file_name = file_name;
	new->next = NULL;
	return (new);
}
static int	cmds_number(t_parse *parse_list)
{
	t_parse	*tmp;
	int		len;

	len = 0;
	tmp = parse_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	// printf("cmd_num  %d\n", len);
	return (len);
}

void	init_cmd_line(t_cmd_line *cmd_info, t_parse *parse_list)
{
	cmd_info->fd[0] = -1;
	cmd_info->fd[1] = -1;
    cmd_info-> red_input= 0;
	cmd_info->red_output = 1;
    cmd_info->cmd_index = -1;
	cmd_info->cmds_num = cmds_number(parse_list);
    cmd_info->exec_path = NULL;
    cmd_info->path = NULL;
}

// t_here_doc	*init_heredoc(void):
// {
//     t_here_doc  *here_doc;
    
//     here_doc = malloc(sizeof(t_here_doc));
// 	if (!here_doc)
// 	{
// 		perror("Malloc failure in open heredoc");
// 		return (NULL);
// 	}
// 	here_doc->read_fd = STDIN_FILENO;
// 	here_doc->next = NULL;
//     return (here_doc);
// }