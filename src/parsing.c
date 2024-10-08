/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/09/20 14:10:13 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void path_to_vect(t_data *s_data, int i);

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
void append_redir_here(t_data *s_data, int i)
{
    const char *str = s_data->full_string;
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

int handle_characters(t_data *s_data, char *to_add, int *i, int *x)
{
    const char *str = s_data->full_string;
    // int check_q = 0;
    while (str[*i] && (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|'))
    {
        if (str[*i] == '$' && ((str[*i + 1] >= 'A' && str[*i + 1] <= 'Z') 
            || (str[*i + 1] == '_') || (str[*i + 1] >= 'a' && str[*i + 1] <= 'z') 
                || (str[*i + 1] >= '0' && str[*i + 1] <= '9')))
        {
            int j = *i + 1;
            int y = 0;
            char check_var[500] = {'\0'};
            while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] == '_') 
                    || (str[j] >= 'a' && str[j] <= 'z') || (str[j] >= '0' && str[j] <= '9')))
            {
                check_var[y] = str[j];
                y++;
                j++;
            }
            *x = search_n_append(s_data, check_var, to_add, *x);
            *i = j;
        }
        // else if ((str[*i] == '"' || str[*i] == '\'') && check_q % 2 == 0)
        // {
        //     (*i)++;
        //     check_q++;
        // }
        // else if ((str[*i] == '"' || str[*i] == '\'') && check_q % 2 == 1)
        //     return 1;
        else
        {
            to_add[*x] = str[*i];
            (*i)++;
            (*x)++;
        }
    }
    return 0;
}

void handle_characters_qotes(t_data *s_data, char *to_add, int *i, int *x)
{
    const char *str = s_data->full_string;
    while (str[*i] && str[*i] != '"')
    {
        if (str[*i] == '$' && ((str[*i + 1] >= 'A' && str[*i + 1] <= 'Z') 
            || (str[*i + 1] == '_') || (str[*i + 1] >= 'a' && str[*i + 1] <= 'z') 
                || (str[*i + 1] >= '0' && str[*i + 1] <= '9')))
        {
            int j = *i + 1;
            int y = 0;
            char check_var[500] = {'\0'};
            while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] == '_') 
                    || (str[j] >= 'a' && str[j] <= 'z') || (str[j] >= '0' && str[j] <= '9')))
            {
                check_var[y] = str[j];
                y++;
                j++;
            }
            *x = search_n_append(s_data, check_var, to_add, *x);
            *i = j;
        }
        else
        {
            to_add[*x] = str[*i];
            (*i)++;
            (*x)++;
        }
    }
}

int append_redir(t_data *s_data, int i)
{
    const char *str = s_data->full_string;
    char to_add[500] = {'\0'};
    int x = 0;
    if (str[i] == '<' || str[i] == '>')
        i++;
    if (str[i] == '<' || str[i] == '>')
        i++;
    while(str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if(str[i] == '"')
    {
        i++;
        handle_characters_qotes(s_data, to_add, &i, &x);
        vect_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);
        return i;
    }
    if (handle_characters(s_data, to_add, &i, &x))
    {
        vect_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);
        return i;
    }
    vect_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);    
    return i;
}
int manage_chevron(t_data *s_data, int prev_i)
{
    const char *str = s_data->full_string;
    int i = prev_i;
    while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != '|' && str[i] != ' ')
    {
        if (str[i] == '>' && str[i + 1] != '>')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDOUT_REDIR);
            i = append_redir(s_data, i);
            while(str[i] && str[i] == ' ')
                i++;
            break;
        }
        if (str[i] == '>' && str[i + 1] == '>')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDOUT_APPEND);
            i = append_redir(s_data, i);
            i++;
            while(str[i] && str[i] == ' ')
                i++;
            break;
        }
        if (str[i] == '<' && str[i + 1] != '<')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, STDIN_REDIR);
            i = append_redir(s_data, i);
            while(str[i] && str[i] == ' ')
                i++; 
            break;          
        }
        if (str[i] == '<' && str[i + 1] == '<')
        {
            vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type, HERE_DOC);
            append_redir_here(s_data, i);
            i++;
            i++;
            while(str[i] && str[i] == ' ')
                i++;
			break;
        }
    }
    if (str[i] == '"')
        i++;
    return i;
}

