/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:40:16 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 15:43:53 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	real_print_export(t_data *s_data, int *i, int *j, int *check)
{
	while (s_data->vect_env->data[(*i)][(*j)])
	{
		if (s_data->vect_env->data[(*i)][(*j)] == '=')
		{
			(*check) = 1;
			printf("=\"");
		}
		else
			printf("%c", s_data->vect_env->data[(*i)][(*j)]);
		(*j)++;
	}
}

void	print_export(t_data *s_data)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (s_data->vect_env->data[i])
	{
		printf("export ");
		j = 0;
		real_print_export(s_data, &i, &j, &check);
		if (check == 1)
		{
			check = 0;
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	check_equal(t_data *s_data, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && ft_isspace(s[(i - 1)]))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			s_data->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
