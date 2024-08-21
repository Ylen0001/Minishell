/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:20 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/21 15:47:20 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_manager(char **cmd)
{
	if(ft_strcmp(cmd[0], "echo") == 0)
		b_i_echo(cmd);
	return;
}

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

// On va c