/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:45:11 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:08:39 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
int     main(void)
{
	t_list  *lst;
	t_list  *new_lst;

	lst = ft_lstnew("second");
	new_lst = ft_lstnew("first");
	ft_lstadd_front(&lst, new_lst);
	printf("Le premier element est %s\n", (char *)lst->content);
	printf("Le deuxieme element est %s\n", (char *)lst->next->content);
	return (0);
}
*/
