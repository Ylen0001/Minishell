/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/22 16:24:13 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str, t_data *data)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 1;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == ft_strlen(str))
		{
			data->flag_echo_trig = 1;
			return (1);
		}
	}
	return (0);
}

void	print_echo(t_data *data, char **charc, int index)
{
	while (charc[index])
	{
		printf("%s", charc[index++]);
		if (charc[index])
			printf(" ");
	}
	if (!data->flag_echo_trig)
		printf("\n");
	return ;
}

void	b_i_echo(t_data *data, char *cmd)
{
	char	**splitted;
	int		i;
	int		index;

	index = 0;
	splitted = ft_split_sa(cmd);
	if (splitted[1])
	{
		i = 1;
		while (splitted[i])
		{
			if (!check_option(splitted[i], data))
			{
				print_echo(data, splitted, ++index);
				break ;
			}
			i++;
			index++;
		}
	}
	free_charchar(splitted);
	return ;
}
