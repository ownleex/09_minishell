/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:23:05 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:08:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
int     main(void)
{
	t_list  *lst;
	t_list  *new_lst;
	t_list  *new_lst2;

	lst = ft_lstnew("third");
	new_lst = ft_lstnew("second");
	new_lst2 = ft_lstnew("first");
	ft_lstadd_front(&lst, new_lst);
	ft_lstadd_front(&lst, new_lst2);
	ft_printf("le dernier element est %s\n", (char *)ft_lstlast(lst)->content);
	return (0);
}
*/
