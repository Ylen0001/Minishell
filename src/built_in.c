/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:20 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/28 13:20:40 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_detector(t_data *data, char *cmd)
{
	size_t	i;

	i = 0;
	while(i < data->v_path->size)
	{
		// printf("cmd = %s\n", cmd);
		if(ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0 
			|| ft_strcmp(cmd, "pwd") == 0)
				data->built_in = 1;
		i++;
	}
	return;
}

void	built_in_manager(t_data *data, char *cmd)
{
	if(ft_strncmp(cmd, "echo", 4) == 0)
		b_i_echo(cmd);
	if(ft_strcmp(cmd, "pwd") == 0)
		b_i_pwd(data);
	if(ft_strncmp(cmd, "cd", 2) == 0)
		b_i_cd(data, cmd);
	return;
}
