/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:01:25 by aberion           #+#    #+#             */
/*   Updated: 2023/11/20 19:39:00 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neww)
{
	t_list	*back;

	if (!neww)
		return ;
	if (lst)
	{
		if (*lst)
		{
			back = ft_lstlast(*lst);
			if (!back)
				return ;
			back->next = neww;
		}
		else
			*lst = neww;
	}
}
