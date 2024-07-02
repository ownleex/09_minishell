/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:49:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:09:03 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nouveau;

	nouveau = malloc(sizeof(t_list));
	if (!nouveau)
		return (NULL);
	nouveau->content = content;
	nouveau->next = NULL;
	return (nouveau);
}

/*
int	main(void)
{
	char	*str;
	t_list	*list;

	str = "bonjour";
	list = ft_lstnew(str);
	printf("%s\n", (char *)list->content);
	return (0);
}
*/
