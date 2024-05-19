/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:48:05 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:21:58 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

char	**get_cmd_args(t_parse *parse_list)
{
	int		i;
	char	**argv;
	t_cmd	*temp;

	i = 0;
	argv = NULL;
	temp = parse_list->cmd;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	argv = (char **)malloc((i + 2) * sizeof(char *));
	if (!argv)
		return (perror("malloc"), NULL);
	i = 0;
	temp = parse_list->cmd;
	while (temp)
	{
		argv[i] = ft_strdup(temp->str);
		temp = temp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
