/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:09:05 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 13:56:22 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp_index(const char *s1, const char *s2, size_t n,
		size_t start_index)
{
	size_t	i;
	size_t	j;

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

void	skip_whitespaces(t_data *s_data, int *it)
{
	const char	*str = s_data->full_string;

	while (str[*it] && ft_isspace(str[*it]))
		(*it)++;
}

void	handle_simple_quotes(int *i, int *x, t_data *s_data)
{
	const char	*s = s_data->full_string;

	s_data->buffer[*x] = s[*i];
	(*i)++;
	(*x)++;
	while (s[*i] && s[*i] != '\'')
	{
		s_data->buffer[*x] = s[*i];
		(*i)++;
		(*x)++;
	}
	if (s[*i] == '\'')
	{
		s_data->buffer[*x] = s[*i];
		(*i)++;
		(*x)++;
	}
	if (s[*i] == '\0')
		s_data->check_quotes_space = 1;
}

void	fill_command(t_data *s_data, int *i, int *x)
{
	const char	*s = s_data->full_string;

	(*i) = handle_variable_expansion(s_data, s, *i, x);
	if (s[(*i)] && s[(*i)] == '"' && s_data->checkerino != 1)
		(*i)++;
	else if (s[(*i)] && (s[(*i)] == '<' || s[(*i)] == '>'))
	{
		(*i) = manage_chevron(s_data, (*i));
		while ((*i) < (int)ft_strlen(s) && s[(*i)] && s[(*i)] == ' ')
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

int	check_empty_pipes(t_data *s_data)
{
	char	*s;
	int		i;

	i = 0;
	s = s_data->full_string;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (1);
	return (0);
}
