/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:09:49 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/21 15:01:02 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	init_data(char **env, int ex_data_buff, t_vectstr *env_buff)
{
	t_data	self;

	(void)env;
	self.flag_echo_trig = 0;
	self.checkerino = 0;
	self.full_string = NULL;
	self.env = NULL;
	self.check_quotes_space = 0;
	self.exit_status = ex_data_buff;
	self.v_path = init_vector();
	self.vect_env = env_buff;
	self.hd_it_2 = 0;
	self.hd_trigger = 0;
	self.in_q = 0;
	self.too_many_args = 0;
	self.checkerina = 0;
	return (self);
}

void	init_data_2(t_data *data)
{
	size_t	i;

	i = 0;
	init_exec(data);
	data->pipefds = ft_calloc(data->v_path->size, sizeof(int *));
	while (i < data->v_path->size)
	{
		data->pipefds[i++] = ft_calloc(2, sizeof(int));
	}
	if (!data->pipefds)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->pids = ft_calloc((data->nbr_cmd + 1), sizeof(pid_t));
	if (data->pids == NULL)
	{
		ft_putstr_fd("Pid malloc failed\n", 2);
		free(data->pids);
		exit(EXIT_FAILURE);
	}
	variables_initializer(data);
	return ;
}

void	init_exec(t_data *data)
{
	data->status = 0;
	data->cd_trigger = 0;
	data->i_pipes = 0;
	data->infile = 0;
	data->suffix = 0;
	data->outfile = 0;
	data->i_cmd = 0;
	data->j = 0;
	data->i_redir = 0;
	data->errno = 0;
	data->nbr_cmd = data->v_path->size;
	data->i_cmd = 0;
	data->built_in = 0;
	data->k = 0;
	data->pipe_trig = 0;
	data->old_fdin = 0;
	data->old_fdout = 0;
	data->hd_names = NULL;
	data->m_cmd = NULL;
	return ;
}

void	variables_initializer(t_data *data)
{
	data->path = NULL;
	data->cwd = NULL;
	data->last_dir = NULL;
	data->home_dir = NULL;
	data->bufffer = NULL;
}
