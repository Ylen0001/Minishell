/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/07/25 15:58:56 by aberion          ###   ########.fr       */
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

void path_to_vect(t_data *s_data)
{
    int i = 0;
    char *s = s_data->full_string;
    while (s[i])
    {
        if (s[i + 4] && s[i] == '$' && s[i + 1] == 'U' && s[i + 2] == 'S' && s[i + 3] == 'E' && s[i + 4] == 'R')
        {
            int j = 0;
            while (s_data->env[j])
            {
                if (ft_strncmp(s_data->env[j], "LOGNAME", strlen(s_data->env[j])) == 0)
                {
                    int x = 7;
                    while (s_data->env[j][x])
                    {
                        printf("%c", s_data->env[j][x]);
                        x++;
                    }
                    printf("\n");
                }
                j++;
            }
        }
        i++;    
    }
}

void launch_parsing(char *input, t_data *s_data)
{
    s_data->full_string = input;
    is_this_ok(s_data);
    path_to_vect(s_data);    
}