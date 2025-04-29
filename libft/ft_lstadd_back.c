/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:05:24 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/25 17:58:02 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*array;

	if (!lst || !new)
		return ;
	array = *lst;
	if (array == NULL)
		*lst = new;
	else
	{
		array = ft_lstlast(*lst);
		array->next = new;
	}
}
