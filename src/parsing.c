/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/08/09 17:39:15 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int check_chevron(t_data *s_data)
{
    int check_double = 0;
    int check_single = 0;
    char *s =s_data->full_string;
    int i = 0;
    
    while(s[i])
    {
        if(s[i] == '"')
            check_double++;
        if(s[i] == '\'')
            check_single++;
        if(s[i] == '>' && check_double % 2 == 0 && check_single % 2 == 0)
        {
            if(s[i + 1] == '<')
                return -1;
            if (s[i + 1] == '>' && s[i + 2] == '>')
                return -1;
        }
        if(s[i] == '<' && check_double % 2 == 0 && check_single % 2 == 0)
        {
            if(s[i + 1] == '>')
                return -1;
            if (s[i + 1] == '<' && s[i + 2] == '<')
                return -1;
        }
        i++;
    }
    return 0;
}
int is_this_ok(t_data *s_data)
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
        return -1;
    return 0;
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
void append_redir(t_data *s_data, char *str, int i)
{
    char to_add[500] = {'\0'};
    int j = 0;
    if (str[i] == '<' || str[i] == '>')
        i++;
    if (str[i] == '<' || str[i] == '>')
        i++;
    while(str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while(str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '<' && str[i] != '>'))
    {
        if(str[i] == '"' || str[i] == '\'')
            i++;
        to_add[j] = str[i];
        i++;
        j++;
    }
    vect_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);
}
int manage_chevron(t_data *s_data, char *str, int prev_i)
{
    int i = prev_i;
    while (str[i] == ' ')
        i++;
    while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != '|' && str[i] != ' ')
    {
        if (str[i] == '>' && str[i + 1] != '>')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDOUT_REDIR);
            append_redir(s_data, str, i);
        }
        if (str[i] == '>' && str[i + 1] == '>')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDOUT_APPEND);
            append_redir(s_data, str, i);
            i++;
        }
        if (str[i] == '<' && str[i + 1] != '<')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDIN_REDIR);
            append_redir(s_data, str, i);
        }
        if (str[i] == '<' && str[i + 1] == '<')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, HERE_DOC);
            append_redir(s_data, str, i);
            i++;
        }
        i++;
    }
    return i;
}

void path_to_vect(t_data *s_data, int i)
{
    char *s = s_data->full_string;
    char str[5000] = {'\0'};
    // char check_var[500] = {'\0'};
    int x = 0;

    s_data->v_path->parsed[s_data->v_path->size] = init_parsed();
    while (s[i])
    {
        if (s[i] == '|')
        {
            vect_happend(s_data->v_path, str);
            i++;
            while(s[i] && s[i] == ' ')
                i++;
            path_to_vect(s_data, i);
            return;
        }
        if (s[i] == '\'')
        {
            i++;
            while(s[i] && s[i] != '\'')
            {
                str[x] = s[i];
                i++;
                x++;
            }
            if (s[i] == '\'')
                i++;
        }
        else if (s[i] == '"')
        {
            i++;
            while (s[i] && s[i] != '"')
            {
                if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '"')
                {
                    int j = i + 1;
                    int y = 0;
                    char check_var[500] = {'\0'};
                    while(s[j] && ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] == '_') 
                        || (s[j] >= 'a' && s[j] <= 'z') || (s[j] >= '0' && s[j] <= '9')))
                    {
                        check_var[y] = s[j];
                        y++;
                        j++;   
                    }
                    x = search_n_append(s_data, check_var, str, x);
                    i = j;
                }
                else
                {
                    str[x] = s[i];    
                    i++;
                    x++;
                }
            }
            if (s[i] == '"')
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
                x = search_n_append(s_data, check_var, str, x);
                i = j; 
            }
            else if (s[i] == '<' || s[i] == '>')
            {
                i = manage_chevron(s_data, s, i);
                while(s[i] && s[i] == ' ')
                    i++;
            }
            else
            {
                str[x] = s[i];
                i++;
                x++;
            }    
        }
        
    }
    vect_happend(s_data->v_path, str);
}

void launch_parsing(char *input, t_data *s_data)
{
    s_data->full_string = input;
    if (is_this_ok(s_data) != 0 || check_chevron(s_data) != 0)
    {
        printf("SyntaxError\n");
        return;
    }
    path_to_vect(s_data, 0);
    vect_print(s_data->v_path);
}
//dleodl| dloele| ldoed| loldoeld |loele| ldoed| loldoeld |loele| ldoed| loldoeld |loele| ldoed| loldoeld |

// <pre> echo salut >> file1 > file0 duplique file 0