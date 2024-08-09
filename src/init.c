/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/08/09 17:24:41 by aberion          ###   ########.fr       */
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
