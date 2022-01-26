#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "libft/libft.h"

# define T_ERR 1
# define T_PIPE 2
# define T_CMD 3
# define T_FLAG 4
# define T_LOWER 5
# define T_GREATER 6
# define T_LLOWER 7
# define T_GGREATER 8
# define T_STRING 9

typedef struct		s_cmd
{
	char			**argv;
	int				argc;
	int				type;
	int				pip[2];
	int				fd_in;
	int				fd_out;
    int             order; // voir si besoin order ou si liste chainee
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_data // globale ?
{
	char	*line;
	t_cmd	*cmd_lst;
	char	**splited_line;
	char	**args;
	int		exit_value;
	int		nb_pipe;
    int     loop; // variable pour maintien de la boucle while
}		t_data;

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
int get_token_type(char *str);
char	*ft_extract_var(char *str);
int ft_isredir(char c);
int ft_isdoubleredir(char *str, int i);
char    *ft_handle_quote(char *str, int *i, int keepquote);
void	ft_freeparsing(char **str, t_list **chain);
int is_forbidden_char(char c);
int	ft_isvarphabet(char c);
#endif