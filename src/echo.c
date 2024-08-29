/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/28 14:18:34 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		flag_is_ok(char *flag)
{
	size_t i;

	i = 1;
	if(flag[0] != '-')
		return (0);
	while(flag[i])
	{
		if(flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	b_i_echo(char *cmd)
{
	char 	**splited;
	int		newline;
	size_t	i;

	newline = 1;
	splited = ft_split(cmd, ' ');	
	i = 1;
	
	if(splited[i] && flag_is_ok(splited[i]) == 1)
	{
		newline = 0;
		i++;
	}
	while(splited[i])
	{	
		printf("%s", splited[i]);
		if (splited[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return;
}