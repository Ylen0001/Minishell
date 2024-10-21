/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:00:00 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 15:51:56 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>

void	free_before_exit(t_data *s_data)
{
	free_charchar(s_data->input_list);
	free_t_data(s_data, 0);
	garbage_destructor(s_data);
	close(s_data->old_fdin);
	close(s_data->old_fdout);
}

void	handle_exit(t_data *s_data, long long dehors, int result)
{
	free(s_data->pids);
	if (result == 1 || result == 2 || result == 3 || result == 42)
	{
		free_before_exit(s_data);
		printf("exit\n");
	}
	if (result == 1)
		exit(1);
	if (result == 2)
		exit(2);
	if (result == 3)
		exit(0);
	if (result == 42)
		exit(dehors);
}

void	builtin_exit(t_data *s_data, char *cmd)
{
	long long	dehors;
	char		**splitted;
	int			result;

	(void)cmd;
	splitted = ft_split_sa(s_data->v_path->parsed[s_data->i_cmd].cmd->data[0]);
	result = check_args_ex(s_data->v_path->parsed[s_data->i_cmd].cmd->data[0],
			s_data);
	if (s_data->too_many_args)
	{
		s_data->exit_status = 1;
		free_charchar(splitted);
		return ;
	}
	dehors = c_toll(splitted[1]);
	free_charchar(splitted);
	if (ft_strncmp(s_data->v_path->parsed[s_data->i_cmd].cmd->data[0], "exit",
			4) == 0)
		handle_exit(s_data, dehors, result);
	dehors = s_data->exit_status;
	free_before_exit(s_data);
	exit(dehors);
}
