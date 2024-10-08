/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:20 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/16 15:30:48 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/colors.h"

void	built_in_detector(t_data *data, char *cmd)
{
	size_t	i;

	i = 0;
	if(cmd == NULL)
		return;
	while(i < data->v_path->size)
	{
		if(ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0 
			|| ft_strncmp(cmd, "pwd", 5) == 0 || ft_strncmp(cmd, "export", 6) == 0
			|| ft_strncmp(cmd, "unset", 5) == 0 || ft_strncmp(cmd, "env", 3) == 0 || 
			ft_strncmp(cmd, "exit", 4) == 0)
				data->built_in = 1;
		i++;
	}
	// printf("cmd = %s\nbuilt_in = %zu\n", cmd, data->built_in);
	return;
}

void	built_in_manager(t_data *data, char *cmd)
{
	char	**splited_cmd;

	// dprintf(2, "cmd = %s\n", cmd);
	splited_cmd = ft_split(cmd, ' ');
	if(ft_strncmp(splited_cmd[0], "echo\0", 5) == 0)
		b_i_echo(data, cmd);
	else if(ft_strncmp(splited_cmd[0], "pwd\0", 4) == 0)
		b_i_pwd(data);
	else if(ft_strncmp(splited_cmd[0], "cd\0", 3) == 0)
		b_i_cd(data, cmd);
	else if(ft_strncmp(splited_cmd[0], "export", 6) == 0)
		builtin_export(data, cmd);
	else if(ft_strncmp(splited_cmd[0], "unset\0", 6) == 0)
		builtin_unset(data, cmd);
	else if(ft_strncmp(splited_cmd[0], "exit\0", 5) == 0)
		builtin_exit(data, cmd);
	else if(ft_strncmp(splited_cmd[0], "env\0", 4) == 0)
		builtin_env(data);
	data->i = 0;
	while(splited_cmd[data->i])
		free(splited_cmd[data->i++]);
	free(splited_cmd);
	// garbage_destructor(data);
	return;
}