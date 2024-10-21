/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_dup_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:47:13 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 17:15:58 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	vectstr_print(t_vectstr *vect)
{
	size_t	i;

	i = 0;
	while (i < vect->size)
	{
		printf("vect[%zu] = |%s|\n", i, vect->data[i]);
		i++;
	}
}

void	vectint_print(t_vectint *vect)
{
	size_t	i;

	i = 0;
	while (i < vect->size)
	{
		printf("vect[%zu] =  %d\n", i, vect->redir_type[i]);
		i++;
	}
}

void	vector_print(t_vector *vect)
{
	size_t	i;

	i = 0;
	while (i < vect->size)
	{
		printf("CMD %zu ===>\n", i);
		vectstr_print(vect->parsed[i].cmd);
		i++;
	}
}

int	copy_vect_data(t_vectstr *new_vect, t_vectstr *vect)
{
	size_t	i;

	i = 0;
	while (i < vect->size)
	{
		new_vect->data[i] = ft_strdup(vect->data[i]);
		if (!new_vect->data[i])
		{
			while (i > 0)
			{
				free(new_vect->data[i - 1]);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

t_vectstr	*vectstr_dup(t_vectstr *vect)
{
	t_vectstr	*new_vect;

	new_vect = malloc(sizeof(t_vectstr));
	if (!new_vect)
		return (NULL);
	new_vect->size = vect->size;
	new_vect->capacity = vect->capacity;
	new_vect->data = ft_calloc(new_vect->capacity, sizeof(char *));
	if (!new_vect->data)
	{
		free(new_vect);
		return (NULL);
	}
	if (!copy_vect_data(new_vect, vect))
	{
		free(new_vect->data);
		free(new_vect);
		return (NULL);
	}
	return (new_vect);
}
