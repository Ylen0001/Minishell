/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/29 12:48:49 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

char	*ft_realloc(char *ptr, size_t size)
{
	char	*self;

	free(ptr);
	self = ft_calloc((size + 1), sizeof(char));
	if (!self)
		exit(EXIT_FAILURE);
	return (self);
}

int	*ft_realloc_int(int *ptr, size_t size)
{
	int	*self;

	free(ptr);
	self = ft_calloc((size + 1), sizeof(int));
	if (!self)
		exit(EXIT_FAILURE);
	return (self);
}

// void vector_append(t_vector *vect, t_vectstr new_vect)
// {
//     if (vect->size == vect->capacity)
//     {
//         vect->capacity *= 2;
//         t_vectstr *new_v_cmd = (t_vectstr *)ft_realloc(*vect->v_cmd.data, vect->capacity * sizeof(t_vectstr));
//         if (!new_v_cmd)
//             EXIT_FAILURE;
//         vect->v_cmd.data = (char **)new_v_cmd; 
//     }
//     vect->v_cmd.data[vect->size] = *new_vect.data;
//     vect->size++;
// }

void vectstr_happend(t_vectstr *vect, char *data)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->data = (char **)ft_realloc(*vect->data, vect->capacity * sizeof(char *));
        if (!vect->data)
            EXIT_FAILURE;
    }
    vect->data[vect->size] = data;
    vect->size++;
}

void vectint_happend(t_vectint *vect, int number)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->redir_type = (int *)ft_realloc_int(vect->redir_type, vect->capacity * sizeof(int));
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->redir_type[vect->size] = number;
    vect->size++;
}