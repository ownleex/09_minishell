/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:39:43 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:09:37 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
void	minuscule(unsigned int i, char *c)
{
        *c = *c + 32;
}

int	main()
{
	char	str[] = "EXEMPLE";

	printf("avant striteri : %s\n", str);
	ft_striteri(str, minuscule);
	printf("apres striteri : %s\n", str);
	return (0);
}
*/
