/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:20 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/29 14:31:22 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_detector(t_data *data, char *cmd)
{
	size_t	i;

	i = 0;
	if(cmd == NULL)
	{
		data->built_in = 0;
		return;
	}
	// printf("cmd = %s\n", cmd);
	while(i < data->v_path->size)
	{
		if(ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0 
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strncmp(cmd, "export", 6) == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0
			|| ft_strcmp(cmd, "env") == 0)
				data->built_in = 1;
		i++;
	}
	return;
}

void	built_in_manager(t_data *data, char *cmd)
{
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, ' ');
	if(ft_strncmp(splited_cmd[0], "echo\0", 5) == 0)
		b_i_echo(cmd);
	if(ft_strncmp(splited_cmd[0], "pwd\0", 4) == 0)
		b_i_pwd(data);
	if(ft_strncmp(splited_cmd[0], "cd\0", 3) == 0)
		b_i_cd(data, cmd);
	if(ft_strncmp(splited_cmd[0], "export", 6) == 0)
		builtin_export(data, cmd);
	if(ft_strncmp(splited_cmd[0], "unset\0", 6) == 0)
		builtin_unset(data, cmd);
	if(ft_strncmp(splited_cmd[0], "exit\0", 5) == 0)
		builtin_exit(data, cmd);
	if(ft_strncmp(splited_cmd[0], "env\0", 4) == 0)
		builtin_env(data);

	return;
}
