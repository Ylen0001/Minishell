/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_redir_savior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:40:05 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:25:06 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	core_exec_3(t_data *data, size_t it_cmd, int built_in)
{
	const t_vectstr	*cmd = data->v_path->parsed[it_cmd].cmd;

	pipes_and_redirs_check_3(data, it_cmd);
	if (built_in == 1)
	{
		built_in_manager(data, cmd->data[0]);
		if (data->v_path->size > 1)
			handle_exit_savior(data);
		return (1);
	}
	else if (built_in == 0)
	{
		data->m_cmd = ft_split_sa(cmd->data[0]);
		check_file(data, data->m_cmd[0]);
		if_absolute_cmd(data);
		if_relative_cmd(data);
	}
	return (0);
}

int	redirections_3(t_data *data, const struct s_vectint *redir_t,
		char **redir_f)
{
	size_t	it;

	it = -1;
	while (++it < redir_t->size)
	{
		if (redir_t->redir_type[it] == STDIN_REDIR)
		{
			if (if_stdin_redir_3(data, redir_t->redir_type[it],
					redir_f[it]) == 1)
				return (1);
		}
		else if (redir_t->redir_type[it] == HERE_DOC)
			if_heredoc_redir(data, redir_t->redir_type[it]);
		else
		{
			if (if_stdout_redir_3(data, redir_t->redir_type[it],
					redir_f[it]) == 1)
				return (1);
		}
	}
	return (0);
}

int	if_stdin_redir_3(t_data *data, int redir_type, char *redir_file)
{
	if (open_file_minishell_3(data, redir_type, redir_file) == 0)
	{
		free_pids(data);
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	if (dup2(data->a_file, STDIN_FILENO) == -1)
		data->exit_status = 0;
	close(data->a_file);
	return (0);
}

int	if_stdout_redir_3(t_data *data, int redir_type, char *redir_file)
{
	if (open_file_minishell_3(data, redir_type, redir_file) == 0)
	{
		return (1);
	}
	if (dup2(data->a_file, STDOUT_FILENO) == -1)
		data->exit_status = 2;
	close(data->a_file);
	return (0);
}

int	open_file_minishell_3(t_data *data, int type, char *file)
{
	int	open_flags;

	open_flags = get_open_flags(type);
	if ((type == STDIN_REDIR && access(file, F_OK | R_OK) != -1)
		|| type >= HERE_DOC)
	{
		data->a_file = open(file, open_flags, 0644);
		if (data->a_file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			data->exit_status = 1;
			return (1);
		}
		if (data->a_file == 0)
			ft_putstr_fd("Error : Open failed\n", 2);
		return (1);
	}
	else
	{
		data->exit_status = 1;
		return (0);
	}
	return (0);
}
