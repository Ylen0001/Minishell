/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:26:12 by aberion           #+#    #+#             */
/*   Updated: 2023/11/14 16:41:43 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	bigfat_size;

	bigfat_size = nmemb * size;
	if (nmemb != 0 && size != 0 && bigfat_size / nmemb != size)
		return (NULL);
	p = malloc(bigfat_size);
	if (p)
		ft_bzero(p, bigfat_size);
	return (p);
}
