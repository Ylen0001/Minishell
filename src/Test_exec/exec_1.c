/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:01:25 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 17:36:27 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 1ère étape, ligne de cmd non valide */

int		is_dir(t_data *data)
{
	DIR	*dir;
	if((dir = opendir(data->full_string)) != NULL)
	{
		printf("%s: Is a directory\n", data->full_string);
		closedir(dir);
		return -1;
	}
	else if(access(data->full_string, F_OK | R_OK | W_OK) == -1)
	{
		printf("%s: Permission denied\n", data->full_string);
		return -1;
	}
	return (1);
}

void	infile_check(t_data *data)
{
	data->i = 0;
	if(is_dir(data))
		data->infile = open(data->lst_cmd[data->i], O_RDONLY, 0777);
	if(data->infile == -1)
	{
		close(data->infile);
		printf("%s: Permission Denied\n", data->lst_cmd[data->i]);
	}
}
void	mother_forker(pid_t *pid, t_data *data)
{
	if(pipe(data->pipefds[data->i_pipes]) == -1)
	{
		printf("Pipe %d : Failure\n", data->i_pipes);
		return ;
	}
	data->i_pipes++;
	data->pids[data->i_pids] = fork();
	if (*pid == -1)
	{
		free(data->pipefds);
		error();
	}
	return ;
}

