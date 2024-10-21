/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:28:57 by aberion           #+#    #+#             */
/*   Updated: 2023/11/13 13:50:55 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void) {
	// Test de la fonction isalpha
	char ch;

	printf("Entrez un caractère : ");
	scanf("%c", &ch);

	if (ft_isalpha(ch)) {
		printf("'%c' est un caractère alphabétique.\n", ch);
	} else {
		printf("'%c' n'est pas un caractère alphabétique.\n", ch);
	}

	return (0);
}
*/