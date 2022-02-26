#include "minishell.h"

void ft_print_error()
{
    char	*log;
	char	*error;
	int		ret;
    int     fd;

    if ((fd = open(".log", O_RDONLY)) < 0)
        printf("error open\n"); 
	log = NULL;
	error = NULL;
	ret = get_next_line(fd, &log);
	if (ret >= 0)
	{
		error = ft_strdup(log);
		while (ret == 1)
		{
            if (error != NULL)
                error = ft_strjoin(error, "\n");
			free(log);
			log = NULL;
			ret = get_next_line(fd, &log);
			error = ft_strjoin(error, log);
		}
        if (ft_strlen(error) > 0)
        {
		    write(STDERR_FILENO, error, (ft_strlen(error) + 1));
            g_data.exit_value = 1;
        }
		free(error);  
	}
    free(log);
	log = NULL;
    close(fd);
    unlink(".log");
}