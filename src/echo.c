/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/21 16:25:16 by ylenoel          ###   ########.fr       */
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

void	b_i_echo(char **cmd)
{
	size_t	i;
	
	i = 0;
	
	if(flag_is_ok(cmd[1]) == 1)
	{
		i = 1;
		while(cmd[i++])
			printf("%s", cmd[i]);
	}
	else
		while(cmd[i++])
			printf("%s\n", cmd[i]);
	return;
}