/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/25 14:21:03 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void vector_append(t_vector *vect, t_node new_node)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->node = (t_node *)realloc(vect->node, vect->capacity * sizeof(t_node));
        if (!vect->node)
            EXIT_FAILURE;
    }
    vect->node[vect->size] = new_node;
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
    }
    vect->data[vect->size] = data;
    vect->size++;
}