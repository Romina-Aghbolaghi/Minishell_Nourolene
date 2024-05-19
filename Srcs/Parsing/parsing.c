/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:50:49 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:22:36 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	if_redir(t_type type)
{
	if (type == REDIR_IN || type == HEREDOC || type == REDIR_OUT
		|| type == APPEND)
		return (1);
	return (0);
}

static int	invalid_operator(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == PIPE)
		return (syntax_error(tmp->value), 1);
	while (tmp)
	{
		if (if_redir(tmp->type))
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (syntax_error(tmp->value), 1);
		}
		if (ft_str_chr(tmp->value, '&') || ft_str_chr(tmp->value, ';')
			|| (!ft_strcmp(tmp->value, "|") && !tmp->next)
			|| (!ft_strcmp(tmp->value, "|") && tmp->next
				&& !ft_strcmp(tmp->next->value, "|")))
		{
			if (tmp->type != WORD)
				return (syntax_error(tmp->value), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	create_parse_list(t_parse *parse_list, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens->next;
	while (tmp)
	{
		if (tmp->type == WORD)
			create_cmd(tmp, parse_list);
		else if (tmp->type == PIPE)
		{
			if (!create_pipe(&parse_list))
				return ;
		}
		else if (if_redir(tmp->type))
		{
			if (!create_redir(tmp, parse_list))
				return ;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return ;
}

t_parse	*parsing(t_token *tokens)
{
	t_parse	*parse_list;
	t_token	*tmp;

	tmp = tokens->next;
	parse_list = NULL;
	if (!tokens)
		return (NULL);
	if (invalid_operator(tmp))
		return (NULL);
	parse_list = init_parse();
	create_parse_list(parse_list, tokens);
	return (parse_list);
}
