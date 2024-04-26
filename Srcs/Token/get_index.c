/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:31:29 by romina            #+#    #+#             */
/*   Updated: 2024/04/24 15:32:53 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"


int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	get_operator_index(char *line, int i, t_type *type)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (get_token_index(line, i, HEREDOC, type));
		else
			return (get_token_index(line, i, REDIR_IN, type));
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (get_token_index(line, i, APPEND, type));
		else
			return (get_token_index(line, i, red_out, type));
	}
	else if (line[i] == '|')
		return (get_token_index(line, i, PIPE, type));
	return (i);
}

int	get_token_index(char *line, int i, t_type curr_type, t_type *type)
{
	*type = curr_type;
	if (curr_type == WORD)
	{
		while (line[i])
		{
            if (line[i] == '\"')
				i = get_quote_index(line, i + 1, D_QUOT);
			else if (line[i] == '\'')
				i = get_quote_index(line, i + 1, S_QUOT);
			if (ft_isspace(line[i + 1]) || is_operator(line[i + 1])
				|| !line[i + 1])
				return (i);
			++i;
		}
	}
	else if (curr_type == HEREDOC || curr_type == APPEND)
		i = i + 1;
	return (i);
}

int	get_quote_index(char *line, int i, t_type type)
{
	if (type == D_QUOT)
	{
		while (line[i] != '\"')
			++i;
	}
	else  if (type == S_QUOT)
	{
		while (line[i] != '\'')
			++i;
	}
	return (i);
}

int	word_token_index(char *line, int i)
{
	while (line[i + 1] != '\0')
	{
		if (line[i] == '\'')
			i = get_quote_index(line, i + 1, S_QUOT);
		else if (line[i] == '\"')
			i = get_quote_index(line, i + 1, D_QUOT);
		if (ft_isspace(line[i + 1]) || line[i + 1] == '\0')
			return (i);
		++i;
	}
	return (i);
}

