/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:46:21 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/08 12:51:07 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pids(t_data *data)
{
	if (data->pids != NULL)
	{
		free(data->pids);
		data->pids = NULL;
	}
	return ;
}
