/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:47:52 by aberion           #+#    #+#             */
/*   Updated: 2024/09/30 13:52:38 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_in_env(t_data *s_data, char *check_var)
{
	int	i;

	i = 0;
	if (!check_var)
		return ;
	while (s_data->vect_env->data[i])
	{
		if (ft_strnstr(s_data->vect_env->data[i], check_var,
				ft_strlen(check_var)) != NULL
			&& (s_data->vect_env->data[i][ft_strlen(check_var)] == '='
			|| s_data->vect_env->data[i][ft_strlen(check_var)] == '\0'))
		{
			free(s_data->vect_env->data[i]);
			while (s_data->vect_env->data[i])
			{
				s_data->vect_env->data[i] = s_data->vect_env->data[i + 1];
				i++;
			}
			s_data->vect_env->data[i] = NULL;
			s_data->vect_env->size--;
			return ;
		}
		i++;
	}
}

void	skip_spaces_co_unset(char *str, int *it)
{
	while (str[*it] && !ft_isspace(str[*it]))
		(*it)++;
	while (str[*it] && ft_isspace(str[*it]))
		(*it)++;
}

void	builtin_unset(t_data *data, char *cmd)
{
	int		i;
	int		j;
	char	to_check[BUFFER_SIZE2];

	ft_memset(to_check, '\0', BUFFER_SIZE2);
	i = 0;
	j = 0;
	skip_spaces_co_unset(cmd, &i);
	while (cmd[i])
	{
		ft_memset(to_check, '\0', BUFFER_SIZE2);
		j = 0;
		while (cmd[i] && cmd[i] != ' ')
		{
			to_check[j] = cmd[i];
			j++;
			i++;
		}
		check_in_env(data, to_check);
		if (!cmd[i])
			return ;
		i++;
	}
}
