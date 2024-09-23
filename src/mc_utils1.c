/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mc_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:02:18 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/17 16:06:36 by ylenoel          ###   ########.fr       */
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
