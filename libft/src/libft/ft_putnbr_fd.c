/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:07:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:09:25 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
	}
	ft_putchar_fd((nbr % 10 + '0'), fd);
}

/*
int	main(void)
{
	ft_putnbr_fd(-1599655345, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
*/
