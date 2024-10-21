/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:28:16 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 14:51:51 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file_minishell(t_data *data, int type, char *file)
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
			handle_exit_savior(data);
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
}

void	redirections(t_data *data, const struct s_vectint *redir_t,
		char **redir_f)
{
	size_t	it;

	it = -1;
	while (++it < redir_t->size)
	{
		if (redir_t->redir_type[it] == STDIN_REDIR)
			if_stdin_redir(data, redir_t->redir_type[it], redir_f[it]);
		else if (redir_t->redir_type[it] == HERE_DOC)
			if_heredoc_redir(data, redir_t->redir_type[it]);
		else
			if_stdout_redir(data, redir_t->redir_type[it], redir_f[it]);
	}
}

void	if_stdout_redir(t_data *data, int redir_type, char *redir_file)
{
	if (open_file_minishell(data, redir_type, redir_file) == 0)
		return ;
	if (dup2(data->a_file, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Dup2: STDOUT REDIR failed.\n", 2);
		data->exit_status = 2;
	}
	close(data->a_file);
}

void	if_heredoc_redir(t_data *data, int redir_type)
{
	if (open_file_minishell(data, redir_type,
			data->hd_names[data->hd_it_2]) == 0)
		return ;
	if (dup2(data->a_file, STDIN_FILENO) == -1)
	{
		data->exit_status = 2;
		ft_putstr_fd("Dup2: HERE_DOC REDIR failed.\n", 2);
	}
	close(data->a_file);
}

void	if_stdin_redir(t_data *data, int redir_type, char *redir_file)
{
	if (open_file_minishell(data, redir_type, redir_file) == 0)
	{
		free_pids(data);
		ft_putstr_fd(" No such file or directory\n", 2);
		handle_exit_savior(data);
		return ;
	}
	if (dup2(data->a_file, STDIN_FILENO) == -1)
	{
		data->exit_status = 0;
		ft_putstr_fd("Dup2: STDIN REDIR failed.\n", 2);
	}
	close(data->a_file);
	return ;
}
