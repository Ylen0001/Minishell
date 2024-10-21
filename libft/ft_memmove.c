/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:57:50 by aberion           #+#    #+#             */
/*   Updated: 2023/11/13 13:50:26 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	const unsigned char	*s_end = s + n;
	unsigned char		*d_end;

	d = dest;
	if (d == s)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d_end = d + n;
		while (n--)
			*(--d_end) = *(--s_end);
	}
	return (dest);
}

/*
int	main(void) {
	char str[50] = "Bonjour tout le monde!";

	// Exemple de chevauchement,
		où nous déplaçons une partie de la chaîne en arrière
	ft_memmove(str + 8, str, 17);

	printf("str après ft_memmove: %s\n", str);

	return (0);
}
*/