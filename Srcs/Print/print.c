/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:16:42 by romina            #+#    #+#             */
/*   Updated: 2024/04/25 15:18:06 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	print_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens->next;
	while (curr)
	{
		printf("%s   token_type: %d\n", curr->value, curr->type);
		curr = curr->next;
	}
}

void	print_parse_list(t_parse *parse_list)
{
	t_cmd	*cur_cmd;
	t_redir		*cur_redir;

	while (parse_list != NULL)
	{
		cur_cmd = parse_list->cmd;
		while (cur_cmd != NULL)
		{
			printf("CMD %s\n", cur_cmd->str);
			cur_cmd = cur_cmd->next;
		}
		cur_redir = parse_list->red_in;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		cur_redir = parse_list->red_out;
		while (cur_redir != NULL)
		{
			printf("T: %d, F: %s\n", cur_redir->type, cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		parse_list = parse_list->next;
	}
}