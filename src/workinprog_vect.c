/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/30 13:37:45 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = (void *) malloc(size * sizeof(void *));
	ft_memcpy(new_ptr, ptr, size);
    free(ptr);
	return (new_ptr);
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
        vect->data = (char **)ft_realloc(vect->data, vect->capacity);
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
        vect->redir_type = (int *)ft_realloc(vect->redir_type, vect->capacity);
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->redir_type[vect->size] = number;
    vect->size++;
}