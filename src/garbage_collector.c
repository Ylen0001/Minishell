/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:27:33 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/13 12:26:56 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_collector(t_data *data)
{
	data->i = 0;

	free(data->cmds);
	free(data->file);
	exit(EXIT_FAILURE);
}

void free_t_vectint(t_vectint *vect)
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

void free_t_vectstr(t_vectstr *vect)
{
    size_t i;

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

void free_t_parsed(t_parsed *parsed)
{
    if (parsed)
    {
        if (parsed->cmd)
            free_t_vectstr(parsed->cmd);
        if (parsed->redir)
            free_t_vectstr(parsed->redir);
        if (parsed->type)
            free_t_vectint(parsed->type);
        // free(parsed);
    }
}

void free_t_vector(t_vector *vector)
{
    size_t i;

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
            free(vector);
        }
    }
}

void free_t_data(t_data *data)
{
    if (data) 
    {
        if (data->vect_env) {
            free_t_vectstr(data->vect_env);
        }

        // if (data->v_path->parsed) {
        //     free_t_vector(data->v_path);
        // }

        if (data->full_string) {
            free(data->full_string);
        }

        if (data->env) {
            for (int i = 0; data->env[i]; ++i) {
                free(data->env[i]);
            }
            free(data->env);
        }

        // free(data);
    }
}
