/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:00:00 by aberion           #+#    #+#             */
/*   Updated: 2024/09/03 13:21:14 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

long long	c_toll(const char *str)
{
	int				minus;
	u_int64_t result;
	int				i;
	size_t	checker;

	checker = 9223372036854775807;
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
	if(str[i] == '+' || str[i] == '-')
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return 2;
	}
	int j = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
		j++;
	}
	if ((j > 19) || (minus == 1 && result > INT64_MAX) 
	|| (minus == -1 && result > (u_int64_t)INT64_MAX + 1))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return 2;
	}
	return ((long long)(result *= minus));
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

int check_args_ex(char *cmd)
{
	char **splitted;
	
	splitted = ft_split(cmd, ' ');
	if (splitted[2])
		return 1;
	if (splitted[1])
		return 42;
	return 0;
}

void builtin_exit(t_data *s_data, char *cmd)
{
	long long dehors;

	
	if (check_args_ex(cmd) == 1)
	{
    	free_t_data(s_data);
		exit(1);
	}
	if (check_args_ex(cmd) == 42)
	{
		dehors = c_toll(cmd);
		free_t_data(s_data);
		exit(dehors);
	}
	dehors = s_data->exit_status;
    free_t_data(s_data);
	// ft_putstr_fd("exit", 2);
    exit(dehors);
}