int handle_exit_code(t_data *s_data, char *str, int x)
{
    char *to_add;
    int i;

    i = 0;
    to_add = ft_itoa(s_data->exit_status);
    while(to_add[i])
    {
        str[x] = to_add[i];
        i++;
        x++;
    }
    free(to_add);
    return x;
}

int handle_variable_expansion(t_data *s_data, const char *s, int i, int *x)
{
    int j;
    int y;
    char *check_var;
    
    check_var = ft_calloc(500, sizeof(char));
    j = i + 1;
    y = 0;
    if (s[i+ 1] && s[i] == '$' && s[i + 1] == '?')
    {   
        *x = handle_exit_code(s_data, s_data->buffer, *x);
        i+=2;
    }
    if (s[i] && s[i] == '$' && ((s[i + 1] >= 'A' && s[i + 1] <= 'Z') || (s[i + 1] == '_') || 
        (s[i + 1] >= 'a' && s[i + 1] <= 'z') || (s[i + 1] >= '0' && s[i + 1] <= '9')))
    {
        while (s[j] && ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] == '_') || 
                (s[j] >= 'a' && s[j] <= 'z') || (s[j] >= '0' && s[j] <= '9')))
        {
            check_var[y] = s[j];
            y++;
            j++;
        }
        *x = search_n_append(s_data, check_var, s_data->buffer, *x);
        i = j;
    }
    free(check_var);
    return i;
}


int handle_double_quotes(t_data *s_data, const char *s, int i, int *x)
{
    i++;
    while (s[i] && s[i] != '"')
    {
        i = handle_variable_expansion(s_data, s, i, x);
        if (s[i] != '"')
        {
            s_data->buffer[*x] = s[i];
            i++;
            (*x)++;
        }
    }
    if (s[i] == '"')
        i++;
    if (s[i] == '\0')
        s_data->check_quotes_space = 1;
    return i;
}

int	ft_strncmp_index(const char *s1, const char *s2, size_t n, size_t start_index)
{
	size_t	i;
    size_t j;

    j = 0;
	i = start_index;
	while ((s1[i] && s2[j]) && j < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i++;
        j++;
	}
	return (0);
}

void skip_whitespaces(t_data *s_data, int *it)
{
    const char *str = s_data->full_string;
	while (str[*it] && ft_isspace(str[*it]))
		(*it)++;
}

bool vect_append_command(int *i, int *j, int *x, t_data *s_data)
{
    const char *s = s_data->full_string;
    (void)j;
	if (ft_strchr("|", s[*i]))
	{
		if (ft_isspace(s[*x -1]))
		{
			(*x)--;
			while (ft_isspace(s[*x]))
				s_data->buffer[(*x)--] = '\0';
		}
		vect_happend(s_data->v_path, s_data->buffer);
		(*i)++;
		while(s[*i] && ft_isspace(s[*i]))
			(*i)++;
		path_to_vect(s_data, *i);
		return true;
	}
	return false;
}

void handle_simple_quotes(int *i, int *x, t_data *s_data)
{
    const char *s = s_data->full_string;
	(*i)++;
	while(s[*i] && s[*i] != '\'')
	{
		s_data->buffer[*x] = s[*i];
		(*i)++;
		(*x)++;
	}
	if (s[*i] == '\'')
		(*i)++;
	if (s[*i] == '\0')
		s_data->check_quotes_space = 1;
}

