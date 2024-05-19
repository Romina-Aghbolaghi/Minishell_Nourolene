/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:00:45 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:28:58 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static int	is_char_in_set(char c, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i++])
			return (1);
	}
	return (0);
}

static char	*find_quote(char *s, char *set)
{
	while (*s)
	{
		if (is_char_in_set(*s, set))
			return (s);
		s++;
	}
	return (NULL);
}

static char	*move_to_next_quote(char **ptr, char c)
{
	char	*next_closed_quote;

	next_closed_quote = ft_strchr((*ptr) + 1, c);
	if (next_closed_quote)
		*ptr = next_closed_quote;
	return (next_closed_quote);
}

int	check_unclosed(char *s)
{
	while (s && *s)
	{
		if (is_char_in_set(*s, "\"\'") && !move_to_next_quote(&s, *s))
		{
			if (*s == '\'')
				return (unclosed_error("single quote"), 1);
			return (unclosed_error("double quotes"), 1);
		}
		s = find_quote(s + 1, "\'\"");
	}
	return (0);
}
