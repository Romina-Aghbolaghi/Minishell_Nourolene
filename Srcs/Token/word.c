/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:21:12 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:29:08 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

char	*expand_word(t_env *env, char *splited_line)
{
	int	i;
	int	j;
	int	double_quote;

	i = 0;
	j = 0;
	double_quote = 0;
	while (splited_line[i])
	{
		if (splited_line[i] == '\"')
			double_quote = !double_quote;
		if (splited_line[i] == '\'' && double_quote == 0)
			next_s_quote(splited_line, &i);
		else if (splited_line[i] == '$')
			expand_dollar(env, &splited_line, &i, double_quote);
		i++;
	}
	return (splited_line);
}

void	add_word_token(t_token **tokens, t_type type, char *expand_str)
{
	int	s_str;
	int	e_str;

	s_str = 0;
	e_str = 0;
	while (expand_str[e_str])
	{
		s_str = e_str;
		e_str = word_token_index(expand_str, e_str);
		add_token(tokens, type, ft_substr(expand_str, s_str, (e_str - s_str
					+ 1)));
		e_str++;
	}
	free(expand_str);
}
