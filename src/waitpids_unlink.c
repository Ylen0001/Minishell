/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpids_unlink.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:15:56 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/08 12:53:13 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	waitpids_and_unlink(t_data *data)
{
	size_t	it;

	it = -1;
	init_signal(S_EXEC);
	if (data->pids != NULL)
	{
		while (++it < data->i_cmd)
		{
			waitpid(data->pids[it], &data->exit_status, 0);
			if (WIFEXITED(data->exit_status))
				data->exit_status = WEXITSTATUS(data->exit_status);
		}
	}
	if (g_signal_received == 2)
	{
		printf("\n");
		data->exit_status = 130;
		g_signal_received = 0;
	}
	free_pids(data);
	it = -1;
	while (++it < data->hd_count)
		unlink(data->hd_names[it]);
	free_pipefds(data);
	unlink_hd(data);
}

void	unlink_hd(t_data *data)
{
	size_t	it;

	it = 0;
	if (data->hd_names)
	{
		while (it < data->suffix)
			free(data->hd_names[it++]);
		free(data->hd_names);
		data->hd_names = NULL;
	}
}
