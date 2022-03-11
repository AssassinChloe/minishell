#include "minishell.h"


void	ft_printtype(t_list *elem)
{
	t_list	*tmp;
	t_cmd	*type;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp)
	{
		type = (t_cmd *)tmp->content;
		printf(" il y a %d argument dans la ligne de commande : \n", type->argc);
		while (i < type->argc)
		{
			printf("type %d : -%s-\n", type->type[i], type->av[i]);
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}

void	ft_printchain(t_list *elem)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp)
	{
		printf("token %d : -%s-\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
}