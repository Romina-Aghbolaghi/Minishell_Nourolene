/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouabdul <nouabdul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:41:17 by nouabdul          #+#    #+#             */
/*   Updated: 2024/05/22 15:52:16 by nouabdul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/included.h"

static void	home_notset(char *cmd, t_env *env, int *status)
{
	if (!cmd)
	{
		*status = home_dir_exec(cmd, env, "HOME");
		if (*status == -1)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			*status = 1;
		}
	}
}

static void	prev_directory(char *head, t_env *env, int *status)
{
	if (!ft_strcmp(head, "-"))
	{
		*status = home_dir_exec(head, env, "OLDPWD");
		if (*status == -1)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			*status = 1;
		}
		else
			print_pwd(env, "PWD");
	}
}

static char	*create_path(char *head)
{
	char	*path;
	char	*tmp;
	char	*cwd;

	path = NULL;
	cwd = NULL;
	tmp = NULL;
	if (head[0] == '/')
		path = ft_strdup(head);
	else
	{
		cwd = getcwd(NULL, 0);
		tmp = ft_strjoin(cwd, "/");
		path = ft_strjoin(tmp, head);
		free(tmp);
		free(cwd);
	}
	return (path);
}

int	change_directory(char *path, t_env *env, char *cmd)
{
	int	res;

	res = chdir(path);
	if (res)
		chdir_error(cmd);
	else
		swap_pwd_old(env);
	if (res == -1)
		return (1);
	else
		return (res);
}

int	builtin_cd(char **cmd, t_env *env)
{
	int		status;
	int		i;
	char	*path;
	t_env	*tmp_env;

	i = 1;
	status = -1;
	path = NULL;
	tmp_env = env->next;
	if (cmd[i] && cmd[i + 1])
		return (error_many_args(cmd[0]), 1);
	home_notset(cmd[1], tmp_env, &status);
	while (cmd[i])
	{
		prev_directory(cmd[i], tmp_env, &status);
		if (status == -1)
		{
			path = create_path(cmd[i]);
			if (path)
				status = change_directory(path, tmp_env, cmd[i]);
		}
		i++;
	}
	free(path);
	return (status);
}
