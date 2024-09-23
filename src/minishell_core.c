/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:55:26 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/17 16:04:35 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_data *data)
{
	init_data_2(data);
	here_doc_detector(data);
	init_signal(S_EXEC);
	if (data->v_path->size > 0
		&& data->v_path->parsed[data->i_cmd].cmd->data[0][0] == '\0')
	{
		data->exit_status = 0;
		return ;
	}
	while (data->v_path->size > 0 && data->i_cmd < data->v_path->size)
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
	waitpids_and_unlink(data);
}

void	waitpids_and_unlink(t_data *data)
{
	size_t	it;

	it = -1;
	while (++it < data->i_cmd)
	{
		waitpid(data->pids[it], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	free(data->pids);
	it = -1;
	while (++it < data->hd_count)
		unlink(data->hd_names[it]);
	return ;
}

void	single_bi_cmd_exec(t_data *data)
{
	data->old_fdin = dup(STDIN_FILENO);
	if (data->old_fdin == 0)
	{
		dprintf(2, "Error: Dup oldfd_in = %d\n", data->old_fdin);
		data->exit_status = 0;
	}
	data->old_fdout = dup(STDOUT_FILENO);
	if (data->old_fdout == -1)
	{
		dprintf(2, "Error: Dup oldfd out = %d\n", data->old_fdout);
		data->exit_status = 0;
	}
	core_exec(data, data->i_cmd, data->built_in);
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
	if (data->pids[data->i_cmd] == -1)
		ft_putstr_fd("Error : Fork Failed\n", 2);
	if (data->pids[data->i_cmd] == 0)
		core_exec(data, data->i_cmd, data->built_in);
	return ;
}

void	mult_cmd_exec(t_data *data)
{
	if (pipe(data->pipefds[data->i_pipes]) == -1)
	{
		perror("");
		ft_putstr_fd("Error : Pipe failed.\n", 2);
	}
	data->pipe_trig = 1;
	if (data->v_path->size >= 3 && data->i_pipes >= 2)
	{
		close(data->pipefds[data->i_pipes - 2][0]);
		close(data->pipefds[data->i_pipes - 2][1]);
	}
	data->pids[data->i_cmd] = fork();
	if (data->pids[data->i_cmd] == -1)
		ft_putstr_fd("Error : Fork Failed\n", 2);
	if (data->pids[data->i_cmd] == 0)
		core_exec(data, data->i_cmd, data->built_in);
	data->i_pipes++;
	return ;
}
