/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:25:27 by aberion           #+#    #+#             */
/*   Updated: 2023/11/13 17:51:01 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = 0;
	while (src[i] != '\0')
	{
		l++;
		i++;
	}
	if (size == 0)
		return (l);
	i = 0;
	while ((src[i] != '\0') && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (l);
}
/*
int	main(void) {
	char src[] = "Copier cette chaîne";
	char dest[10];

	size_t copied = ft_strlcpy(dest, src, sizeof(dest));

	printf("dest: '%s', octets copiés: %zu\n", dest, copied);

	return (0);
}
*/