/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:27:33 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/01 12:53:35 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_collector(t_data *data)
{
	data->i = 0;

	free(data->cmds);
	free(data->file);
	exit(EXIT_FAILURE);
}