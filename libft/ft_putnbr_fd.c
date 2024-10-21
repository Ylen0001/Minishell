/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:13:49 by aberion           #+#    #+#             */
/*   Updated: 2023/11/20 18:09:44 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	char	*nb_str;

	if (!fd)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	else
	{
		i = 0;
		nb_str = ft_itoa(n);
		while (nb_str[i])
		{
			write(fd, &nb_str[i], 1);
			i++;
		}
	}
}
