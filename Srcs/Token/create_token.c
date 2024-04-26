/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:32:25 by romina            #+#    #+#             */
/*   Updated: 2024/04/20 16:48:54 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

t_token	*tokening(t_env *env, char *line)
{
	t_token	*tokens;

	tokens = init_token();
	if (check_unclosed(line))
	{
		free_token(tokens);
		return (NULL);
	}
	if (!split_line(env, line, &tokens))
	{
		free_token(tokens);
		return (NULL);
	}
	delete_quotes(tokens);
	return (tokens);
}

static void	token_process(t_env *env, t_token **tokens, t_type type, char *splited_line)
{
	if (type == WORD)
		add_word_token(tokens, type, expand_word(env, splited_line));
	else
		add_token(tokens, type, splited_line);
}

int	split_line(t_env *env, char *line, t_token **tokens)
{
	int				s_str;
	int				e_str;
	t_type			type;

	e_str = 0;
	type = 0;
	if (line)
	{	
		while (line[e_str])
		{
			e_str = skip_white_spaces(line, e_str);
			if (!line[e_str])
				break ;
			s_str = e_str;
			if (is_operator(line[e_str]))
				e_str = get_operator_index(line, e_str, &type);
			else
				e_str = get_token_index(line, e_str, WORD, &type);
			token_process(env, tokens, type, ft_substr(line, s_str,
							(e_str - s_str + 1)));
			e_str++;
		}
		return (1);
	}
	return (0);		
}

static t_token	*create_token(t_type type, char *value)
{
	t_token	*new;

	new = init_token();
	new->type = type;
	new->value = value;
	return (new);
}

void	add_token(t_token **head, t_type type, char *value)
{
	t_token	*tmp;

	if (!*head)
	{
		free(*head);
		*head = create_token(type, value);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_token(type, value);
		if (!tmp->next)
			return ;
	}
}


