/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/27 16:53:34 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		flag_is_ok(char *flag)
{
	size_t i;

	i = 1;
	if(flag[0] != '-')
		return (0);
	while(flag[i++])
	{
		if(flag[i] != 'n')
			return (0);
	}
	return (1);
}

void	b_i_echo(char *cmd)
{
	char **splited;
	size_t	i;

	splited = ft_split(cmd, ' ');	
	i = 1;
	
	if(flag_is_ok(splited[i]) == 1)
	{
		i++;
		while(splited[i] && splited[i] != NULL)
		{
			printf("%s", splited[i]);
			i++;
		}
	}
	else
	{
		while(splited[i] && splited[i] != NULL)
		{	
			printf("%s\n", splited[i]);
			i++;
		}
	}
	return;
}