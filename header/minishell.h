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

# define T_ERR 1
# define T_PIPE 2
# define T_CMD 3
# define T_FLAG 4
# define T_LOWER 5
# define T_GREATER 6
# define T_LLOWER 7
# define T_GGREATER 8
# define T_STRING 9
# define T_BUILTIN 10
# define T_FILENAME 11

typedef struct s_redir
{
	int	fd;
	int	fdsave;
	int	type;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	int				argc;
	int				argc_init;
	int				*type;
	t_redir			*redir;
	int				redir_nb;
	int				order; // voir si besoin order ou si liste chainee
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_env //ajout
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data // globale ?
{
	char	*line;
	t_cmd	*cmd_lst;
	char	**splited_line;
	char	**args;
	t_env	*env;
	int		exit_value;
	int		nb_pipe;
	int		execution; // pour dire si on est en cours d'execution ou non
	int		loop; // variable pour maintien de la boucle while
}		t_data;

extern t_data	g_data;

int		ft_isvarphabet(char c);
void	ft_parse(char *str);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_ispipe(char c);
int		ft_special(char c);
void	ft_printchain(t_list *elem);
void	ft_addone(t_list **tokens, char **tmp);
int		has_dollar(char *str);
int		get_token_type(char *str, int *multicmd);
char	*ft_extract_var(char *str);
int		ft_isredir(char c);
int		ft_isdoubleredir(char *str, int i);
void	ft_concatquote(char *str, char **tmp, int *i);
char	*ft_handle_quote(char *str, int *i, int keepquote);
int		ft_parsetxt(char *str, int *i, char **tmp, int *multiple);
void	ft_freeparsing(char **str, t_list **chain);
int		is_forbidden_char(char c);
int		ft_lexing(t_list **list);
void	ft_printtype(t_list *elem);
void	ft_execution_test(t_cmd *cmd);
void	ft_divide_redirection(t_list *commandlist);
void	ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist);
void	ft_free_commandlist(t_list **commandlist);
void	ft_lowerstart(t_cmd *tmp, int i, int j);
void	ft_llowerstart(t_cmd *tmp, int i, int j);
void	ft_write_heredoc(char **buffer, t_cmd *cmd, int j);
void	ft_greaterstart(t_cmd *tmp, int i, int j);
void	ft_ggreaterstart(t_cmd *tmp, int i, int j);
void	modif_arg(t_cmd **cmd);
void	modif_arg_heredoc(t_cmd **cmd, char *filename);
int		ft_countredir(t_cmd *cmd);
void	ft_handleredir(int j, t_cmd *cmd, int *i);
void	ft_pipe(t_list *commandlist);
void	ft_closepipe(int **pip, int i);
void	ft_closepipe_end(int **pip, int i);
void	ft_endredir(t_cmd *cmd);
void	ft_redirstd(t_redir *redir, int std);
char	*is_forbidden_redir(int *i, int *multiple);
char	*ft_extract_pipe(char *str, int *i, int *multiple);
char	*extract_redir(char *str, int *i, int *multiple);
void	ft_get_cmd_path(t_cmd *cmd);
void	execute_command(t_list *commandlist);
void	exec_cmd(char **cmd);
int	ft_isbuiltin(char *str);
void	ft_child(int **pip, int i, t_list *cmdlist, t_cmd *cmd);
void	ft_parent(int **pip, int i);
void	ft_free_pipe(int **pip);
void	ft_open_pipes(int **pip);

void	destroy_var(t_env *var);
void	clear_list(t_env **list);
t_env	*record_var(char *key, char *value);
t_env	*get_env(char **envp);
char	**ft_split_env(char *s);
char **ft_split_env_plus(char *s);
char	**free_tab2(char **tmp);
void	init_data(char **envp);
void	handle_sig(int sig);
void	init_signal(void);
int		minishell(void);
int		ft_echo(char **args);
int		ft_pwd(void);
int		launch_builtin(t_cmd *cmd);
t_env	*search_var(char *str);
char	*get_env_value(char *str);
int		ft_cd(t_cmd cmd);
int		ft_env(t_cmd cmd);
int		ft_atoi_exit(const char *str);
int		ft_exit(t_cmd cmd);
int		already_in_env(char *arg);
int		format_key_ok(char *str);
int		has_equal(char *str);
int		print_exp_list(void);
int		ft_export(t_cmd cmd);
t_env	*find_last_env(void);
void	add_env_value(char *newkey, char *newvalue);
int	is_flag_n(char *arg);
#endif
