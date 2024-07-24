/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/24 11:59:19 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void init_heredoc(t_data **s_data)
{
    t_heredoc *new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
    if (!new_heredoc)
        EXIT_FAILURE;
    new_heredoc->limiter = NULL;
    new_heredoc->node = 0;
    new_heredoc->prev = NULL;
    new_heredoc->next = NULL;
    (*s_data)->s_here = new_heredoc;
}

void init_liste(t_data **s_data)
{
    t_liste *new_liste = (t_liste *)malloc(sizeof(t_liste));
    if (!new_liste)
        EXIT_FAILURE;
    new_liste->full_string = NULL;
    new_liste->cmd = NULL;
    new_liste->redirect = STDIN_REDIR;
    new_liste->prev = NULL;
    new_liste->next = NULL;
    (*s_data)->s_list = new_liste;
}

void init_data(t_data **s_data)
{
    
    t_data *new_data = (t_data *)malloc(sizeof(s_data));
    if (!new_data)
        EXIT_FAILURE;
    new_data->pipefds = NULL;
    new_data->pids = NULL;
    new_data->infile = -1;
    new_data->i = 0;
    new_data->j = 0;
    new_data->tmp = NULL;
    new_data->c = '\0';
    new_data->s_here = NULL;
    new_data->s_list = NULL;
    new_data->errno = 0;
    *s_data = new_data;
}

void init(t_data **s_data)
{
    init_data(s_data);
    if (s_data)
    {
        init_heredoc(s_data);
        init_liste(s_data);
    }
}