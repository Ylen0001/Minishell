/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:23:37 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 08:50:20 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_plus_minus(const char *str, int *i, int *minus)
{
	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32))
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		(*i)++;
		(*minus) *= (-1);
	}
	if (str[*i] == '+' || str[*i] == '-')
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	return (0);
}

long long	c_toll(const char *str)
{
	int			minus;
	u_int64_t	result;
	int			i;
	int			j;

	j = 0;
	i = 0;
	result = 0;
	minus = 1;
	if (!str || skip_plus_minus(str, &i, &minus) == 2)
		return (2);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
		j++;
	}
	if ((j > 19) || (minus == 1 && result > INT64_MAX) || (minus == -1
			&& result > (u_int64_t)INT64_MAX + 1))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	return ((long long)(result *= minus));
}

void	builtin_env(t_data *s_data)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (i < s_data->vect_env->size)
	{
		j = 0;
		while (s_data->vect_env->data[i][j]
			&& s_data->vect_env->data[i][j] != '=')
			j++;
		if (s_data->vect_env->data[i][j] == '\0')
		{
			i++;
			continue ;
		}
		printf("%s\n", s_data->vect_env->data[i]);
		i++;
	}
}

int	check_splitted(char **splitted, int i, t_data *data)
{
	if (!splitted[1])
		return (3);
	if (splitted[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->too_many_args = 1;
		return (1);
	}
	if (splitted[1])
	{
		while (splitted[1][i])
		{
			if (ft_isdigit(splitted[1][i]) == 0 && splitted[1][i] != '+'
				&& splitted[1][i] != '-')
			{
				ft_putstr_fd("exit: numeric argument required\n", 2);
				return (2);
			}
			i++;
		}
		return (42);
	}
	return (0);
}

int	check_args_ex(char *cmd, t_data *data)
{
	char	**splitted;
	int		i;
	int		result;

	i = 0;
	splitted = ft_split_sa(cmd);
	if (!splitted)
		return (-1);
	result = check_splitted(splitted, i, data);
	free_charchar(splitted);
	if (result == 3)
		return (3);
	if (result == 1)
		return (1);
	if (result == 2)
		return (2);
	if (result == 42)
		return (42);
	return (0);
}
