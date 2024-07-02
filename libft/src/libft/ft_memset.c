/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:56:00 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:09:18 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char) c;
		i++;
	}
	return (b);
}

/*
int	main(void)
{
	char	str[] = "bla bla bla";

	printf("Avant ft_memset : %s\n", str);
	ft_memset(str, 'a', 4);
	printf("Apres ft_memset : %s\n", str);

	return (0);
}
*/
