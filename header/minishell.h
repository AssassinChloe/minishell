/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:07:55 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 23:01:30 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"

# include <sys/ioctl.h>

# define T_ERR 1
# define T_PIPE 2
# define T_CMD 3
# define T_VAR 4
# define T_LOWER 5
# define T_GREATER 6
# define T_LLOWER 7
# define T_GGREATER 8
# define T_STRING 9
# define T_BUILTIN 10
# define T_FILENAME 11

typedef struct s_gnl
{
	char	*log;
	int		fd;
	int		ret;
}	t_gnl;

typedef struct s_parse
{
	int		i;
	char	*tmp;
	t_list	*tokens;
	int		ret;
	int		pipe;
	int		multiple;
}	t_parse;

typedef struct s_redir
{
	int	fd;
	int	fdsave;
	int	type;
}	t_redir;

typedef struct s_split
{
	char			*str;
	int				token_nb;
}	t_split;

typedef struct s_cmd
{
	char			**av;
	int				argc;
	int				argc_init;
	int				*type;
	t_redir			*redir;
	int				redir_nb;
	int				env;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	t_list	*split;
	char	*log;
	int		token;
	char	**env_in_tab;
	t_env	*env;
	int		exit_value;
	int		nb_pipe;
	int		execution;
	int		loop;
	int		check;
}		t_data;

extern t_data	g_data;

int		is_forbidden_char(char c); // a supprimr ?
void	ft_execution_test(t_cmd *cmd); // a supprimer ?
void	ft_pipe(t_list *commandlist); // a supprimer ?

/* Parsing */
int		ft_isvarphabet(char c);
void	ft_parse(char *str);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_ispipe(char c);
int		ft_special(char c);
void	ft_printchain(t_list *elem);
void	ft_addone(t_list **tokens, char **tmp);
int		has_dollar(char *str);
char	*ft_extract_var(char *str, int quote, int start);
int		ft_isredir(char c);
int		ft_isdoubleredir(char *str, int i);
void	ft_concatquote(char *str, char **tmp, int *i);
char	*ft_handle_quote(char *str, int *i, int keepquote);
int		ft_parsetxt(char *str, t_parse *parse);
void	ft_freeparsing(t_parse **parse);
char	*is_forbidden_redir(t_parse *parse);
char	*ft_extract_pipe(char *str, t_parse *parse);
char	*extract_redir(char *str, t_parse *parse);
char	*ft_addquote(char *str);
char	*ft_remove_dollar(char *str, int start);
void	build_split_list(char *str);
void	ft_free_splitlist(t_list **splitlist);

/* Lexing */
int		get_token_type(char *str, int *multicmd);
void	ft_check_for_env(t_cmd *tokens);
int		ft_lexing(t_list **list);
void	ft_printtype(t_list *elem);
int		ft_divide_redirection(t_cmd *cmd);
int		ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist);
void	ft_free_commandlist(t_list **commandlist);
int		ft_lowerstart(t_cmd *tmp, int i, int j);
int		ft_llowerstart(t_cmd *tmp, int i, int j);
int		ft_greaterstart(t_cmd *tmp, int i, int j);
int		ft_ggreaterstart(t_cmd *tmp, int i, int j);
void	modif_arg(t_cmd **cmd);
void	modif_arg_heredoc(t_cmd **cmd, char *filename);
void	ft_write_heredoc(char **buffer, t_cmd *cmd, int j, int isquote);
int		open_heredoc(t_cmd *cmd, int i, int j);
void	ft_countredir(t_cmd *cmd);
int		ft_handleredir(int j, t_cmd *cmd, int *i);
void	ft_endredir(t_cmd *cmd);
void	ft_redirstd(t_redir *redir, int std);
int		ft_get_cmd_path(char **cmd);
int		ft_isbuiltin(char *str);
int		is_valid_cmd(t_cmd *cmd);
void	ft_error_check_cmd(t_cmd *cmd, int *ret);

/* Execution */
void	ft_closepipe(int **pip);
int		execute_command(t_list *commandlist);
void	exec_cmd(t_cmd *cmd);
int		ft_child(int **pip, int i, t_cmd *cmd);
void	ft_parent(int **pip);
void	ft_free_pipe(int **pip);
void	ft_open_pipes(int **pip);
void	if_redir(int **pip, t_cmd *cmd, int i);

/* General */
void	init_data(char **envp);
void	handle_sig(int sig);
void	init_signal(void);
int		minishell(void);
void	ft_print_error(void);
void	free_g_data(void);

/* Env */
void	destroy_var(t_env *var);
void	clear_list(t_env **list);
t_env	*record_var(char *key, char *value);
t_env	*get_env(char **envp);
char	**ft_split_env(char *s);
char	**ft_split_env_plus(char *s);
char	**free_tab2(char **tmp);
t_env	*search_var(char *str);
char	*get_env_value(char *str);
int		already_in_env(char *arg);
int		format_key_ok(char *str);
int		format_value_ok(char *str);
void	modify_shlvl_value(void);
void	change_env_value(char *key, char *newvalue, int int_value);
void	destroy_var_env(t_env *var);
void	free_env(void);
int		count_var_env(void);
char	**ft_env_in_tab(void);
int		print_table_string(char **table);
void	free_table_string(char **table);

/* Builtins */
int		ft_echo(char **args);
int		is_flag_n(char *arg);
int		ft_pwd(t_cmd cmd);
int		launch_builtin(t_cmd *cmd);
int		cd_too_many(void);
int		err_cd_home_unset(char *srcpath, char *destpath);
int		err_cd_oldpwd_unset(char *srcpath, char *destpath);
int		ft_cd(t_cmd cmd);
int		ft_env(void);
int		ft_atoi_exit(const char *str);
int		ft_exit(t_cmd cmd);
int		has_equal(char *str);
int		has_plus_equal(char *str);
char	**table_export_key(void);
char	**sort_table(char **table);
int		print_exp_list(void);
int		print_table_export(void);
int		ft_export(t_cmd cmd);
t_env	*find_last_env(void);
void	add_env_value(char *newkey, char *newvalue, int int_value);
int		ft_unset(char **arg);
void	del_first_env(void);
t_env	*get_prev(char *key);
int		check_format_exit(char *str);
int		ft_is_long_long(char *str);
char	*ft_strjoin_d(char *s1, char *s2);

#endif