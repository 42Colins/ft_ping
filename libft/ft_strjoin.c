/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:52:31 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:39:53 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		sizearray;
	int		sizestring;
	int		runner;
	char	*array;

	runner = 0;
	sizearray = ft_strlen(s1);
	sizestring = ft_strlen(s2);
	array = malloc(sizeof(char) * (sizearray + sizestring) + 1);
	if (!array)
		return (NULL);
	while (runner < sizearray)
	{
		array[runner] = s1[runner];
		runner++;
	}
	runner = 0;
	while (runner < sizestring)
	{
		array[runner + sizearray] = s2[runner];
		runner++;
	}
	array[runner + sizearray] = '\0';
	return (array);
}
