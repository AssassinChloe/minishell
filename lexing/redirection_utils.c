#include "minishell.h"

int end_redir_error(t_cmd *command)
{
	ft_endredir(command);
	g_data.exit_value = 1;
	close(g_data.check);
	return (1);
}