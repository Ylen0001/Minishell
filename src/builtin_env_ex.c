/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:00:00 by aberion           #+#    #+#             */
/*   Updated: 2024/08/30 17:20:42 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>


long long	c_toll(const char *str)
{
	int				minus;
	size_t	result;
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
		return 0;
	}
	int j = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
		j++;
	}
	if (j >= 19)
		return 0;
	if (result > checker && minus == 1)
		return 0;
	if (result > (checker + 1) && minus == -1)
		return 0;
	long long r_res = result * minus;
	return (r_res);
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
		return -1;
	if (splitted[1])
	{
		int i = 0;
		
	}
	
	return 0;
}

void builtin_exit(t_data *s_data, char *cmd)
{
    (void)cmd;
    free_t_data(s_data);
	// ft_putstr_fd("exit", 2);
    exit(s_data->exit_status);
}
