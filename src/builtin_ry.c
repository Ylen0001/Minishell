/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:33:52 by aberion           #+#    #+#             */
/*   Updated: 2024/09/03 12:22:17 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void replace_variable(t_vectstr *env, char *to_add, int i)
{
    free(env->data[i]);
    env->data[i] = (char *)ft_calloc(ft_strlen(to_add), sizeof(char));
    env->data[i] = (char *)ft_strdup(to_add);
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

int check_presence(t_vectstr *env, char *to_check)
{
    int i = 0;
    char clean[500] = {'\0'};

    while (to_check[i] && to_check[i] != '=')
    {
        clean[i] = to_check[i];
        i++;
    }
    i = 0;
    while(env->data[i])
    {
        if (ft_strnstr(env->data[i], clean, ft_strlen(clean)) != 0)
        {
            replace_variable(env, to_check, i);
            return 1;
        }
        i++;
    }
    return 0;
}
void builtin_export(t_data *s_data, char *cmd)
{
    int i = 0;
    int j = 0;
    char *s = cmd;
    while (s[i] && s[i] == ' ')
        i++;
    while(s[i] && s[i] != ' ')
        i++;
    if (s[i] == '\0')
    {
        print_export(s_data);
        return;
    }
    while (s[i] && s[i] == ' ')
        i++;
    while(s[i])
    {
        char to_add[500] = {'\0'};
        j = 0;
        while(s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
        {
			// if(ft_isalnum(s[i]) == 0 || s[i] == '_')
			// 	s_data->exit_status = 1;
            to_add[j] = s[i];
            i++;
            j++;
        }
        if (to_add[0])
        {
            if (check_presence(s_data->vect_env, to_add) == 0)
			{
               vect_happend(s_data->vect_env, to_add);
			}
			else
				s_data->exit_status = 1;
        }
        i++;
    }
}

// void send_builtin(t_data *s_data)
// {
//     //char *checker = ft_strnstr(s_data->full_string, "export", ft_strlen(s_data->full_string));
//     // if(checker[6] && (checker[6] == '\0' || checker[6] == ' ' || checker[6] == '\n'))
//     //     builtin_export(s_data);
//     builtin_unset(s_data, s_data->full_string);
//     if(strcmp(s_data->v_path->parsed[0].cmd[0].data[0], "exit") == 0)
//         builtin_exit(s_data);
// }

