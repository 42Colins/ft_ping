/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:20:43 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/29 11:21:31 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewfree(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(content);
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*array;
	t_list	*next_array;

	if (!lst || !f || !del)
		return (NULL);
	array = ft_lstnewfree(f(lst -> content));
	if (!array)
		return (NULL);
	lst = lst -> next;
	while (lst)
	{
		next_array = ft_lstnewfree(f(lst -> content));
		if (!next_array)
		{
			ft_lstclear(&array, (del));
			return (NULL);
		}
		ft_lstadd_back(&array, next_array);
		lst = lst -> next;
	}
	return (array);
}
