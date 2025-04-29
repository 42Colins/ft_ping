/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:45:16 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:40:12 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int		index;
	char				*array;

	if (!s || !f)
		return (NULL);
	array = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!array)
		return (NULL);
	index = 0;
	while (s[index])
	{
		array[index] = f(index, s[index]);
		index++;
	}
	array[index] = '\0';
	return (array);
}
