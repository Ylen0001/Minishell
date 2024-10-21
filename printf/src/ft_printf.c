/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:31:02 by aberion           #+#    #+#             */
/*   Updated: 2024/03/04 13:20:54 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_norminette_nitro_killer(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'd')
		len += ft_print_int(va_arg(args, int));
	else if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 'p')
		len += ft_print_hex_p((unsigned long)va_arg(args, void *));
	else if (format == 'i')
		len += ft_print_int(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_uint(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	process_format(const char *format, va_list args)
{
	int	len;

	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (-1);
			len += ft_norminette_nitro_killer(args, *format);
			format++;
		}
		else
		{
			len += ft_putchar(*format++);
		}
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bigfat_len;

	bigfat_len = 0;
	va_start(args, format);
	if (format == NULL)
	{
		va_end(args);
		return (-1);
	}
	bigfat_len = process_format(format, args);
	va_end(args);
	return (bigfat_len);
}

/*int	main(void)
{
	// int stock;
	// sint *ptr;
	// int a = 2;
	// stock = printf( "%+d\t%+d\n   ", 786, -786 );
	// printf("%d\n",stock);
	//printf("%d\n", printf());
	//    ft_printf("%p", &ptr);
	//printf("%d", ft_printf());
	 int *null_pointer = NULL; 
    printf("Test printf with NULL pointer: %d\n", 
	printf("%p\n", null_pointer));
    printf("Test ft_printf with NULL pointer: %d\n",
	 ft_printf("%p\n", null_pointer));
    printf("Test printf with empty string: %d\n", printf(""));
    printf("Test ft_printf with empty string: %d\n", ft_printf(""));
	printf("Test printf with 0: %d\n", printf(0));
    printf("Test ft_printf with 0: %d\n", ft_printf(0));
    return 0;
}*/