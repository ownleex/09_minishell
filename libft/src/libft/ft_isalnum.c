/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:53:31 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:08:23 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}

/*
int	main(void)
{
	int	c;

	c = ',';
	if (ft_isalnum(c))
		printf("Le caractere est un chiffre ou une lettre\n");
	else
		printf("Le caractere n'est ni un chiffre ni une lettre\n");
	return (0);
}
*/
