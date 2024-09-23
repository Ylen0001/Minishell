/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:56 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/17 16:05:42 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	core_exec(t_data *data, size_t it_cmd, int built_in)
{
	const t_vectstr	*cmd = data->v_path->parsed[it_cmd].cmd;

	pipes_and_redirs_check(data, it_cmd);
	if (built_in == 1)
	{
		built_in_manager(data, cmd->data[0]);
		if (data->v_path->size > 1)
			builtin_exit(data, NULL);
		return ;
	}
	else if (built_in == 0)
	{
		data->m_cmd = ft_split(cmd->data[0], ' ');
		check_file(data, data->m_cmd[0]);
		if_absolute_cmd(data);
		if_relative_cmd(data);
	}
	return ;
}

void	if_relative_cmd(t_data *data)
{
	char	*path;

	path = find_path(data->m_cmd[0], data->vect_env->data);
	if (!path || execve(path, data->m_cmd, data->vect_env->data) == -1)
	{
		ft_putstr_fd("0: command not found\n", 2);
		data->exit_status = 127;
		free(path);
		builtin_exit(data, NULL);
	}
	free(path);
	return ;
}

void	if_absolute_cmd(t_data *data)
{
	if (data->m_cmd[0] && (access(data->m_cmd[0], X_OK | F_OK) == 0)
		&& there_is_slash(data->m_cmd[0]))
	{
		if (execve(data->m_cmd[0], data->m_cmd, data->vect_env->data) == -1)
		{
			ft_putstr_fd("0 ; command not found\n", 2);
			data->exit_status = 127;
			builtin_exit(data, NULL);
		}
	}
	return ;
}

void	pipes_and_redirs_check(t_data *data, size_t it_cmd)
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
		redirections(data, redir_t, redir_f->data);
	return ;
}
