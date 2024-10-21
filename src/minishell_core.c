/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:55:26 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:51:40 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_data *data)
{
	init_signal(S_EXEC);
	init_data_2(data);
	here_doc_detector(data);
	if (data->hd_trigger == 1)
	{
		garbage_destructor(data);
		free_pids(data);
		return ;
	}
	if (g_signal_received == 2)
	{
		g_signal_received = 0;
		return ;
	}
	if (data->v_path->size > 0
		&& data->v_path->parsed[data->i_cmd].cmd->data[0][0] == '\0')
	{
		data->exit_status = 0;
		garbage_destructor_hd(data);
		return ;
	}
	while (data->v_path->size > 0 && data->i_cmd < data->v_path->size)
		cmds_exec(data);
	waitpids_and_unlink(data);
}

void	cmds_exec(t_data *data)
{
	built_in_detector(data, data->v_path->parsed[data->i_cmd].cmd->data[0]);
	if (data->v_path->size > 1)
		mult_cmd_exec(data);
	else if (data->i_cmd == 0 && data->built_in == 0
		&& data->v_path->size == 1)
		single_cmd_not_bi_exec(data);
	else
		single_bi_cmd_exec(data);
	if (data->i_cmd == data->v_path->size - 1 && data->pipe_trig)
		close_pipes(data);
	data->i_cmd++;
	data->built_in = 0;
}

void	single_bi_cmd_exec(t_data *data)
{
	data->old_fdin = dup(STDIN_FILENO);
	if (data->old_fdin == 0)
		data->exit_status = 0;
	data->old_fdout = dup(STDOUT_FILENO);
	if (data->old_fdout == -1)
		data->exit_status = 0;
	core_exec_3(data, data->i_cmd, data->built_in);
	if (dup2(data->old_fdin, STDIN_FILENO) == -1)
		ft_putstr_fd("Error: Dup2\n", 2);
	if (dup2(data->old_fdout, STDOUT_FILENO) == -1)
		ft_putstr_fd("Error: Dup2\n", 2);
	close(data->old_fdin);
	close(data->old_fdout);
}

void	single_cmd_not_bi_exec(t_data *data)
{
	data->pids[data->i_cmd] = fork();
	if (data->pids[data->i_cmd] != 0)
		data->hd_it_2++;
	if (data->pids[data->i_cmd] == -1)
		ft_putstr_fd("Error : Fork Failed\n", 2);
	if (data->pids[data->i_cmd] == 0)
	{
		init_signal(S_EXEC);
		core_exec(data, data->i_cmd, data->built_in);
	}
	return ;
}

void	mult_cmd_exec(t_data *data)
{
	if (pipe(data->pipefds[data->i_pipes]) == -1)
		ft_putstr_fd("Error : Broken pipe.\n", 2);
	data->pipe_trig = 1;
	if (data->v_path->size >= 3 && data->i_pipes >= 2)
	{
		close(data->pipefds[data->i_pipes - 2][0]);
		close(data->pipefds[data->i_pipes - 2][1]);
	}
	data->pids[data->i_cmd] = fork();
	if (data->pids[data->i_cmd] != 0)
		data->hd_it_2++;
	if (data->pids[data->i_cmd] == -1)
		ft_putstr_fd("Error : Fork Failed\n", 2);
	if (data->pids[data->i_cmd] == 0)
	{
		init_signal(S_EXEC);
		core_exec(data, data->i_cmd, data->built_in);
	}
	data->i_pipes++;
	return ;
}
