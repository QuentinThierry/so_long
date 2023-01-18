/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:14:09 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/18 19:34:07 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->content = content;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	ft_lstadd_back(t_list **lst, t_list *elem)
{
	if (lst && (*lst))
		ft_lstlast(*lst)->next = elem;
	else
		*lst = elem;
}


void	free_list(t_list **lst)
{
	t_list	*cpy;

	if (!lst)
		return ;
	while (*lst)
	{
		cpy = *lst;
		*lst = (*lst)->next;
		free(cpy->content);
		free(cpy);
	}
}
