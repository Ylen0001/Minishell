/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:34:09 by aberion           #+#    #+#             */
/*   Updated: 2023/11/16 20:09:46 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_l;
	size_t	src_l;
	size_t	i;
	size_t	j;

	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	i = 0;
	j = dest_l;
	if (size <= dest_l)
		return (src_l + size);
	while ((j < size - 1) && (src[i] != '\0'))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	if (dest_l < size)
		dest[j] = '\0';
	return (dest_l + src_l);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char	dest[15] = "rrrrrrrrrrrrrrr";
	char	dest2[15] = "rrrrrrrrrrrrrrr";
	char	src[] = "lorem ipsum dolor sit amet";
	size_t	result;
	size_t	result2;

	result = ft_strlcat(dest, src, 5);
	result2 = strlcat(dest, src, 5);
	printf("Concatenated String: '%s'\n", dest);
	printf("Total Length: %zu\n", result);
	printf("Concatenated String: '%s'\n", dest2);
	printf("Total Length: %zu\n", result2);
	return (0);
}
*/
