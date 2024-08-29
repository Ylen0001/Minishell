/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:00:00 by aberion           #+#    #+#             */
/*   Updated: 2024/08/29 14:37:41 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void builtin_env(t_data *s_data)
{
    size_t i = 0;
    while (i < s_data->vect_env->size)
    {
        printf("%s\n", s_data->vect_env->data[i]);
        i++;
    }
}

void builtin_exit(t_data *s_data, char *cmd)
{
    free_t_data(s_data);
    exit(EXIT_SUCCESS);
}
