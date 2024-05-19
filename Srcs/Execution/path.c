/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:55:43 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:21:02 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static char	**get_data_of_paths(const char *path)
{
	char	**table;

	table = ft_split_ignore_spaces(path, ':');
	return (table);
}

static char	*create_executable_path(const char *path, const char *cmd)
{
	char	*executable_path;
	char	*cmd_path;

	executable_path = ft_strjoin(path, "/");
	if (!executable_path)
		return (NULL);
	cmd_path = ft_strjoin2(executable_path, cmd);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static char	*find_executable(char **dirs, const char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		cmd_path = create_executable_path(dirs[i], cmd);
		if (!cmd_path)
			break ;
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_executable_path(const char *cmd, const char *path)
{
	char	**dirs;
	char	*executable_path;

	dirs = get_data_of_paths(path);
	if (!dirs)
		return (NULL);
	executable_path = find_executable(dirs, cmd);
	free_darray(dirs);
	return (executable_path);
}
