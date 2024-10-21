/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:31:55 by aberion           #+#    #+#             */
/*   Updated: 2024/06/25 15:32:54 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	char	*newptr;

	if (ptr == 0)
		return (malloc(newsize));
	if (newsize <= oldsize)
		return (ptr);
	newptr = malloc(newsize);
	if (newptr)
	{
		ft_memcpy(newptr, ptr, oldsize);
		free(ptr);
	}
	return (newptr);
}
