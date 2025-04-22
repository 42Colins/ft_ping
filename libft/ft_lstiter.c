/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:35:06 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/27 14:19:50 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*array;
	t_list	*next_array;

	if (!lst || !f)
		return ;
	array = lst;
	while (array)
	{
		next_array = array->next;
		f(array->content);
		array = next_array;
	}
}
