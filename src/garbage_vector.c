/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:38:52 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/25 10:40:00 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_vectint(t_vectint *vect)
{
	if (vect)
	{
		if (vect->redir_type)
		{
			free(vect->redir_type);
		}
		free(vect);
	}
}

void	free_t_vectstr(t_vectstr *vect)
{
	size_t	i;

	i = 0;
	if (vect)
	{
		if (vect->data)
		{
			while (i < vect->size)
			{
				if (vect->data[i])
					free(vect->data[i]);
				i++;
			}
			free(vect->data);
		}
		free(vect);
	}
}

void	free_t_parsed(t_parsed *parsed)
{
	if (parsed)
	{
		if (parsed->cmd)
			free_t_vectstr(parsed->cmd);
		if (parsed->redir)
			free_t_vectstr(parsed->redir);
		if (parsed->type)
			free_t_vectint(parsed->type);
	}
}

void	free_t_vector(t_vector *vector)
{
	size_t	i;

	i = 0;
	if (vector)
	{
		if (vector->parsed)
		{
			while (i < vector->size)
			{
				free_t_parsed(&vector->parsed[i]);
				i++;
			}
			free(vector->parsed);
		}
		free(vector);
	}
}

void	free_t_data(t_data *data, int check)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	if (data)
	{
		if (data->vect_env)
			free_t_vectstr(data->vect_env);
		if (data->v_path)
			free_t_vector(data->v_path);
		if (check == 0 && data->env)
		{
			while (data->env[i])
			{
				free(data->env[i]);
				i++;
			}
			free(data->env);
		}
	}
}
