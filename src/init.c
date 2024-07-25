/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/25 15:17:26 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// void init_heredoc(t_data **s_data)
// {
//     t_heredoc *new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
//     if (!new_heredoc)
//         EXIT_FAILURE;
//     new_heredoc->limiter = NULL;
//     new_heredoc->size = 0;
//     (*s_data)->s_here = new_heredoc;
    
// }

t_vectstr init_vect_str()
{
    t_vectstr self;
    
    self.size = 0;
    self.capacity = 10;
    self.data = (char **)malloc(10 * sizeof(char *));
    if (!self.data)
        EXIT_FAILURE;
    return self;
}

t_vector init_vector()
{
    t_vector self;
    
    self.size = 0;
    self.capacity = 10;
    self.node = (t_node *)malloc(10 * sizeof(t_node));
    if(!self.node)
        EXIT_FAILURE;
    self.node->v_cmd = init_vect_str();
    self.node->v_redir = init_vect_str();
    return self;
}

t_data init_data()
{
    t_data self;
    self.pipefds = NULL;
    self.pids = NULL;
    self.infile = 0;
    self.i = 0;
    self.j = 0;
    self.limiter = NULL;
    self.tmp = NULL;
    self.c = '\0';
    self.redirect = 0;
    self.errno = 0;
    self.full_string = NULL;
    self.env = NULL;
    self.v_path = init_vector();
    return self;
}

t_data init()
{
    t_data self;
    self = init_data();
    return self;
}