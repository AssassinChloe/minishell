/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:07:55 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/31 16:12:54 by cassassi         ###   ########.fr       */
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

typedef struct 		s_redir
{
	int	fd;
	int	fdsave;
	int	type;
}	t_redir;

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				*type;
	t_redir			*redir;
	int				redir_nb;
	int				pip[2];
	int				fd_in;int jt;
    int             order; // voir si besoin order ou si liste chainee
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_env //ajout
{
	char			*key;
	char			*value;
	struct s_env	*next;
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
    int     loop; // variable pour maintien de la boucle while
}		t_data;

extern t_data	g_data;

int	ft_isvarphabet(char c);
void    ft_parse(char *str);
int ft_isspace(char c);
int ft_isquote(char c);
int ft_issimplequote(char c);
int ft_isdoublequote(char c);
int ft_ispipe(char c);
void    ft_printchain(t_list *elem);
void    ft_addone(t_list **tokens, char **tmp);
int	has_dollar(char *str);
int	ft_strcmp(char *s1, char *s2);
int get_token_type(char *str, int *multicmd);
char	*ft_extract_var(char *str);
int ft_isredir(char c);
int ft_isdoubleredir(char *str, int i);
char    *ft_handle_quote(char *str, int *i, int keepquote);
void	ft_freeparsing(char **str, t_list **chain);
int is_forbidden_char(char c);
int ft_lexing(t_list *list);
void    ft_printtype(t_list *elem);
void	ft_execution_test(t_cmd *cmd);
void	ft_divide_redirection(t_list *commandlist);
void    ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist);
void    ft_free_commandlist(t_list **commandlist);
void	ft_lowerstart(t_cmd *tmp, int i, int j);
void    ft_llowerstart(t_cmd *tmp, int i, int j);
void    ft_greaterstart(t_cmd *tmp, int i, int j);
void    ft_ggreaterstart(t_cmd *tmp, int i, int j);
void	modif_arg(t_cmd **cmd);
int ft_countredir(t_cmd *cmd);

int	ft_env(void);
void	destroy_var(t_env *var);
void	clear_list(t_env **list);
t_env	*record_var(char *key, char *value);
t_env	*get_env(char **envp);
char **ft_split_env(char *s);
char    **free_tab2(char **tmp);
void	init_data(char **envp);
void    handle_sig(int sig);
void	init_signal();
int minishell();
int	ft_echo(char **args);
int		ft_pwd(void);
int	launch__builtin(t_cmd *cmd);

#endif
