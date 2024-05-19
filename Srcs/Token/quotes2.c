/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:39:24 by rmohamma          #+#    #+#             */
/*   Updated: 2024/05/19 16:29:23 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

void	next_s_quote(char *str, int *i)
{
	while (str[*i + 1] != '\'')
		(*i)++;
	(*i)++;
}

void	delete_quotes(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens->next;
	while (tmp)
	{
		if (tmp->type == WORD)
			create_new_words(tmp->value);
		tmp = tmp->next;
	}
}

void	create_new_words(char *value)
{
	int	index;
	int	prev_index;

	index = 0;
	prev_index = 0;
	while (value[index])
	{
		if (value[index] == '\"')
			remove_quotes(value, '\"', &index, &prev_index);
		else if (value[index] == '\'')
			remove_quotes(value, '\'', &index, &prev_index);
		else
		{
			value[prev_index] = value[index];
			++prev_index;
			++index;
		}
	}
	value[prev_index] = '\0';
}

void	remove_quotes(char *str, char quote, int *index, int *prev_index)
{
	(*index)++;
	while (str[*index] != quote)
	{
		str[*prev_index] = str[*index];
		(*index)++;
		(*prev_index)++;
	}
	(*index)++;
}
