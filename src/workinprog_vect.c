/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/26 14:40:26 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void vector_append(t_vector *vect, t_vectstr new_vect)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        t_vectstr *new_v_cmd = (t_vectstr *)realloc(vect->v_cmd.data, vect->capacity * sizeof(t_vectstr));
        if (!new_v_cmd)
            EXIT_FAILURE;
        vect->v_cmd.data = (char **)new_v_cmd; 
    }
    vect->v_cmd.data[vect->size] = *new_vect.data;
    vect->size++;
}

void vectstr_happend(t_vectstr *vect, char *data)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->data = (char **)realloc(vect->data, vect->capacity * sizeof(char *));
        if (!vect->data)
            EXIT_FAILURE;
        vect->limiter = (char **)realloc(vect->limiter, vect->capacity * sizeof(char *));
        if (!vect->limiter)
            EXIT_FAILURE;
        vect->redir_type = (int *)realloc(vect->limiter, vect->capacity * sizeof(int));
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->data[vect->size] = data;
    vect->size++;
}