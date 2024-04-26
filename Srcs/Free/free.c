/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:16:23 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:26:11 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

void	*free_token(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;

	tmp = tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
		    free(tmp->value);
		free(tmp);
		tmp = next;
	}
	return (NULL);
}


void	free_data(t_data *data)
{
	if (data->tokens)
		data->tokens = free_token(data->tokens);
	if (data->parse_list)
		data->parse_list = free_parse(data->parse_list);
}

static void	*free_redir(t_redir *head)
{
	t_redir	*tmp;

	if (!head)
		return (NULL);
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
		tmp = NULL;
	}
	return (NULL);
}

// static void	*free_redir(t_redir *head)
// {
// 	t_redir	*tmp;

// 	if (!head)
// 		return (NULL);
// 	while (head)
// 	{
// 		tmp = head->next;
// 		free(head->file_name);
// 		head->file_name = NULL;
// 		free(head);
// 		head = tmp;
// 	}
// 	return (NULL);
// }

static void	*free_cmd(t_cmd *head)
{
	t_cmd	*tmp;

	if (!head)
		return (NULL);
	while (head)
	{
		tmp = head->next;
		free(head->str);
		head->str = NULL;
		free(head);
		head = tmp;
	}
	return (NULL);
}

void	*free_parse(t_parse *head)
{
	t_parse	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (head)
	{
		tmp = head->next;
		if (head->cmd)
			head->cmd = free_cmd(head->cmd);
		if (head->red_in)
			head->red_in = free_redir(head->red_in);
		if (head->red_out)
			head->red_out = free_redir(head->red_out);
		free(head);
		head = tmp;
	}
	return (NULL);
}


