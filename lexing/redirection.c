#include "minishell.h"

void    ft_redirstd(t_redir *redir, int std)
{
	redir->fdsave = dup(std);
	if (redir->fdsave == -1)
		printf("error copie fd\n");
	if (dup2(redir->fd, std) == -1)
		printf("error redirection\n");
}

void modif_arg(t_cmd **cmd)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while ((*cmd)->argv[j] && ((*cmd)->type[j] < T_LOWER || (*cmd)->type[j] > T_GGREATER))
	{
		j++;
		i++;
	}
	free((*cmd)->argv[j]);
	(*cmd)->argv[j] = NULL;
	free((*cmd)->argv[j + 1]);
	(*cmd)->argv[j + 1] = NULL;
	j = j + 2;
	
	while ((*cmd)->argv[j])
	{
		(*cmd)->argv[i] = ft_strdup((*cmd)->argv[j]);
		(*cmd)->type[i] = (*cmd)->type[j];
		j++;
		i++;
	}
	while ((*cmd)->argv[i])
	{
		free((*cmd)->argv[i]);
		(*cmd)->argv[i] = NULL;
		(*cmd)->type[i] = 0;
		i++;
	}
	(*cmd)->argc = (*cmd)->argc - 2;
	return ;	
}

void modif_arg_heredoc(t_cmd **cmd, char *filename)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while ((*cmd)->argv[j] && ((*cmd)->type[j] < T_LOWER || (*cmd)->type[j] > T_GGREATER))
	{
		j++;
		i++;
	}
	free((*cmd)->argv[j]);
	(*cmd)->argv[i] = ft_strdup(filename);
	(*cmd)->type[i] = T_FILENAME;
	i++;
	free((*cmd)->argv[j + 1]);
	(*cmd)->argv[j + 1] = NULL;
	(*cmd)->type[i] = 0;
	j = j + 2;
		while ((*cmd)->argv[j])
	{
		(*cmd)->argv[i] = ft_strdup((*cmd)->argv[j]);
		(*cmd)->type[i] = (*cmd)->type[j];
		j++;
		i++;
	}
	while ((*cmd)->argv[i])
	{
		free((*cmd)->argv[i]);
		(*cmd)->argv[i] = NULL;
		(*cmd)->type[i] = 0;
		i++;
	}
	(*cmd)->argc = (*cmd)->argc - 2;
	return ;	
}
void ft_lowerstart(t_cmd *cmd, int i, int j)
{
	if (cmd->type[i] == T_LOWER)
	{
		cmd->redir[j].fd = open(cmd->argv[i + 1], O_RDONLY);
		if (cmd->redir[j].fd == -1)
		{
			printf("error open\n");
			return ;
		}
	}
	modif_arg(&cmd);
    ft_redirstd(&cmd->redir[j], STDIN_FILENO);

}

void    ft_llowerstart(t_cmd *cmd, int i, int j)
{
    char    *buffer;
	char	*delimiter;
	
	if (ft_isquote(cmd->argv[i + 1][0]) > 0)
		delimiter = ft_handle_quote(cmd->argv[i + 1], &j, 0);
	else
		delimiter = ft_strdup(cmd->argv[i + 1]);
	
	buffer = readline("heredoc> ");
	cmd->redir[j].fd = open(".heredoc", O_CREAT|O_RDWR|O_APPEND, 0650);
	if (cmd->redir->fd == -1)
	{
		printf("error open\n");
		return ;
	}
	while (buffer && ft_strcmp(buffer, delimiter) != 0)
	{
		if (has_dollar(buffer) > 0)
			buffer = ft_extract_var(buffer);
		write(cmd->redir[j].fd, buffer, ft_strlen(buffer));
		write(cmd->redir[j].fd, "\n", 2);
		free(buffer);
		buffer = readline("heredoc>");

	}
	free(buffer);
	free(delimiter);
	modif_arg_heredoc(&cmd, ".heredoc");
	ft_redirstd(&cmd->redir[j], STDIN_FILENO);
}

void    ft_greaterstart(t_cmd *cmd, int i, int j)
{
    cmd->redir[j].fd = open(cmd->argv[i + 1], O_RDWR|O_CREAT|O_TRUNC, 0650);
	if (cmd->redir[j].fd == -1)
	{
		printf("error open\n");
		return ;
	}
	modif_arg(&cmd);
    ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
}
void    ft_ggreaterstart(t_cmd *cmd, int i, int j)
{
    cmd->redir[j].fd = open(cmd->argv[i + 1], O_RDWR|O_CREAT|O_APPEND, 0650);
	if (cmd->redir[j].fd == -1)
	{
		printf("error open\n");
		return ;
	}
	modif_arg(&cmd);
    ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
}