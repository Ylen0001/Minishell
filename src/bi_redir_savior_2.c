/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_redir_savior_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:55:15 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/08 12:55:55 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipes_and_redirs_check_3(t_data *data, size_t it_cmd)
{
	const t_vectint	*redir_t = data->v_path->parsed[it_cmd].type;
	const t_vectstr	*redir_f = data->v_path->parsed[it_cmd].redir;

	if (data->i_pipes > 0)
	{
		if (dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Dup2: Error\n", 2);
		close(data->pipefds[data->i_pipes - 1][0]);
		close(data->pipefds[data->i_pipes - 1][1]);
	}
	if (it_cmd != data->v_path->size - 1 || (it_cmd == 0
			&& data->v_path->size >= 2))
	{
		if (dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Dup2: Error\n", 2);
	}
	if (data->pipe_trig)
	{
		close(data->pipefds[data->i_pipes][1]);
		close(data->pipefds[data->i_pipes][0]);
	}
	if (redir_f->size > 0)
		redirections_3(data, redir_t, redir_f->data);
	return (0);
}
