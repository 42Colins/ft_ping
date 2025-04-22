/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:03:53 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/30 18:14:17 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_words(char *str, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if ((index == 0 && str[index] != c))
			count++;
		if (index != 0 && (str[index - 1] == c
				&& str[index] != c && str[index] != '\0'))
			count++;
		index++;
	}
	return (count);
}

int	find_sep(char *str, char c, int index)
{
	if (index == 0 && str[index] != c)
		return (index);
	while (str[index] == c)
		index++;
	return (index);
}

int	word_size(char *str, char c, int index)
{
	int	pos;

	pos = 0;
	while (str[index] == c)
	{
		index++;
	}
	while (str[index] != c && str[index])
	{
		pos++;
		index++;
	}
	return (pos);
}

void	*free_all(char **str, int runner)
{
	int	index;

	index = 0;
	while (runner >= index)
	{
		free(str[runner]);
		runner--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	size_t	runner;
	int		words;
	size_t	index;
	int		size;

	runner = 0;
	index = 0;
	words = how_many_words(str, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	while ((int)runner < words)
	{
		index = find_sep(str, c, index);
		size = word_size(str, c, index);
		split[runner] = ft_substr(str, index, size);
		if (!split[runner])
			return (free_all(split, runner));
		index += size;
		runner++;
	}
	split[runner] = NULL;
	return (split);
}
