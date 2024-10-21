/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:27:33 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:34:58 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_destructor(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->m_cmd != NULL)
	{
		while (data->m_cmd[i] != NULL)
			free(data->m_cmd[i++]);
		free(data->m_cmd);
	}
	i = 0;
	if (data->pipefds != NULL)
	{
		while (i < data->nbr_cmd)
			free(data->pipefds[i++]);
		free(data->pipefds);
	}
	i = 0;
	if (data->hd_names)
	{
		while (i < data->hd_count)
			free(data->hd_names[i++]);
		free(data->hd_names);
		data->hd_names = NULL;
	}
	free_pids(data);
}

void	garbage_destructor_hd(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->pipefds != NULL)
	{
		while (i < data->nbr_cmd)
			free(data->pipefds[i++]);
		free(data->pipefds);
	}
	i = 0;
	if (data->hd_names)
	{
		while (i < data->hd_count)
			free(data->hd_names[i++]);
		free(data->hd_names);
		data->hd_names = NULL;
	}
	if (data->pids != NULL)
	{
		free(data->pids);
		data->pids = NULL;
	}
}

void	garbage_collector(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->pipefds[i] && i < data->v_path->size)
		free(data->pipefds[i++]);
	free(data->pipefds);
	i = 0;
}

void	free_cd(t_data *data, int trigger)
{
	size_t	i;

	i = 0;
	if (trigger)
	{
		if (data->path != NULL)
		{
			while (data->path[i] != NULL)
			{
				free(data->path[i]);
				data->path[i] = NULL;
				i++;
			}
			free(data->path);
			data->path = NULL;
		}
	}
	free(data->last_dir);
	data->last_dir = NULL;
	free(data->home_dir);
	data->home_dir = NULL;
	free(data->cwd);
	data->cwd = NULL;
}
