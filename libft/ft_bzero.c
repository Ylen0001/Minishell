/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:02:35 by ylenoel           #+#    #+#             */
/*   Updated: 2023/11/10 13:48:23 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char *) s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
