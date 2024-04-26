/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:17:54 by romina            #+#    #+#             */
/*   Updated: 2024/04/24 17:54:30 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

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
	/*PRINT THE RESUALT*/
	// printf("cmd: [ %s ]\n", cmd->str);
	
}


void	*create_pipe(t_token **token, t_parse **parse_list)
{
	t_parse	*node;

	if ((((*token)->type) == PIPE)
		&& (!(*token)->next
		|| ((*token)->next && ((*token)->next->type) == PIPE)))
		return (syntax_error((*token)->value));
	else if ((((*token)->type) == PIPE) && (((*token)->next->type) == PIPE)
		&& !(*token)->next->next)
		return (syntax_error("||"));
	else
	{
		node = init_parse();
		(*parse_list)->next = node;
	}
	if (node)
		(*parse_list) = (*parse_list)->next;

	// /*PRINT THE RESUALT*/
 	// ft_putstr_fd(PURPLE_COLOR, 1);
 	// printf("pipe-type: [ %u ]\n\n", (*token)->type);
 	// ft_putstr_fd(RESET_PURPLE_COLOR, 1);
	
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

	if (!tokens->next || tokens->next->type != WORD)
		return (syntax_error("newline"));
	node = init_redir(tokens->type, tokens->next->value);
	if (tokens->type == REDIR_IN || tokens->type == HEREDOC)
		add_redir(&parse_list->red_in, node);
	else
		add_redir(&parse_list->red_out, node);
	// /*PRINT THE RESUALT*/
	// ft_putstr_fd(PURPLE_COLOR, 1);
	// printf("redir-type: [ %d ]\n", node->type);
	// printf("redir-filename: [ %s ]\n\n", node->file_name);
	// ft_putstr_fd(RESET_PURPLE_COLOR, 1);
	
	return (node);
}
