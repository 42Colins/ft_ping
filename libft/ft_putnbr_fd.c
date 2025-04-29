/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:17:34 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/17 17:27:39 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_next_putnbr_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	char	dash;

	dash = '-';
	if (n == -2147483648)
	{
		write(fd, &dash, 1);
		ft_putnbr_fd(214748364, fd);
		write(fd, "8", 1);
	}
	else if (n < 0)
	{
		write(fd, &dash, 1);
		ft_putnbr_fd(n * -1, fd);
	}
	ft_next_putnbr_fd(n, fd);
}

void	ft_next_putnbr_fd(int n, int fd)
{
	char	mod;

	if (n >= 10)
	{
		mod = (n % 10) + 48;
		n = n / 10;
		ft_putnbr_fd(n, fd);
		write(fd, &mod, 1);
	}
	else if ((n >= 0) && (n < 10))
	{
		mod = (n % 10) + 48;
		write(fd, &mod, 1);
	}
}
