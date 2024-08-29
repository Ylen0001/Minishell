/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:47:52 by aberion           #+#    #+#             */
/*   Updated: 2024/08/28 16:32:59 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_in_env(t_data *s_data, char *check_var)
{
    int i = 0;
    if (!check_var)
        return;
    while (s_data->vect_env->data[i])
    {
        if (ft_strnstr(s_data->vect_env->data[i], check_var, ft_strlen(check_var)) != NULL 
        && (s_data->vect_env->data[i][ft_strlen(check_var)] == '=' 
        || s_data->vect_env->data[i][ft_strlen(check_var)] == '\0'))
        {
            free(s_data->vect_env->data[i]);
            while (s_data->vect_env->data[i])
            {
                s_data->vect_env->data[i] = s_data->vect_env->data[i + 1];
                i++;
            }
            s_data->vect_env->data[i] = NULL;
            s_data->vect_env->size--;
            return;
        }
        i++;
    }
}

void builtin_unset(t_data *data, char *cmd)
{
    int i = 0;
    int j = 0;
    
    while(cmd[i] && cmd[i] != ' ')
        i++;
    while(cmd[i] && cmd[i] == ' ')
        i++;
    while(cmd[i])
    {
        char to_check[500] = {'\0'};
        while(cmd[i] && cmd[i] != ' ')
        {
            to_check[j] = cmd[i];
            j++;
            i++;
        }
        check_in_env(data, to_check);
        if (!cmd[i])
            return;
        i++;
    }
}
