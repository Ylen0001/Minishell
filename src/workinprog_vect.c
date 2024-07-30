/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/07/30 17:07:45 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void		*ft_realloc(void *ptr, size_t size)
{
	char **new_ptr;
    size_t new_capacity;

    new_capacity = size * 2;
	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = (char **) ft_calloc(new_capacity, sizeof(char *));
	ft_memcpy(new_ptr, ptr, size * sizeof(char *));
    free(ptr);
	return ((void *)new_ptr);
}

void vectstr_free(t_vectstr *vect) {
    int i;

    i = 0;
    while (vect->data[i]) {
        free(vect->data[i]);
        i++;
    }
    free(vect->data);
    free(vect);
}

void vectstr_happend(t_vectstr *vect, char *data)
{
    if (vect->size == vect->capacity)
    {
        vect->data = (char **)ft_realloc(vect->data, vect->capacity);
        vect->capacity *= 2;
        if (!vect->data)
            EXIT_FAILURE;
    }
    vect->data[vect->size] = ft_strdup(data);
    vect->size++;
}

void vectstr_print(t_vectstr *vect) {
    for (int i = 0; vect->data[i] != NULL; i++) {
        printf("vect[%d] = |%s|\n", i, vect->data[i]);
    }
}

void vectint_happend(t_vectint *vect, int number)
{
    if (vect->size == vect->capacity)
    {
        vect->redir_type = (int *)ft_realloc(vect->redir_type, vect->capacity);
        vect->capacity *= 2;
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->redir_type[vect->size] = number;
    vect->size++;
}