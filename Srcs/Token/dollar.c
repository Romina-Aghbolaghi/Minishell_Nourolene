/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:09:09 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:28:52 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static char	*find_var_value(t_env *env, char *str, int *i)
{
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*expand_str;
	char	*after_str;

	var_name_len = env_var_len(str);
	var_name = ft_substr(str, 0, var_name_len);
	var_value = env_var_value(env, var_name);
	after_str = ft_substr(str, var_name_len, ft_strlen(str));
	*i = *i + ft_strlen(var_value) - 1;
	expand_str = ft_strjoin(var_value, after_str);
	free(var_value);
	free(var_name);
	free(after_str);
	return (expand_str);
}

static char	*dollar_signs(t_env *fake_env, char **before, char **str, int *i)
{
	char	*after_dollar;
	char	*sub;

	sub = ft_substr(*str, 0, *i);
	if ((*str)[*i + 1] == '=')
		*before = ft_strjoin(sub, "$=");
	else if ((*str)[*i + 1] == ':')
		*before = ft_strjoin(sub, "$:");
	else if ((*str)[*i + 1] == '+')
		*before = ft_strjoin(sub, "$+");
	free(sub);
	after_dollar = find_var_value(fake_env, (*str + *i + 2), i);
	*i += 1;
	return (after_dollar);
}

void	expand_dollar(t_env *env, char **str, int *i, int quote)
{
	char	*before;
	char	*after;

	if (!(*str)[*i + 1] || (*str)[*i + 1] == ' ' || ((*str)[*i + 1] == '\''
			&& quote == 1) || ((*str)[*i + 1] == '\"' && quote == 1))
		return ;
	else
	{
		if ((*str)[*i + 1] == '=' || (*str)[*i + 1] == ':' || (*str)[*i
			+ 1] == '+')
			after = dollar_signs(env, &before, str, i);
		else
		{
			before = ft_substr(*str, 0, *i);
			after = find_var_value(env, *str + *i + 1, i);
		}
		free(*str);
		*str = ft_strjoin(before, after);
		free(before);
		free(after);
	}
}
