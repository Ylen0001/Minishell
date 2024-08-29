/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:00:00 by aberion           #+#    #+#             */
/*   Updated: 2024/08/29 14:59:29 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>


long long	c_toll(const char *str)
{
	int				minus;
	unsigned int	result;
	int				i;

	i = 0;
	result = 0;
	minus = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		minus *= (-1);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result *= minus);
}

void builtin_env(t_data *s_data)
{
    size_t i = 0;
    while (i < s_data->vect_env->size)
    {
        printf("%s\n", s_data->vect_env->data[i]);
        i++;
    }
}

void builtin_exit(t_data *s_data, char *cmd)
{
    (void)cmd;
    free_t_data(s_data);
    exit(EXIT_SUCCESS);
}
