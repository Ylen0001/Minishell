/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workinprog_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:08:10 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 16:47:17 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t capacity, size_t size, size_t elemSize)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(capacity));
	if (!capacity)
		return (ptr);
	new_ptr = ft_calloc(capacity, elemSize);
	ft_memcpy(new_ptr, ptr, size * elemSize);
	free(ptr);
	return (new_ptr);
}

void	vectstr_free(t_vectstr *vect)
{
	int	i;

	i = 0;
	while (vect->data[i])
	{
		free(vect->data[i]);
		i++;
	}
	free(vect->data);
	free(vect);
}

void	vectstr_happend(t_vectstr *vect, char *data)
{
	if (vect->size == vect->capacity)
	{
		vect->capacity *= 2;
		vect->data = (char **)ft_realloc(vect->data, vect->capacity, vect->size,
				sizeof(char *));
		if (!vect->data)
			exit(EXIT_FAILURE);
	}
	vect->data[vect->size] = ft_strdup(data);
	vect->size++;
}

void	vectint_happend(t_vectint *vect, int number)
{
	if (vect->size == vect->capacity)
	{
		vect->capacity *= 2;
		vect->redir_type = (int *)ft_realloc(vect->redir_type, vect->capacity,
				vect->size, sizeof(int));
		if (!vect->redir_type)
			exit(EXIT_FAILURE);
	}
	vect->redir_type[vect->size] = number;
	vect->size++;
}

void	vector_happend(t_vector *vect, char *str)
{
	if (vect->size == vect->capacity)
	{
		vect->capacity *= 2;
		vect->parsed = (t_parsed *)ft_realloc(vect->parsed, vect->capacity,
				vect->size, sizeof(t_parsed));
		if (!vect->parsed)
			exit(EXIT_FAILURE);
	}
	vectstr_happend(vect->parsed[vect->size].cmd, str);
	vect->size++;
}
