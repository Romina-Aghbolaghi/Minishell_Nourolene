/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   included.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:22:11 by romina            #+#    #+#             */
/*   Updated: 2024/05/19 16:31:24 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_H
# define INCLUDED_H

# include "../libft/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*COLORS*/
# define PURPLE_COLOR "\x1b[35m"
# define RESET_PURPLE_COLOR "\x1b[0m"
# define RED_COLOR "\e[0;31m"
# define RESET_RED_COLOR "\e[0m"
# define HEREDOC_CMD "\e[0;31mheredoc> \e[0m"

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
	REDIR_OUT,
	HEREDOC,
	APPEND
}						t_type;

typedef enum e_sig_state
{
	SIG_DEFAULT = 1,
	SIG_HEREDOC
}						t_sig_state;

//////////////////////////////////EXEC STRUCTS/////////////////////////////

typedef struct s_cl_info
{
	int					red_input;
	int					red_output;
	char				*file_failed;
	char				*heredoc_file;
	char				*path;
	char				**argv;
	char				**envp;
	char				*exec_path;
	struct s_cl_info	*next;
}						t_cl_info;

/////////////////////////////////////PARSING STRUCTS//////////////////////

typedef struct s_redir
{
	t_type				type;
	char				*file_name;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				*str;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_parse
{
	t_cmd				*cmd;
	t_redir				*red_in;
	t_redir				*red_out;
	struct s_parse		*next;
}						t_parse;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*str;
	char				*var_name;
	char				*var_value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	int					fd[2];
	int					pipes[2][2];
	char				*prompt;
	t_env				*env;
	t_token				*tokens;
	t_parse				*parse_list;
	t_cl_info			*exec;
}						t_data;

///////////////////////////////////////FUNCTIONS/////////////////////////

/***************************initialization********************************/

void					init_data(t_data *data, char **envp);
t_token					*init_token(void);

t_parse					*init_parse(void);
t_cmd					*init_cmd(char *str);
t_redir					*init_redir(t_type type, char *name);

/*initialization2*/

t_cl_info				*init_cl_info(t_env *env, t_parse *parse_list);
char					**get_cmd_args(t_parse *parse_list);
char					**duplicate_envp(t_env *env);

/************************************prompt*********************************/
char					*ft_prompt(t_env *fake_env);
char					*prompt_in_color(char *prompt);

/*signals*/
void					sig_handle(int state);
void					sig_ctrlc(int sig);
void					sig_ctrlc2(int sig);

/*****************************environment*********************************/
/*ENV*/
void					create_env(t_env *head, char **envp);
int						env_var_len(char *var_name);

/*ENV_UTILS*/
t_env					*add_env_node(char *str);
char					*env_var_value(t_env *env, char *var_name);
char					*find_path(t_env *env);
void					copy_t_env(t_env *src, t_env **dest);

/*********************************errors***********************************/
int						error_msg(char *cmd, char *detail, int error_nb);
char					*join_strs(char *str, char *add);
void					unclosed_error(char *str);
// void	*syntax_error(char *str);
void					syntax_error(char *str);
void					*chdir_error(char *str);
void					not_valid_error(char *name);
void					error_numeric(char *str, char *cmd_name);
void					error_many_args(char *cmd_name);
void					export_error(char *name);
int						err_msg_heredoc(char *cmd, char *delim, int error_nb);

/*free*/

/*FREE_ENV*/
void					free_env(t_env **env);
void					free_env_unset(t_env *env);
char					*ft_strjoin2(char *s1, char const *s2);

/*FREE_PARSING*/
void					*free_token(t_token *tokens);
void					free_lexer(t_data *data);
void					*free_parse(t_parse *head);

/*FREE_ALL*/
void					free_all(char *line, t_data *data);
void					free_darray(char **table);
void					free_data(t_data *data);
void					free_exec(t_cl_info **exec);
void					safe_exit(t_data *data, long long int i);

/*parsing*/

/*PARSING*/
t_parse					*parsing(t_token *tokens);

/*PARSING UTILS*/
void					create_cmd(t_token *tokens, t_parse *parse_list);
void					*create_pipe(t_parse **parse_list);
t_redir					*create_redir(t_token *tokens, t_parse *parse_list);

/*token*/

/*CREATE_TOKENS*/
t_token					*tokening(t_env *env, char *line);
int						split_line(t_env *env, char *line, t_token **tokens);
void					add_token(t_token **head, t_type type, char *value);

/*TOKEN_UTILS*/
int						skip_white_spaces(char *s, int i);
int						ft_isspace(char c);

/*QUOTES*/
int						check_unclosed(char *s);

/*GET_INDEX*/
int						is_operator(char c);
int						get_operator_index(char *line, int i, t_type *type);
int						get_token_index(char *line, int i, t_type curr_type,
							t_type *type);
int						get_next_quote_index(char *line, int i, t_type type);
int						word_token_index(char *line, int i);

/*WORD*/
char					*expand_word(t_env *env, char *splited_line);

/*DOLLAR*/
void					expand_dollar(t_env *env, char **str, int *i,
							int quote);

/*QOTES*/
int						check_unclosed(char *s);
void					next_s_quote(char *str, int *i);
void					delete_quotes(t_token *tokens);
void					create_new_words(char *value);
void					remove_quotes(char *str, char quote, int *index,
							int *prev_index);

/*WORD*/
char					*expand_word(t_env *env, char *splited_line);
void					add_word_token(t_token **tokens, t_type type,
							char *expand_str);

/*EXECUTION*/

/*cmd_execution*/
int						cl_exec(t_data *data);
int						execute(t_data *data);

/*fd*/
void					ft_close(int *fd);
void					close_all(t_data *data, t_cl_info *temp, int i);
void					copy_std_files(t_data *data);
void					back_to_original_io(t_data *data, t_cl_info *exec);
void					back_red_io_to_original_io(t_data *data,
							t_cl_info *exec);
void					close_in_parent(t_data *data, t_cl_info *exec, int i);

/*BUILTINS*/
/*builtinn_utils*/

int						is_built_in(char *cmd);
int						ft_builtin(t_cl_info *exec, t_env *env, t_data *data);

int						builtin_echo(char **cmd);

int						builtin_export(char **cmd, t_data *data);

t_env					*sort_list(t_env *env);
int						builtin_env(t_env *env);
int						builtin_pwd(void);

int						builtin_unset(char **cmd, t_env *env);

int						builtin_exit(char **cmd, t_data *data);

int						builtin_cd(char **cmd, t_env *env);

void					print_pwd(t_env *env, char *str);
void					swap_pwd_old(t_env *env);

int						ft_str_cmp(char *str1, char *str2);

int						home_dir_exec(char *cmd, t_env *env, char *str);
char					*find_directory(char *str, t_env *env);

int						change_directory(char *path, t_env *env, char *cmd);

void					add_var_exec(t_env *env, char *cmd, char *value);
int						ft_str_chr(char *str, char c);

/*redirections*/
int						redirection_input(t_cl_info *exec, t_parse *parse_list);
int						fd_open_file(char *file);
int						open_heredoc_file(char *heredoc_file, char *eof);
int						redirection_output(t_parse *parse_list);

int						create_pipes(t_data *data, t_cl_info *exec, int i);
void					child_exec(t_data *data, t_cl_info *exec, int i);

void					other_cmds_exec(t_data *data, t_cl_info *exec);
char					*get_executable_path(const char *cmd, const char *path);
char					**ft_split_ignore_spaces(const char *s, char c);
int						global_status(pid_t last_pid);

#endif