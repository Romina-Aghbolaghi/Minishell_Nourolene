/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   included.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:22:11 by romina            #+#    #+#             */
/*   Updated: 2024/04/26 13:06:33 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_H
# define INCLUDED_H

#include <readline/history.h>
#include <readline/readline.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stddef.h>

# include "../libft/libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

/*COLORS*/
# define BLUE_COLOR "\033[1;36m"
# define RESET_BLUE_COLOR "\033[0m"
# define PURPLE_COLOR "\x1b[35m"
# define RESET_PURPLE_COLOR "\x1b[0m"

/*CONSTANTS*/
# define TRUE 1
# define FAULSE 0
# define OTHER -1
# define SUCCES ((void *)1)

extern int				g_status;



/*ENUM CONSTANT*/
typedef enum e_type
{
	S_QUOT,
	D_QUOT,
	WORD,
	PIPE,
	REDIR_IN,
	red_out,
	HEREDOC,
	APPEND
}						t_type;

typedef enum e_sig_state
{
	SIG_DEFAULT = 1,
	SIG_HEREDOC,
	SIG_CHILD,
	SIG_PARENT
}					t_sig_state;



typedef enum e_num_cmd
{
	ONE_CMD,
	MULTI_CMD
}						t_num_cmd;


//////////////////////////EXEC STRUCTS/////////////////////////

typedef struct s_cmd_line
{
	int					fd[2];
	int					red_input;
	int					red_output;
	int					cmd_index;
	int					cmds_num;
	char				*path;
	char				*exec_path;
}						t_cmd_line;


// typedef struct s_here_doc
// {
// 	int					read_fd;
// 	struct s_here_doc	*next;
// }						t_here_doc;



//////////////////////////PARSING STRUCTS/////////////////////////




typedef struct s_redir
{
	t_type				type;
	char				*file_name;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char			*str;
	struct s_cmd	*next;
}						t_cmd;

typedef struct s_parse
{
	t_cmd			*cmd;
	t_redir			*red_in;
	t_redir			*red_out;
	struct s_parse	*next;
	// struct s_parse	*prev;
	
}						t_parse;

typedef struct s_token //ok
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}						t_token;


typedef struct s_env //ok
{
	char				*var_name;
	char				*var_value;
	char				*str;
	struct s_env		*next;
}						t_env;


typedef struct s_data //ok
{
	t_env				*env;
	t_token				*tokens;
	t_parse				*parse_list;
	t_cmd_line			*cl_info;
	// t_here_doc			*here_doc;
	// t_arg				*arg;//exec part
}						t_data;



///////////////////////////////FUNCTIONS///////////////////////////////////

/*environment*/

/*ENV*/
void	create_env(t_env *head, char **envp);
void	manipulate_env(t_env *head, char *str);

/*ENV_UTILS*/
char	*env_var_name(char *str);
int     env_var_name_len(char *var_name);
char	*env_var_value(t_env *env, char *var_name);


/*errors*/

void	parantes_error(char *str);
void	unclosed_error(char *str);
void	*syntax_error(char *str);
void	*chdir_error(char *str);



/*free*/

/*FREE_ENV*/
void	free_env(t_env **env);


/*FREE_PARSING*/
void	*free_token(t_token *tokens);
void	free_data(t_data *data);
void	*free_parse(t_parse *head);

/*FREE_ALL*/
void	safe_exit(t_data *data);



/*initialization*/

t_env	*init_env(char **envp);
void	init_data(t_data *data, t_env *env);
t_token	*init_token(void);
t_parse	*init_parse(void);
t_cmd	*init_cmd(char *str);
t_redir	*init_redir(t_type type, char *name);


/*initialization2*/
void	init_cmd_line(t_cmd_line *cmd_info, t_parse *parse_list);



/*minishell*/


void	invalid_arg_msg(int argc, char **argv);
void	shell_exec(t_env *env, char *line, t_data *data);




/*parsing*/

/*PARSING*/
t_parse	*parsing(t_token *tokens);


/*PARSING UTILS*/
void	create_cmd(t_token *tokens, t_parse *parse_list);
void	*create_pipe(t_token **token, t_parse **parse_list);
t_redir	*create_redir(t_token *tokens, t_parse *parse_list);




/*signals*/

void	sig_handle(int state);





/*token*/


/*CREATE_TOKENS*/
t_token	*tokening(t_env *env, char *line);
int	split_line(t_env *env, char *line, t_token **tokens);
void	add_token(t_token **head, t_type type, char *value);

 /*TOKEN_UTILS*/
int	skip_white_spaces(char *s, int i);
int	ft_isspace(char c);


/*QUOTES*/
int	check_unclosed(char *s);


/*GET_INDEX*/
int	is_operator(char c);
int	get_operator_index(char *line, int i, t_type *type);
int	get_token_index(char *line, int i, t_type curr_type, t_type *type);
int	get_quote_index(char *line, int i, t_type type);
int	word_token_index(char *line, int i);



/*WORD*/
char	*expand_word(t_env *env, char *splited_line);



/*DOLLAR*/
void	expand_dollar(t_env *env, char **str, int *i, int quote);


/*QOTES*/
int	   check_unclosed(char *s);
void	next_s_quote(char *str, int *i);
void	delete_quotes(t_token *tokens);
void	create_new_words(char *value);
void	remove_quotes(char *str, char quote, int *index, int *prev_index);


/*WORD*/
char	*expand_word(t_env *env, char *splited_line);
void	add_word_token(t_token **tokens, t_type type, char *expand_str);





/*EXECUTION*/

/*cmd_execution*/
void	cl_exec(t_data *data);


/*BUILTINS*/
/*builtinn_utils*/
int		is_built_in(t_cmd *cmd);
void	builtin_exec(t_parse *parse_list, t_data *data);


/*builtins_cd*/


int	builtin_echo(t_cmd *cmd);
int	builtin_cd(t_cmd *cmd, t_env *env);
int	builtin_unset(t_cmd *cmd, t_env *env);
int	builtin_exit(t_cmd *cmd, t_data *data);
int	builtin_env(t_env *env);
int	builtin_pwd(void);
int	builtin_export(t_cmd *cmd, t_env *env);






void	print_parse_list(t_parse *parse_list);



#endif