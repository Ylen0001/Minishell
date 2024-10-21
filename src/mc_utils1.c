/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:02:18 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:50:38 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(t_data *data)
{
	close(data->pipefds[data->i_pipes - 1][0]);
	close(data->pipefds[data->i_pipes - 1][1]);
	close(data->pipefds[data->i_pipes - 2][0]);
	close(data->pipefds[data->i_pipes - 2][1]);
	return ;
}

int	there_is_slash(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	free_pipefds(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->pipefds != NULL)
	{
		while (i < data->v_path->size)
			free(data->pipefds[i++]);
		free(data->pipefds);
	}
}

void	swap_dir(t_data *data)
{
	char	*tmp;

	tmp = data->cwd;
	data->cwd = data->last_dir;
	data->last_dir = tmp;
}
