/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/25 12:27:22 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void vector_append(t_vector *vect, t_node new_node)
{
    if (vect->size >= vect->capacity)
    {
        t_node *new_nodes;
        vect->capacity *= 2;
        new_nodes = (t_node *)realloc(vect->node, vect->capacity * sizeof(t_node));
        if (!vect->node)
            EXIT_FAILURE;
        vect->node = new_nodes;
    }
    vect->node[vect->size] = new_node;
    vect->size++;
}