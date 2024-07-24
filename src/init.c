/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/24 17:26:23 by aberion          ###   ########.fr       */
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

void init_data(t_data *s_data)
{
    if (!s_data)
        EXIT_FAILURE;
    s_data->pipefds = NULL;
    s_data->pids = NULL;
    s_data->infile = 0;
    s_data->i = 0;
    s_data->j = 0;
    s_data->limiter = NULL;
    s_data->tmp = NULL;
    s_data->c = '\0';
    s_data->redirect = 0;
    s_data->errno = 0;
    s_data->v_path.data = (char **)malloc(10 * sizeof(char *));
    if (!s_data->v_path.data)
        EXIT_FAILURE;
    s_data->v_path.size = 0;
    s_data->v_path.capacity = 10;
}

void init(t_data *s_data)
{
    init_data(s_data);
}