/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:48:10 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 12:30:01 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/included.h"

int	is_built_in(t_cmd *cmd)
{
	int		i;
	char	*built_in[] = {"/bin/pwd", "/bin/cd", "/bin/env", "/bin/echo", "/bin/exit", "/bin/export",
		"/bin/unset","pwd", "cd", "env", "echo", "exit", "export",
		"unset", NULL};

	i = 0;
	if (!cmd)
		return (0);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd->str))
			return (1);
		i++;
	}
	return (0);
}
// static void	ft_builtin(t_cmd *cmd, t_env *env, t_num_cmd cmd_num, t_data *data)
// {
// 	int	b_status;

// 	b_status = 0;
// 	if (!strcmp(cmd->str, "echo") || !strcmp(cmd->str, "/bin/echo"))
// 		b_status = builtin_echo(cmd);
// 	else if (!strcmp(cmd->str, "cd") || !strcmp(cmd->str, "/bin/cd"))
// 		b_status = builtin_cd(cmd, env);
// 	else if (!strcmp(cmd->str, "pwd") || !strcmp(cmd->str, "/bin/pwd"))
// 		b_status = builtin_pwd();
// 	else if (!strcmp(cmd->str, "env") || !strcmp(cmd->str, "/bin/env"))
// 		b_status = builtin_env(env);
// 	else if (!strcmp(cmd->str, "export") || !strcmp(cmd->str, "/bin/export"))
// 		b_status = builtin_export(cmd, env);
// 	else if (!strcmp(cmd->str, "unset") || !strcmp(cmd->str, "/bin/unset"))
// 		b_status = builtin_unset(cmd, env);
// 	else if (!strcmp(cmd->str, "exit") || !strcmp(cmd->str, "/bin/exit"))
// 		b_status = builtin_exit(cmd, data);
// 	if (cmd_num == ONE_CMD)
// 		g_status = b_status;
// }

void	builtin_exec(t_parse *parse_list, t_data *data)
{
	(void) parse_list;
	(void) data;
	//ft_builtin(parse_list->cmd, data->env, ONE_CMD, data);
	printf("va_tu dans la fichier Builtins/builtins_utils;Tu dois commencer d'ici. au debut tu dois supprimer (void) parse_list; et (void) data; \n \"" 
	"apres supprime // avant ft_builtin() et cette fonction et static just audessus de actuelle fonction \n \"" 
	"\"j'ai ecrit les noms des fonctions et ses argument.Tu peux regarder des stucturs (cmd et env)\n");

}
