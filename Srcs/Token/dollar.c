/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:09:09 by romina            #+#    #+#             */
/*   Updated: 2024/04/25 19:38:34 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static char	*find_var_value(t_env *env, char *str, int *i)
{
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	char	*expand_str;
	char	*after_str;

	var_name_len = env_var_name_len(str);
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

static char	*dollar_equal(t_env *fake_env, char **before, char **str, int *i)
{
	char	*after_dollar;
	char	*sub;

	sub = ft_substr(*str, 0, *i);
	if ((*str)[*i + 1] == '=')
		*before = ft_strjoin(sub, "$=");
	else if ((*str)[*i + 1] == ':')
		*before = ft_strjoin(sub, "$:");
	free(sub);
	after_dollar = find_var_value(fake_env, (*str + *i + 2), i);
	*i += 1;
	return (after_dollar);
}


void	expand_dollar(t_env *env, char **str, int *i, int quote)
{
	char	*before;
	char	*after;

	// if (!(*str)[*i + 1] || (*str)[*i + 1] == ' '
	// 	|| ((*str)[*i + 1] == '\'' && quote == 1)
	// 	|| ((*str)[*i + 1] == '\"' && quote == 1 && !(*str)[*i + 2]))
	// 	return ;
	if (!(*str)[*i + 1] || (*str)[*i + 1] == ' '
		|| ((*str)[*i + 1] == '\'' && quote == 1)
		|| ((*str)[*i + 1] == '\"' && quote == 1))
		return ;
	else
	{	
		if ((*str)[*i + 1] == '=' || (*str)[*i + 1] == ':')
			after = dollar_equal(env, &before, str, i);
		else
		{
			before = ft_substr(*str, 0, *i);	
			after = find_var_value(env, *str + *i + 1, i);
		} 
		free(*str);
		*str = ft_strjoin(before, after);
		// if (before)
			free(before);
		// if (after)
			free(after);
    }

}



////////////////////////////////////////////////////////////////////////////
// int	dollar_sign(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			if (str[i] == '?' || str[i] == '_' || ft_isalpha(str[i])
// 				|| ft_isdigit(str[i]))
// 				return (1);
// 			else if (str[i] == '\0')
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// static char	*dollar_backslash(char **before, char **str, int *i, int *k)
// {
// 	char	*after_dollar;
// 	char	*sub;

// 	// *k = 1;
// 	(void)k;
// 	sub = ft_substr(*str, 0, *i);
// 	printf("sub %s\n", sub);
// 	*before= ft_strjoin(sub, "$");
// 	after_dollar = *str + *i + 2;
// 	*i += 1;
// 	free(sub);
// 	return (after_dollar);
// }

// static char	*dollar_pid(char **before, char **str, int *i, int *k)
// {
// 	pid_t	pid;
// 	char	*after_dollar;
// 	char	*pid_str;
// 	char	*sub;

// 	*k = 2;
// 	sub = ft_substr(*str, 0, *i);
// 	pid = getpid();
// 	if (!pid)
// 	{
// 		perror("pid system call error");
// 		if (sub)
// 			free(sub);
// 		return NULL;
// 	}
// 	pid_str = ft_itoa(pid);
// 	*before = ft_strjoin(sub, pid_str);
// 	if (sub)
// 		free(sub);
// 	after_dollar = *str + *i + 2;
// 	// printf("after %s\n", after_dollar);
// 	*i += (ft_strlen(pid_str) - 1);
// 	free(pid_str);
// 	return (after_dollar);
// }

// static char	*find_env_value(char *str, t_env *env)
// {
// 	t_env	*head;

// 	head = env;
// 	while (head)
// 	{
// 		if (!ft_strcmp(head->var_name, str))
// 			return (head->var_value);
// 		head = head->next;
// 	}
// 	return (NULL);
// }
// static char	*other_after_dollar_case(t_env *fake_env, char **str, int *i)
// {
// 	char	*after_dollar;
// 	char	*value;
// 	char	*first_part;
// 	char	*uid_value;

// 	after_dollar = NULL;
// 	if (str && *str)
// 	{
// 		if (!ft_strncmp(*str + *i + 1, "UID", 3))
// 		{
// 			value = find_env_value("XDG_RUNTIME_DIR", fake_env);
// 			first_part = ft_substr(value, 0, 10);
// 			uid_value = value + ft_strlen(first_part);
// 			after_dollar = ft_strjoin(uid_value, (*str + *i + 4));
// 			free(first_part);
// 		}
// 		else
// 			after_dollar = find_var_value(fake_env, *str + *i + 1, i);
// 	}
// 	return (after_dollar);
// }
