/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:33:52 by aberion           #+#    #+#             */
/*   Updated: 2024/08/27 15:52:30 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_format(char *s)
{
    int i = 0;
    while(s[i] != ' ')
        i++;
    while (s[i] == ' ')
        i++;
    while(s[i] && (ft_isalnum(s[i])!= 0 || s[i] == '_'))
        i++;
    if(s[i] != '=')
        return -1;
    return 0;
}

void print_export(t_data *s_data)
{
    int i = 0;
    int j = 0;
    int check = 0;
    
    while (s_data->vect_env->data[i])
    {
        printf("export ");
        j = 0;
        while (s_data->vect_env->data[i][j])
        {
            if(s_data->vect_env->data[i][j] == '=')
            {
                check = 1;
                printf("=\"");
            }
            else
                printf("%c", s_data->vect_env->data[i][j]);
            j++;
        }
        if (check == 1)
        {
            check = 0;
            printf("\"");
        }
        printf("\n");
        i++;
    }
}
void builtin_export(t_data *s_data)
{
    int i = 0;
    int j = 0;
    char *s = s_data->full_string;
    // if (check_format(s) != 0)
    // {
    //     printf("export expected format :\nexport var=value\n");
    //     return;
    // }
    while(s[i] && s[i] != ' ')
        i++;
    while (s[i] && s[i] == ' ')
        i++;
    if (s[i] == '\0')
    {
        print_export(s_data);
        return;
    }
    while(s[i])
    {
        char to_add[500] = {'\0'};
        j = 0;
        while(s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
        {
            to_add[j] = s[i];
            i++;
            j++;
        }
        if (to_add[0])
            vect_happend(s_data->vect_env, to_add);
        i++;
    }
}

void send_builtin(t_data *s_data)
{
    if(ft_strnstr(s_data->full_string, "export", 6) != 0)
        builtin_export(s_data);
    
}

