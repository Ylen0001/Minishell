/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:22:27 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:25:23 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_file(t_data *data, char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat) != -1)
	{
		if (check_file_1(data, &file_stat, cmd) != NULL)
			return (cmd);
	}
	else if (there_is_slash(cmd))
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		data->exit_status = 127;
		if (data->pids != NULL)
		{
			free(data->pids);
			data->pids = NULL;
		}
		handle_exit_savior(data);
	}
	return (NULL);
}

char	*check_file_1(t_data *data, struct stat *file_stat, char *cmd)
{
	if (there_is_slash(cmd) && S_ISDIR(file_stat->st_mode))
	{
		ft_putstr_fd(" Is a directory\n", 2);
		data->exit_status = 126;
		handle_exit_savior(data);
	}
	if (file_stat->st_mode & S_IXUSR)
	{
		return (cmd);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		data->exit_status = 126;
		handle_exit_savior(data);
	}
	else
	{
		ft_putstr_fd(" command not found\n", 2);
		data->exit_status = 127;
		handle_exit_savior(data);
	}
	return (NULL);
}
