/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:15:52 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:07:19 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printint(int nbr)
{
	int		ret;
	char	*str;

	str = ft_itoa(nbr);
	ret = ft_printstr(str);
	free(str);
	return (ret);
}
