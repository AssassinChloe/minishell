#include "minishell.h"

void    ft_redirstd(t_redir *redir, int std)
{
	redir->fdsave = dup(std);
	if (redir->fdsave == -1)
		printf("error copie fd\n");
	if (dup2(redir->fd, std) == -1)
		printf("error redirection\n");
}

void ft_lowerstart(t_cmd *tmp, int i, t_redir *redir)
{
	if (tmp->type[i] == T_LOWER)
	{
		redir->fd = open(tmp->argv[i + 1], O_RDONLY);
		if (redir->fd == -1)
		{
			printf("error open\n");
			return ;
		}
	}
    ft_redirstd(redir, STDIN_FILENO);
}

void    ft_llowerstart(t_cmd *tmp, int i, t_redir *redir)
{
    char    *buffer;
	char	*delimiter;
	int 	j;

	j = 0;
	if (ft_isquote(tmp->argv[i + 1][0]) > 0)
		delimiter = ft_handle_quote(tmp->argv[i + 1], &j, 0);
	else
		delimiter = ft_strdup(tmp->argv[i + 1]);
	
	buffer = readline("heredoc> ");
	redir->fd = open(".heredoc", O_CREAT|O_RDWR|O_APPEND, 0666);
	if (redir->fd == -1)
	{
		printf("error open\n");
		return ;
	}
	while (buffer && ft_strcmp(buffer, delimiter) != 0)
	{
		if (j == 0 && has_dollar(buffer) > 0)
			buffer = ft_extract_var(buffer);
		write(redir->fd, buffer, ft_strlen(buffer));
		write(redir->fd, "\n", 2);
		free(buffer);
		buffer = readline("heredoc>");

	}
	free(buffer);
	free(delimiter);
	tmp->argv[i] = ft_strdup(".heredoc");
	free(tmp->argv[i + 1]);
	tmp->argv[i + 1] = NULL;
	ft_redirstd(redir, STDIN_FILENO);
}

void    ft_greaterstart(t_cmd *tmp, int i, t_redir *redir)
{
    redir->fd = open(tmp->argv[i + 1], O_RDWR|O_CREAT|O_TRUNC, 0666);
	if (redir->fd == -1)
	{
		printf("error open\n");
		return ;
	}
    ft_redirstd(redir, STDOUT_FILENO);
}
void    ft_ggreaterstart(t_cmd *tmp, int i, t_redir *redir)
{
    redir->fd = open(tmp->argv[i + 1], O_RDWR|O_CREAT|O_APPEND, 0666);
	if (redir->fd == -1)
	{
		printf("error open\n");
		return ;
	}
    ft_redirstd(redir, STDOUT_FILENO);
}