void fill_command(t_data *s_data, int *i, int *x)
{
    const char *s = s_data->full_string;
	(*i) = handle_variable_expansion(s_data, s, *i, x);
	if (s[(*i)] && s[(*i)] == '"' && s_data->checkerino != 1)
		(*i)++;
	else if (s[(*i)] && (s[(*i)] == '<' || s[(*i)] == '>'))
	{
		(*i) = manage_chevron(s_data, (*i));
		while(s[(*i)] && s[(*i)] == ' ')
			(*i)++;
	}
	else if (s[(*i)] && s[(*i)] != '$' && s[(*i)] != '"')
	{
		s_data->buffer[(*x)] = s[(*i)];
		(*i)++;
		(*x)++;
	}
	else if (s[(*i)])
	{
		s_data->buffer[(*x)] = s[(*i)];
		(*i)++;
		(*x)++;
	}    
}

bool parse_input(int *i, int *j, int *x, t_data *s_data)
{
    const char *s = s_data->full_string;
	if (vect_append_command(i, j, x, s_data))
		return true;
	if (s[*i] == '\'')
		handle_simple_quotes(i, x, s_data);
	else if (s[*i] == '\"' && s_data->checkerino != 1)
		*i = handle_double_quotes(s_data, s, *i, x);
	else
		fill_command(s_data, i, x);
	return false;
}

void path_to_vect(t_data *s_data, int i)
{
    const char *s = s_data->full_string;
	int j;
    int x;
    
	ft_memset(s_data->buffer, '\0', BUFFER_SIZE2);
	x = 0;
    s_data->checkerino = 0;
    s_data->v_path->parsed[s_data->v_path->size] = init_parsed();
	skip_whitespaces(s_data, &j);
	j = i;
    if (!ft_strncmp(&s[j], "export", 6))
        s_data->checkerino = 1;
    while (s[i])
		if (parse_input(&i, &j, &x, s_data))
			return;
    if (ft_isspace(s_data->buffer[x - 1]) && s_data->check_quotes_space != 1 && (x-- == 0) + 1)
    {
        while (s_data->buffer[x] == ' ' || s_data->buffer[x] == '\t')
            s_data->buffer[x--] = '\0';
    }
    s_data->check_quotes_space = 0;
    vect_happend(s_data->v_path, s_data->buffer);
}

int check_after_chev(char *line)
{
    int i = 0;
    int j = 0;
    int size = 0;
    char **splited;
    
    splited = ft_split(line, '|');
    
    while(splited[i])
    {
        j = 0;
        size = ft_strlen(splited[i]);
        while (splited[i][j])
        {
            if (splited[i][j] == '<' || splited[i][j] == '>')
            {
                j++;
                if (splited[i][j] == '<' || splited[i][j] == '>')
                    j++;
                while(splited[i][j] && (splited[i][j] == ' ' || splited[i][j] == '\t'))
                    j++;
                if (j == size)
                    return -1;
            }
            j++;
        }    
            i++;
    }
    i = 0;
    while(splited[i])
    {
        free(splited[i]);
        i++;
    }
    free(splited);
    return 0;
}

void launch_parsing(char *input, t_data *s_data)
{
    s_data->full_string = input;
    if (is_this_ok(s_data) != 0 || check_chevron(s_data) != 0 || check_after_chev(input))
    {
        printf("SyntaxError\n");
        return;
    }
    path_to_vect(s_data, 0);
    // vect_print(s_data->v_path);
    // printf("redir :\n");
    // vect_print(s_data->v_path->parsed->redir);
    // printf("type :\n");
    // vect_print(s_data->v_path->parsed->type);
}

int check_spaces(char *input)
{
    if(!input)
        return 0;
    int i;
    size_t check;

    check = 0;
    i = 0;
    while (input[i])
    {
        if(input[i] == ' ' || input[i] == '\t')
            check++;
        i++;
    }
    if (check == ft_strlen(input))
        return -1;
    return 0;
}
