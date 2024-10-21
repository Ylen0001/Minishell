/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:54:10 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 15:44:37 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_first_digit(t_data *s_data, char *to_check)
{
	if (ft_isdigit(to_check[0]) != 0)
	{
		s_data->exit_status = 1;
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	check_if_only_digits(t_data *s_data, char *clean)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (clean[i])
	{
		if (ft_isdigit(clean[i]) != 0)
			checker++;
		i++;
	}
	if (checker == i)
	{
		s_data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	check_and_replace_variable(t_vectstr *vect_env, char *clean, char *to_check)
{
	int	i;

	i = 0;
	while (vect_env->data[i])
	{
		if (ft_strnstr(vect_env->data[i], clean, ft_strlen(clean)) != 0)
		{
			replace_variable(vect_env, to_check, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	clean_and_check_variable(t_data *s_data, char *to_check, char *clean)
{
	int	i;

	i = 0;
	while (to_check[i] && to_check[i] != '=')
	{
		if ((ft_isalnum(to_check[i]) == 0 && to_check[i] != '_'))
		{
			s_data->exit_status = 1;
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (1);
		}
		clean[i] = to_check[i];
		i++;
	}
	return (0);
}

int	check_presence(t_data *s_data, char *to_check)
{
	char	clean[BUFFER_SIZE2];

	ft_memset(clean, '\0', BUFFER_SIZE2);
	if (check_first_digit(s_data, to_check))
		return (1);
	if (clean_and_check_variable(s_data, to_check, clean))
		return (1);
	if (check_if_only_digits(s_data, clean))
		return (1);
	if (check_and_replace_variable(s_data->vect_env, clean, to_check))
		return (1);
	return (0);
}

// int	check_presence(t_data *s_data, char *to_check)
// {
// 	int		i;
// 	char	clean[BUFFER_SIZE2];
// 	int		checker;

// 	ft_memset(clean, '\0', BUFFER_SIZE2);
// 	i = 0;
// 	if (ft_isdigit(to_check[0]) != 0)
// 	{
// 		s_data->exit_status = 1;
// 		ft_putstr_fd("invalid variable\n", 2);
// 		return (1);
// 	}
// 	while (to_check[i] && to_check[i] != '=')
// 	{
// 		if ((ft_isalnum(to_check[i]) == 0 && to_check[i] != '_'))
// 		{
// 			s_data->exit_status = 1;
// 			ft_putstr_fd("invalid variable\n", 2);
// 			return (1);
// 		}
// 		clean[i] = to_check[i];
// 		i++;
// 	}
// 	i = 0;
// 	checker = 0;
// 	while (clean[i])
// 	{
// 		if (ft_isdigit(clean[i]) != 0)
// 			checker++;
// 		i++;
// 	}
// 	if (checker == i)
// 	{
// 		s_data->exit_status = 1;
// 		return (1);
// 	}
// 	i = 0;
// 	while (s_data->vect_env->data[i])
// 	{
// 		if (ft_strnstr(s_data->vect_env->data[i], clean, ft_strlen(clean)) != 0)
// 		{
// 			replace_variable(s_data->vect_env, to_check, i);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
