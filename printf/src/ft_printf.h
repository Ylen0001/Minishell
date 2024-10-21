/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:39:15 by aberion           #+#    #+#             */
/*   Updated: 2024/02/29 08:08:13 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

// Prototype de la fonction ft_printf
int	ft_printf(const char *format, ...);

// Prototypes des fonctions auxiliaires
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_print_int(int n);
int	ft_print_uint(unsigned int n);
int	ft_print_hex_p(unsigned long nbr);
int	ft_print_hex(unsigned int n, char specifier);
int	ft_print_pointer(void *ptr);

#endif
