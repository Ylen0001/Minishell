/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/24 12:36:12 by aberion          ###   ########.fr       */
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

void init_data(t_data **s_data)
{
    
    t_data *new_data = (t_data *)malloc(sizeof(s_data));
    if (!new_data)
        EXIT_FAILURE;
    new_data->pipefds = NULL;
    new_data->pids = NULL;
    new_data->infile = 0;
    new_data->i = 0;
    new_data->j = 0;
    new_data->limiter = NULL;
    new_data->tmp = NULL;
    new_data->c = '\0';
    // new_data->redirect = default_redirect;
    new_data->errno = 0;
    *s_data = new_data;
}

void init(t_data **s_data)
{
    init_data(s_data);
}