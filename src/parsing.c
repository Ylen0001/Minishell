/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/07/31 18:02:43 by aberion          ###   ########.fr       */
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

int search_n_append(t_data *s_data, char *check_var, char *str, int x_prev)
{
    int safe = x_prev;
    int i = 0;
    while (s_data->vect_env->data[i])
    {
        if (ft_strnstr(s_data->vect_env->data[i], check_var, ft_strlen(check_var)) != 0 && s_data->vect_env->data[i][ft_strlen(check_var)] == '=')
        {
            int j = ft_strlen(check_var) + 1;
            while (s_data->vect_env->data[i][j])
            {
                str[x_prev] = s_data->vect_env->data[i][j];
                x_prev++;
                j++;
            }
            return x_prev;
        }
        i++;
    }
    return safe;
}

void path_to_vect(t_data *s_data)
{
    int i = 0;
    char *s = s_data->full_string;
    char str[1024] = {'\0'};
    // char check_var[500] = {'\0'};
    int x = 0;
    while (s[i])
    {
        if (s[i] == '\'')
        {
            printf("check\n");
            i++;
            while(s[i] && s[i] != '\'')
            {
                str[x] = s[i];
                i++;
                x++;
            }
            i++;
        }
        else if (s[i] == '"')
        {
            i++;
            while (s[i] && s[i] != '"')
            {
                if (s[i] == '$')
                {
                    int j = i + 1;
                    int y = 0;
                    char check_var[500] = {'\0'};
                    while(s[j] && ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] == '_') || (s[j] >= 'a' && s[j] <= 'z') || (s[j] >= '0' && s[j] <= '9')))
                    {
                        check_var[y] = s[j];
                        y++;
                        j++;   
                    }
                    if (s[j] == ' ' || s[j] == '\t' || s[j] == '"' || s[j] == '\'')
                    {
                        x = search_n_append(s_data, check_var, str, x);
                        i+= ft_strlen(check_var) + 1;
                    } 
                }
                
                i++;
                x++;
            }
            i++;
        }
        else
        {
            if (s[i] == '$')
                {
                    int j = i + 1;
                    int y = 0;
                    char check_var[500] = {'\0'};
                    while(s[j] && ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] == '_') || (s[j] >= 'a' && s[j] <= 'z') || (s[j] >= '0' && s[j] <= '9')))
                    {
                        check_var[y] = s[j];
                        y++;
                        j++;   
                    }
                    if (s[j] == ' ' || s[j] == '\t' || s[j] == '"' || s[j] == '\'')
                    {
                        x = search_n_append(s_data, check_var, str, x);
                        i+= ft_strlen(check_var) + 1;
                    } 
                }
            if (s[i] != '"')
                    str[x] = s[i];
            i++;
            x++;    
        }
        
    }
    if (str[0] != '\0')
        vect_happend(s_data->v_path.parsed[0].cmd, str);
}

void launch_parsing(char *input, t_data *s_data)
{
    s_data->full_string = input;
    is_this_ok(s_data);
    path_to_vect(s_data);
    vectstr_print(s_data->v_path.parsed[0].cmd);
}

//''"$USER"''