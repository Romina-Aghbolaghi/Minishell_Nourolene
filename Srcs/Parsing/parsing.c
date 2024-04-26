/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:50:49 by romina            #+#    #+#             */
/*   Updated: 2024/04/24 16:43:47 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/included.h"

static int	if_redir(t_type type)
{
	if (type == REDIR_IN || type == HEREDOC
		|| type == red_out || type == APPEND)
		return (1);
	return (0);
}
void	*invalid_operator(t_token *tokens)
{
	if (ft_strcmp(tokens->value, "&") == 0
        || ft_strcmp(tokens->value, ";") == 0
		|| ft_strcmp(tokens->value, "&&") == 0)
		return (syntax_error(tokens->value));
	return (SUCCES);
}



static void	parsing_processe(t_parse *parse_list, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens->next;
	while (tmp)
	{
		/*PRINT THE RESUALT*/
		// ft_putstr_fd(BLUE_COLOR, 1);
		// printf("token-value: [ %s ]\n\n", tokens->value);
		// ft_putstr_fd(RESET_BLUE_COLOR, 1);

		if (!invalid_operator(tmp))
			return ;
		if (tmp->type == WORD)
			create_cmd(tmp, parse_list);
		else if (tmp->type == PIPE)
		{
			if (!create_pipe(&tmp, &parse_list))
				return ;
		}
		else if (if_redir(tmp->type))
		{
			if (!create_redir(tmp, parse_list))
				return ;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return ;
}

static void	create_parse(t_parse *parse_list, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens->next;
	if (tmp && tmp->type == PIPE)
	{
		syntax_error(tmp ->value);
		return ;
	}
	parsing_processe(parse_list, tokens);
}
t_parse	*parsing(t_token *tokens)
{
	t_parse	        *parse_list;

	parse_list = NULL;
	if (!tokens)
		return (NULL);
	parse_list = init_parse();
    create_parse(parse_list, tokens);
	//////////////FOR PRINT RESUALT///////////////////
	// t_parse  *tmp = parse_list;
	// while (tmp)
	// {
	// 	ft_putstr_fd(PURPLE_COLOR, 1);
	// 	if (tmp->cmd)
	// 	{
	// 		while (tmp->cmd)
	// 		{
	// 			printf("cmd: [ %s ]\n\n", tmp->cmd->str);
	// 			tmp->cmd = tmp->cmd->next;
	// 		}
	// 	}		
	// 	else if (tmp->red_in)
	// 	{	
	// 	printf("redir_in: [ %u ]\n", tmp->red_in->type);
	// 	printf("redir_in file: [ %s ]\n\n", tmp->red_in->file_name);
	//  	}		
	// 	else if (tmp->red_out)
	// 	{	
	// 		printf("red_out: [ %u ]\n", tmp->red_out->type);
	// 		printf("red_out file: [ %s ]\n\n", tmp->red_out->file_name);
	//  	}
	// 	else
	// 		printf("type is pipe\n");

	// 	ft_putstr_fd(RESET_PURPLE_COLOR, 1);
	// 	tmp = tmp->next;
	// }
	//////////////FOR PRINT RESUALT///////////////////
	
	return (parse_list);
}


// static int	parsing_processe(t_parse *parse_list, t_token *tokens)
// {
// 	t_token	*tmp;

// 	tmp = tokens->next;
// 	while (tmp)
// 	{
// 		/*PRINT THE RESUALT*/
// 		ft_putstr_fd(BLUE_COLOR, 1);
// 		printf("token-value: [ %s ]\n\n", tokens->value);
// 		ft_putstr_fd(RESET_BLUE_COLOR, 1);

// 		if (!invalid_operator(tmp))
// 			return (0);
// 		if (tmp->type == WORD)
// 			create_cmd(tmp, parse_list);
// 		else if (tmp->type == PIPE)
// 		{
// 			if (!create_pipe(&tmp, &parse_list))
// 				return (0);
// 		}
// 		else if (if_redir(tmp->type))
// 		{
// 			if (!create_redir(tmp, parse_list))
// 				return (0);
// 			tmp = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (TRUE);
// }

// static int	create_parse(t_parse *parse_list, t_token *tokens)
// {
// 	t_token	*tmp;

// 	tmp = tokens->next;
// 	if (tmp && tmp->type == PIPE)
// 	{
// 		syntax_error(tmp ->value);
// 		return (0);
// 	}
// 	return (parsing_processe(parse_list, tokens));
// }

// t_parse	*parsing(t_token *tokens)
// {
// 	t_parse	        *parse_list;

// 	parse_list = NULL;
// 	if (!tokens)
// 		return (NULL);
// 	parse_list = init_parse();
//     if (!create_parse(parse_list, tokens))
//     {
//         free_parse(parse_list);
//         return (NULL);
//     }
// 	return (parse_list);
// }


/////////////////////////////////////////////////////////////////////////
// static int	create_parse(t_parse *parse_list, t_token *tokens)
// {
// 	t_token	*tmp;

// 	tmp = tokens->next;
// 	if (tmp  && tmp ->type == PIPE)
// 	{
// 		syntax_error(tmp ->value);
// 		return (-1);
// 	}
// 	while (tmp)
// 	{
// 		if (!invalid_operator(tmp))
// 			return (-1);
// 		if (tmp->type == WORD)
// 			create_cmd(tmp, parse_list);
//         else if (if_redir(tmp->type))
// 		{
// 			if (!create_redir(tmp, parse_list))
// 				return (-1);
// 			tmp = tmp->next;
// 		}
// 		else if (tmp->type == PIPE)
// 		{
// 			if (!create_pipe(&tmp, &parse_list))
// 				return (-1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }


