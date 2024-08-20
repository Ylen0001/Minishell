/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/08/20 13:13:05 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

t_vectstr *init_vect_str()
{
    t_vectstr *self;
    
    self = ft_calloc(1, sizeof(t_vectstr));
    self->size = 0;
    self->capacity = 10;
    self->data = (char **)ft_calloc(10, sizeof(char *));
    if (!self->data)
        exit(EXIT_FAILURE);
    return self;
}

t_vectint *init_vect_int()
{
    t_vectint *self;
    
    self = ft_calloc(1, sizeof(t_vectint));
    self->size = 0;
    self->capacity = 10;
    self->redir_type = (int *)ft_calloc(10, sizeof(int));
    if (!self->redir_type)
        exit(EXIT_FAILURE);
    return self;
}

t_parsed init_parsed()
{
    t_parsed self;
    
    self.cmd = (t_vectstr *)ft_calloc(10, sizeof(t_vectstr *));
    if (!self.cmd)
        exit(EXIT_FAILURE);
    self.cmd = init_vect_str();
    self.redir = (t_vectstr *)ft_calloc(10, sizeof(t_vectstr *));
    if (!self.redir)
        exit(EXIT_FAILURE);
    self.redir = init_vect_str();
    self.type = init_vect_int();

    return self;
}

t_vector *init_vector()
{
    t_vector *self;
    
    self = ft_calloc(1, sizeof(t_vector));
    self->parsed = (t_parsed *)ft_calloc(10, sizeof(t_parsed));
    if (!self->parsed)
        exit(EXIT_FAILURE);
    self->size = 0;
    self->capacity = 10;
    return self;
}

void init_env(t_vectstr *vect_env, char **env)
{
    int i = 0;

    while(env[i])
    {
        vect_happend(vect_env, env[i]);
        i++;
    }
}

t_data init_data(char **env)
{
    t_data self;
    
    self.full_string = NULL;
    self.env = NULL;
    self.v_path = init_vector();
    self.vect_env = init_vect_str();
    // size_t i = 0;
    // while (i < 10)
    // {
    //     self.v_path->parsed[i] = init_parsed();
    //     i++;
    // }
    init_env(self.vect_env, env);
    return self;
}

void	init_data_2(t_data *data)
{
	size_t	i;

	i = 0;
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
	i = 0;
	data->pipefds = ft_calloc( data->v_path->size, sizeof(int *));
	while (i < data->v_path->size)
		data->pipefds[i++] = ft_calloc(2, sizeof(int) + 1);
	if (!data->pipefds)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->pids = malloc(data->nbr_cmd * sizeof(pid_t) + 1);
	if (data->pids == NULL)
	{
		ft_putstr_fd("Pid malloc failed\n", 2);
		free(data->pids);
		exit(EXIT_FAILURE);
	}
	return ;
}

// void init_heredoc(t_data **s_data)
// {
//     t_heredoc *new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
//     if (!new_heredoc)
//         EXIT_FAILURE;
//     new_heredoc->limiter = NULL;
//     new_heredoc->size = 0;
//     (*s_data)->s_here = new_heredoc;
    
// }
