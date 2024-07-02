/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:13:43 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:07:21 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printptr(void *ptr)
{
	unsigned long long	addr;
	int					ret;

	ret = 0;
	addr = (unsigned long long)ptr;
	if (addr == 0)
		ret += ft_printstr("(nil)");
	else
	{
		ret += ft_printstr("0x");
		ret += ft_printhex(addr, 'x');
	}
	return (ret);
}
