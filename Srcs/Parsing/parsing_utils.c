/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:54 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:22:33 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	add_cmd(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (*head == NULL)
		*head = cmd;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

void	create_cmd(t_token *tokens, t_parse *parse_list)
{
	t_cmd	*cmd;

	cmd = init_cmd(tokens->value);
	add_cmd(&parse_list->cmd, cmd);
}

void	*create_pipe(t_parse **parse_list)
{
	t_parse	*node;

	node = init_parse();
	(*parse_list)->next = node;
	if (node)
		(*parse_list) = (*parse_list)->next;
	return (node);
}

static void	add_redir(t_redir **head, t_redir *node)
{
	t_redir	*end;

	if (!*head)
		*head = node;
	else
	{
		end = *head;
		while (end->next)
			end = end->next;
		end->next = node;
	}
}

t_redir	*create_redir(t_token *tokens, t_parse *parse_list)
{
	t_redir	*node;

	node = NULL;
	node = init_redir(tokens->type, tokens->next->value);
	if (tokens->type == REDIR_IN || tokens->type == HEREDOC)
		add_redir(&parse_list->red_in, node);
	else
		add_redir(&parse_list->red_out, node);
	return (node);
}
