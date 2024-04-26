/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:00:45 by romina            #+#    #+#             */
/*   Updated: 2024/04/24 10:46:00 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static char	*move_to_next_char(char **ptr, char c)
{
	char	*cursor;

	cursor = ft_strchr((*ptr) + 1, c);
	if (cursor)
		*ptr = cursor;
	return (cursor);
}

static int  is_char_in_set(char c, char *s)
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

static char	*ft_strchrs(char *s, char *set)
{
	while (*s)
	{
		if (is_char_in_set(*s, set))
			return (s);
		s++;
	}
	return (NULL);
}

int	check_unclosed(char *s)
{
	int	open_parenthesis;

	open_parenthesis = 0;
	while (s && *s)
	{
		if (*s == '(')
			open_parenthesis++;
		else if (*s == ')' && open_parenthesis-- < 1)
			return (parantes_error("`)'"), 1);
		else if (is_char_in_set(*s, "\"\'") && !move_to_next_char(&s, *s))
		{
			if (*s == '\'')
				return (unclosed_error("single quote"), 1);
			return (unclosed_error("double quotes"), 1);
		}
		s = ft_strchrs(s + 1, "\'\"()");
	}
	if (open_parenthesis)
		return (unclosed_error("parenthesis"), 1);
	return (0);
}

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
	int		index;
	int		prev_index;

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
		// printf(" char  %c \n ",str[*index] );
		(*index)++;
		(*prev_index)++;
	}
	(*index)++;
}




///////////////////////////////////////////////////////////////////////////////
// static char	*ft_strndup(const char *s, size_t n)
// {
// 	char	*dup;
// 	size_t	i;

// 	dup = (char *)malloc((n + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
// void	create_new_words(char *value)
// {
// 	int		index;
// 	int		prev_index;
// 	char	*trimmed_str;

// 	index = 0;
// 	prev_index = 0;
// 	while (value[index])
// 	{
// 		if (value[index] == '\"')
// 			remove_quotes(value, '\"', &index, &prev_index);
// 		else if (value[index] == '\'')
// 			remove_quotes(value, '\'', &index, &prev_index);
// 		else
// 		{
// 			trimmed_str = ft_strndup(&(value)[1], ft_strlen(&(value)[1]) - 1);
// 			if (!trimmed_str)
// 				return ;
// 			free(*value);
// 			*value = trimmed_str;
// 		}
// 	}
// 	// value[prev_index] = '\0';
// 	// printf("token->value:[ %s ]\n", value);
// }
// // static void	cut_quotes2(char **str)
// // {
// // 	char	*trimmed_str;

// // 	if (!ft_is_char_in_set(**str, "\'\""))
// // 		return ;
// // 	trimmed_str = ft_strndup(&(*str)[1], ft_strlen(&(*str)[1]) - 1);
// // 	if (!trimmed_str)
// // 		return ;
// // 	free(*str);
// // 	*str = trimmed_str;
// // }

// void	remove_quotes(char **str, char quote, int *index, int *prev_index)
// {
// 	(void*)prev_index;
// 	char	*trimmed_str;
// 	(*index)++;
// 	while (str[*index] != quote)
// 	{
// 	trimmed_str = ft_strndup(&str[*index], ft_strlen(&str[*index]) - 1);
// 	if (!trimmed_str)
// 		return ;
// 	free(*str);
// 	*str = trimmed_str;
// 	}
// 	(*index)++;
// }

