/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:53:52 by cprojean          #+#    #+#             */
/*   Updated: 2025/05/05 09:32:41 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SIZE_MAX 2147483647

void	*ft_calloc(size_t count, size_t size)
{
	char	*calloc;
	size_t	total;

	total = size * count;
	if (count != 0 && (SIZE_MAX / count) < size)
		return (NULL);
	calloc = malloc(total);
	if (!calloc)
		return (0);
	ft_bzero(calloc, total);
	return (calloc);
}
