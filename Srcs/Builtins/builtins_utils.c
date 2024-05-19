/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:48:10 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:14:32 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

int	is_built_in(char *cmd)
{
	if (!strcmp("/bin/pwd", cmd) || !strcmp("/bin/cd", cmd)
		|| !strcmp("/bin/env", cmd) || !strcmp("/bin/echo", cmd)
		|| !strcmp("/bin/exit", cmd) || !strcmp("/bin/export", cmd)
		|| !strcmp("/bin/unset", cmd) || !strcmp("pwd", cmd) || !strcmp("cd",
			cmd) || !strcmp("env", cmd) || !strcmp("echo", cmd)
		|| !strcmp("exit", cmd) || !strcmp("export", cmd) || !strcmp("unset",
			cmd))
		return (1);
	else
		return (0);
}

int	ft_builtin(t_cl_info *exec, t_env *env, t_data *data)
{
	int	b_status;

	b_status = 127;
	if (exec->file_failed)
		return (error_msg(exec->file_failed, "no such file or directory", 1));
	if (!strcmp(exec->argv[0], "echo") || !strcmp(exec->argv[0], "/bin/echo"))
		b_status = builtin_echo(exec->argv);
	else if (!strcmp(exec->argv[0], "cd") || !strcmp(exec->argv[0], "/bin/cd"))
		b_status = builtin_cd(exec->argv, env);
	else if (!strcmp(exec->argv[0], "pwd") || !strcmp(exec->argv[0],
			"/bin/pwd"))
		b_status = builtin_pwd();
	else if (!strcmp(exec->argv[0], "env") || !strcmp(exec->argv[0],
			"/bin/env"))
		b_status = builtin_env(env);
	else if (!strcmp(exec->argv[0], "export") || !strcmp(exec->argv[0],
			"/bin/export"))
		b_status = builtin_export(exec->argv, data);
	else if (!strcmp(exec->argv[0], "unset") || !strcmp(exec->argv[0],
			"/bin/unset"))
		b_status = builtin_unset(exec->argv, env);
	else if (!strcmp(exec->argv[0], "exit") || !strcmp(exec->argv[0],
			"/bin/exit"))
		b_status = builtin_exit(exec->argv, data);
	return (b_status);
}

int	ft_str_cmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}
