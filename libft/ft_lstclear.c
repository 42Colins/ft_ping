/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:27:24 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/26 18:29:14 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*array;
	t_list	*next_array;

	if (!lst || !del)
		return ;
	array = *lst;
	while (array)
	{
		next_array = array->next;
		del(array->content);
		free(array);
		array = next_array;
	}
	*lst = NULL;
	return ;
}
