/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:20 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/22 16:42:23 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_manager(t_data *data, char **cmd)
{
	if(ft_strcmp(cmd[0], "echo") == 0)
		b_i_echo(cmd);
	if(ft_strcmp(cmd[0], "pwd") == 0)
		pwd(data);
	if(ft_strcmp(cmd[0], "cd") == 0)
		cd(data, cmd);
	return;
}
