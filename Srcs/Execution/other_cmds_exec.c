/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:45:51 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:21:20 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static char	*env_var_value2(t_env *env, char *var_name)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env->next;
	while (head)
	{
		if (var_name[0] == '?')
			return (ft_itoa(g_status));
		else if (!ft_strcmp(var_name, head->var_name))
		{
			if (!head->var_value)
				return (NULL);
			return (head->var_value);
		}
		head = head->next;
	}
	return (NULL);
}

static int	ft_isdirectory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	other_cmds_exec(t_data *data, t_cl_info *exec)
{
	if (!exec->argv)
		return ;
	exec->path = env_var_value2(data->env, "PATH");
	if (ft_strchr(exec->argv[0], '/') || !ft_strncmp(exec->argv[0], "./", 2))
		exec->exec_path = ft_strdup(exec->argv[0]);
	else
		exec->exec_path = get_executable_path(exec->argv[0], exec->path);
	if (!exec->exec_path || !exec->argv[0][0])
	{
		error_msg(exec->argv[0], "command not found", 127);
		if (!exec->next)
			safe_exit(data, 127);
	}
	else if (ft_isdirectory(exec->exec_path))
	{
		error_msg(exec->argv[0], "Is a directory", 126);
		safe_exit(data, 126);
	}
	else if (execve(exec->exec_path, exec->argv, exec->envp) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(exec->argv[0]);
		safe_exit(data, 127);
	}
	safe_exit(data, 0);
}

int	global_status(pid_t last_pid)
{
	pid_t	terminated_pid;
	int		termination_status;
	int		exit_status;

	while (1)
	{
		terminated_pid = wait(&termination_status);
		if (terminated_pid < 0)
			break ;
		if (terminated_pid == last_pid)
		{
			if (WIFEXITED(termination_status))
				exit_status = WEXITSTATUS(termination_status);
			else
				exit_status = 128 + WTERMSIG(termination_status);
		}
	}
	return (exit_status);
}

// void	other_cmds_exec(t_data *data, t_cl_info *exec)
// {
// 	if (!exec->argv)
// 		return ;
// 	exec->path = env_var_value2(data->env, "PATH");
// 	if (ft_strchr(exec->argv[0], '/') || !ft_strncmp(exec->argv[0], "./", 2))
// 		exec->exec_path = ft_strdup(exec->argv[0]);
// 	else
// 		exec->exec_path = get_executable_path(exec->argv[0], exec->path);
// 	// printf("exec->argv %s\n",exec->argv[0] );
// 	// if (access(exec->exec_path, X_OK))
// 	// {
// 	// 	ft_putstr_fd("minishell: ", 2);
// 	// 	perror(exec->argv[0]);
// 	// 	safe_exit(data, 126);
// 	// }
// 	// printf("exec->path %s\n",exec->exec_path);
// 	if (!exec->exec_path || !exec->argv[0][0])
// 	{
// 		error_msg(exec->argv[0], "command not found", 127);
// 		if (!exec->next)
// 			safe_exit(data, 127);
// 	}
// 	// else if (access(exec->exec_path, X_OK))
// 	// {
// 	// 	ft_putstr_fd("minishell: ", 2);
// 	// 	perror(exec->argv[0]);
// 	// 	safe_exit(data, 126);
// 	// }
// 	else if (ft_isdirectory(exec->exec_path))
// 	{
// 		error_msg(exec->argv[0], "Is a directory", 126);
// 		safe_exit(data, 126);
// 	}
// 	else if (execve(exec->exec_path, exec->argv, exec->envp) == -1)
// 	{
// 		// if (access(exec->exec_path, X_OK))
// 		// {
// 		// 	ft_putstr_fd("minishell: ", 2);
// 		// 	perror(exec->argv[0]);
// 		// 	safe_exit(data, 126);
// 		// }
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(exec->argv[0]);
// 		safe_exit(data, 127);
// 		// if( !ft_strncmp(exec->argv[0], "./", 2))
// 		// 	{
// 		// 	safe_exit(data, 126);}
// 		// else
// 		// 	{
// 		// 	safe_exit(data, 127);}
// 	}
// 	safe_exit(data, 0);
// }