/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 16:41:28 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

t_vectstr	*init_vect_str(void)
{
	t_vectstr	*self;

	self = ft_calloc(1, sizeof(t_vectstr));
	self->size = 0;
	self->capacity = 10;
	self->data = (char **)ft_calloc(10, sizeof(char *));
	if (!self->data)
		exit(EXIT_FAILURE);
	return (self);
}

t_vectint	*init_vect_int(void)
{
	t_vectint	*self;

	self = ft_calloc(1, sizeof(t_vectint));
	self->size = 0;
	self->capacity = 10;
	self->redir_type = (int *)ft_calloc(10, sizeof(int));
	if (!self->redir_type)
		exit(EXIT_FAILURE);
	return (self);
}

t_parsed	init_parsed(void)
{
	t_parsed	self;

	self.cmd = init_vect_str();
	self.redir = init_vect_str();
	self.type = init_vect_int();
	return (self);
}

t_vector	*init_vector(void)
{
	t_vector	*self;

	self = ft_calloc(1, sizeof(t_vector));
	self->parsed = (t_parsed *)ft_calloc(10, sizeof(t_parsed));
	if (!self->parsed)
		exit(EXIT_FAILURE);
	self->size = 0;
	self->capacity = 10;
	return (self);
}

void	init_env(t_vectstr *vect_env, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		vectstr_happend(vect_env, env[i]);
		i++;
	}
}
