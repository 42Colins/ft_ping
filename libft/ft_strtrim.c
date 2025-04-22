/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:08:31 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/30 18:10:48 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_error_case(void)
{
	char	*array;

	array = malloc(sizeof(char) * 1);
	if (!array)
		return (NULL);
	array[0] = '\0';
	return (array);
}

int	ft_is_sep(char s1, const char *set)
{
	size_t	runner;

	runner = 0;
	while (set[runner])
	{
		if (set[runner] == s1)
			return (1);
		runner++;
	}
	return (0);
}

int	ft_trim_this(const char *s1, const char *set, int index, int size)
{
	if (index == size)
	{
		if (index != 0)
			index -= 1;
		while (s1[index] && ft_is_sep(s1[index], set) == 1)
		{
			index--;
		}
		index++;
	}
	else
	{
		while (s1[index] && ft_is_sep(s1[index], set) == 1)
		{
			index++;
		}
	}
	return (index);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	index;
	size_t	size;
	int		count;
	int		second;

	if (!(s1 && set))
		return (NULL);
	size = ft_strlen(s1);
	index = 0;
	count = ft_trim_this(s1, set, index, size);
	second = ft_trim_this(s1, set, size, size);
	size = size - ((size - second) + count);
	if (size == 0)
		return (ft_error_case());
	return (ft_substr(s1, count, size));
}
