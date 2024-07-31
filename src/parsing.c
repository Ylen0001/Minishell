/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/07/31 14:39:50 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void is_this_ok(t_data *s_data)
{
    if (!s_data->full_string || s_data->full_string == NULL)
        EXIT_FAILURE;
    int i = 0;
    int count_double = 0;
    int count_single = 0;
    int check_double = 0;
    int check_single = 0;
    char *s = s_data->full_string; 

    while (s[i])
    {
        if (s[i] == 39 && check_double % 2 == 0)
        {
            count_single++;
            check_single++;
        }
        if (s[i] == '"' && check_single % 2 == 0)
        {
            count_double++;
            check_double++;
        }
        i++;
    }
    if(count_double % 2 != 0 || count_single % 2 != 0)
    {
        printf("SyntaxError\n");
        EXIT_FAILURE;
    }
}

void search_n_append(t_data *s_data, char *var)
{
    char to_add[1024] = {'\0'};
    int i = 0;
    while (s_data->vect_env->data[i])
    {
        if (ft_strnstr(s_data->vect_env->data[i], var, strlen(var)) != 0)
        {
            int j = strlen(var) + 1;
            int x = 0;
            while (s_data->vect_env->data[i][j])
            {
                to_add[x] = s_data->vect_env->data[i][j];
                x++;
                j++;
            }
            vectstr_happend(s_data->v_path.parsed[0].cmd, to_add);
        }
        i++;
    }
}

void path_to_vect(t_data *s_data)
{
    int i = 0;
    char *s = s_data->full_string;
    char var[500] = {'\0'};
    int x = 0;
    while (s[i])
    {
        if (s[i] == '$')
        {
            int j = i + 1;
            x = 0;
            while(s[j] && ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] == '_')))
            {
                var[x] = s[j];
                x++;
                j++;   
            }
            if (s[j] == ' ' || s[j] == '\t' || s[j] == '\0')
                search_n_append(s_data, var);
        }
        i++;    
    }
}

void launch_parsing(char *input, t_data *s_data)
{
    s_data->full_string = input;
    is_this_ok(s_data);
    path_to_vect(s_data);
    // vectstr_print(s_data->v_path.parsed[0].cmd);
}