/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:51:10 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:38:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		runner;
	char	character;

	character = c;
	runner = 0;
	while (s[runner])
	{
		if (s[runner] == character)
			return ((char *)&s[runner]);
		runner++;
	}
	if (character == '\0')
		return ((char *)&s[runner]);
	return (0);
}
