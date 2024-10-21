/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:20 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 16:47:02 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

bool	parse_input(int *i, int *j, int *x, t_data *s_data)
{
	const char	*s = s_data->full_string;

	if (vect_append_command(i, j, x, s_data))
		return (true);
	if (s[*i] == '\'')
		handle_simple_quotes(i, x, s_data);
	else if (s[*i] == '\"' && s_data->checkerino != 1)
		*i = handle_double_quotes(s_data, s, *i, x);
	else
		fill_command(s_data, i, x);
	return (false);
}

void	path_to_vect(t_data *s_data, int i)
{
	const char	*s = s_data->full_string;
	int			j;
	int			x;

	ft_memset(s_data->buffer, '\0', BUFFER_SIZE2);
	x = 0;
	s_data->checkerino = 0;
	s_data->v_path->parsed[s_data->v_path->size] = init_parsed();
	skip_whitespaces(s_data, &i);
	j = i;
	if (!ft_strncmp(&s[j], "export", 6))
		s_data->checkerino = 1;
	while (i < (int)ft_strlen(s) && s[i])
		if (parse_input(&i, &j, &x, s_data))
			return ;
	if (ft_isspace(s_data->buffer[x - 1]) && s_data->check_quotes_space != 1
		&& (x-- == 0) + 1)
	{
		while (s_data->buffer[x] == ' ' || s_data->buffer[x] == '\t')
			s_data->buffer[x--] = '\0';
	}
	s_data->check_quotes_space = 0;
	vector_happend(s_data->v_path, s_data->buffer);
}

int	check_redir_after_chev(char *str)
{
	int	j;
	int	size;

	j = 0;
	size = ft_strlen(str);
	while (str[j])
	{
		if (str[j] == '<' || str[j] == '>')
		{
			j++;
			if (str[j] == '<' || str[j] == '>')
				j++;
			while (str[j] && (str[j] == ' ' || str[j] == '\t'))
				j++;
			if (j == size)
				return (-1);
		}
		j++;
	}
	return (0);
}

int	check_after_chev(char *line)
{
	int		i;
	char	**splited;

	i = 0;
	splited = ft_split(line, '|');
	while (splited[i])
	{
		if (check_redir_after_chev(splited[i]) == -1)
		{
			while (splited[i])
				free(splited[i++]);
			free(splited);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
	return (0);
}

// vect_print(s_data->v_path);
// printf("redir :\n");
// vect_print(s_data->v_path->parsed->redir);
// printf("type :\n");
// vect_print(s_data->v_path->parsed->type);
void	launch_parsing(char *input, t_data *s_data)
{
	s_data->full_string = input;
	s_data->count_double = 0;
	s_data->count_single = 0;
	s_data->check_double = 0;
	s_data->check_single = 0;
	if (is_this_ok(s_data) != 0 || check_chevron(s_data) != 0
		|| check_after_chev(input) || check_empty_pipes(s_data))
	{
		s_data->exit_status = 2;
		printf("SyntaxError\n");
		return ;
	}
	path_to_vect(s_data, 0);
}
