/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/08/27 10:42:27 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>




void		*ft_realloc(void *ptr, size_t capacity, size_t size, size_t elemSize)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(capacity));
	if (!capacity)
		return (ptr);
	new_ptr = ft_calloc(capacity, elemSize);
	ft_memcpy(new_ptr, ptr, size * elemSize);
    free(ptr);
	return (new_ptr);
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
        vect->data = (char **)ft_realloc(vect->data, vect->capacity, vect->size, sizeof(char *));
        if (!vect->data)
            EXIT_FAILURE;
    }
    vect->data[vect->size] = ft_strdup(data);
    vect->size++;
	// printf("%zu\n", vect->size);
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
        vect->redir_type = (int *)ft_realloc(vect->redir_type, vect->capacity, vect->size, sizeof(int));
        if (!vect->redir_type)
            EXIT_FAILURE;
    }
    vect->redir_type[vect->size] = number;
    vect->size++;
}

void vector_happend(t_vector *vect, char *str)
{
	if (vect->size == vect->capacity)
    {
        vect->capacity *= 2;
        vect->parsed = (t_parsed *)ft_realloc(vect->parsed, vect->capacity, vect->size, sizeof(t_parsed));
        if (!vect->parsed)
            EXIT_FAILURE;
    }
    // vect->parsed[vect->size] = init_parsed();
    vect_happend(vect->parsed[vect->size].cmd, str);
    vect->size++;
}

void vector_print(t_vector *vect) {
	for (size_t i = 0; i < vect->size; i++) {
        dprintf(2, "CMD %zu ===>\n", i);
		vect_print(vect->parsed[i].cmd);
	}
}


t_vectstr *vectstr_dup(t_vectstr *vect)
{
    t_vectstr *new_vect = malloc(sizeof(t_vectstr));
    if (!new_vect)
        return NULL;

    new_vect->size = vect->size;
    new_vect->capacity = vect->capacity;
    new_vect->data = ft_calloc(new_vect->capacity, sizeof(char *));
    if (!new_vect->data)
    {
        free(new_vect);
        return NULL; 
    }
    size_t i = 0;
    while (i < vect->size)
    {
        new_vect->data[i] = ft_strdup(vect->data[i]);
        if (!new_vect->data[i])
        {
            while (i > 0)
            {
                free(new_vect->data[i]);
                i--;
            }
            free(new_vect->data);
            free(new_vect);
            return NULL;
        }
        i++;
    }

    return new_vect;
}