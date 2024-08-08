/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/08/08 16:44:58 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>




void		*ft_realloc(void *ptr, size_t capacity, size_t size)
{
	char **new_ptr;

	if (ptr == NULL)
		return (malloc(capacity));
	if (!capacity)
		return (ptr);
	new_ptr = (char **) ft_calloc(capacity, sizeof(char *));
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
        vect->capacity *= 2;
        vect->data = (char **)ft_realloc(vect->data, vect->capacity, vect->size);
        if (!vect->data)
            EXIT_FAILURE;
    }
    vect->data[vect->size] = ft_strdup(data);
    vect->size++;
}



void vectstr_print(t_vectstr *vect) {
    for (size_t i = 0; i < vect->size; i++) {
        printf("vect[%zu] = |%s|\n", i, vect->data[i]);
    }
}

void vectint_print(t_vectint *vect) {
    for (size_t i = 0; i < vect->size; i++) {
        printf("vect[%zu] =  %d\n", i, vect->redir_type[i]);
    }
}


void vectint_happend(t_vectint *vect, int number)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->redir_type = (int *)ft_realloc(vect->redir_type, vect->capacity, vect->size);
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->redir_type[vect->size] = number;
    vect->size++;
}

void vector_happend(t_vector *vect, void *n) {
    (void) n;
	if (vect->size == vect->capacity - 1)
    {
        vect->capacity *= 2;
        vect->parsed = (t_parsed *)ft_realloc(vect->parsed, vect->capacity, vect->size);
        if (!vect->parsed)
            EXIT_FAILURE;
    }
    vect->size++;
    vect->parsed[vect->size] = init_parsed();
}