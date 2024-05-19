/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:48:21 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:23:36 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static char	*rest_part(t_env *fake_env)
{
	char	*user;
	char	*joined;
	char	*home;
	char	*pointer;
	char	*joined2;

	user = env_var_value(fake_env, "USER");
	joined2 = ft_strjoin(user, ":");
	home = env_var_value(fake_env, "HOME");
	pointer = getcwd(NULL, 0);
	joined = ft_strjoin(joined2, pointer);
	free(home);
	free(pointer);
	free(user);
	free(joined2);
	return (joined);
}

static char	*final_prompt(char *joined)
{
	int		len;
	int		i;
	int		j;
	char	*prompt;

	i = 0;
	j = 0;
	len = ft_strlen(joined);
	prompt = (char *)malloc(sizeof(char) * (len + 3));
	if (!prompt)
	{
		printf("Alloc failure\n");
		return (NULL);
	}
	while (joined && joined[j])
	{
		prompt[i] = joined[j];
		i++;
		j++;
	}
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}

char	*ft_prompt(t_env *fake_env)
{
	char	*prompt;
	char	*joined;

	joined = rest_part(fake_env);
	prompt = final_prompt(joined);
	free(joined);
	return (prompt);
}

char	*prompt_in_color(char *prompt)
{
	char	*first;
	char	*second;

	first = NULL;
	second = NULL;
	first = ft_strjoin(PURPLE_COLOR, prompt);
	free(prompt);
	second = ft_strjoin(first, RESET_PURPLE_COLOR);
	free(first);
	return (second);
}

// // static char	*ft_tilde_prompt(char *joined2, char *pointer, char *home)
// // {
// // 	int		len;
// // 	char	*joined3;
// // 	char	*joined;

// // 	joined3 = ft_strjoin(joined2, "~");
// // 	len = ft_strlen(home);
// // 	pointer = pointer + len;
// // 	joined = ft_strjoin(joined3, pointer);
// // 	free(joined3);
// // 	return (joined);
// // }

// static char	*rest_part(t_env *fake_env)
// {
// 	char	*user;
// 	char	*joined;
// 	char	*home;
// 	char	*pointer;
// 	char	*joined2;

// 	user = env_var_value(fake_env, "USER");
// 	joined2 = ft_strjoin(user, ":");
// 	home = env_var_value(fake_env, "HOME");
// 	pointer = getcwd(NULL, 0);
// 	// if (home && *home && ft_strcmp(pointer, home) >= 0)
// 	// 	joined = ft_tilde_prompt(joined2, pointer, home);
// 	// else
// 		joined = ft_strjoin(joined2, pointer);
// 	free(home);
// 	free(pointer);
//     free(user);
// 	free(joined2);
// 	return (joined);
// }
