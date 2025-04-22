/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:23:52 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 16:43:07 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		index;
	size_t	size;
	char	*array;

	index = 0;
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	size = size - start;
	if (size > len)
		size = len;
	array = malloc(sizeof(char) * (size) + 1);
	if (!array)
		return (NULL);
	if (len < size)
		return (ft_strdup(""));
	while ((size_t)index < size && s[start + index])
	{
		array[index] = s[start + index];
		index++;
	}
	array[index] = '\0';
	return (array);
}
