/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:27:33 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/18 15:12:00 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	garbage_destructor(t_data *data)
{
	size_t i;

	i = 0;
	if(data->m_cmd != NULL)
	{
		while(data->m_cmd[i] != NULL)
		{
			free(data->m_cmd[i]);
			i++;
		}
		free(data->m_cmd);
	}
	i = 0;
	if(data->pipefds != NULL)
	{
		while(i < data->nbr_cmd)
			free(data->pipefds[i++]);
		free(data->pipefds);
	}
	if(data->pids != NULL)
		free(data->pids);
	i = 0;
	// if(data->hd_names != NULL)
	// {
	// 	while(i < data->hd_count)
	// 		free(data->hd_names[i++]);
	// 	free(data->hd_names);
	// }
}

void	garbage_collector(t_data *data)
{
	// (void)data;
	size_t i;

	i = 0;
	free(data->pids);
	// i = 0;
	while(data->pipefds[i] && i < data->v_path->size)
		free(data->pipefds[i++]);
	free(data->pipefds);
	i = 0;

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
            free(vector->parsed);
        }
        free(vector);
    }
}

void free_t_data(t_data *data, int check)
{
    size_t i;

    i = 0;
    if (!data)
        return;
    if (data) 
    {
        if (data->vect_env)
            free_t_vectstr(data->vect_env);
        if (data->v_path)
            free_t_vector(data->v_path);
        if (data->full_string)
            free(data->full_string);
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


