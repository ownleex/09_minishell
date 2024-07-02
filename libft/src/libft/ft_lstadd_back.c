/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:34:54 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:08:37 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/*
int     main(void)
{
	t_list	*lst;
	t_list	*new_lst;

	lst = ft_lstnew("first");
	new_lst = ft_lstnew("second");
	ft_lstadd_back(&lst, new_lst);
	printf("le dernier element est %s\n", (char *)lst->next->content);
	return (0);
}
*/
