/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:54:55 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 08:31:40 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	check_chevron_conditions(char *s, int i, t_data *s_data)
{
	if (s[i] == '>' && s_data->check_double % 2 == 0 && s_data->check_single
		% 2 == 0)
	{
		if (s[i + 1] == '<')
			return (-1);
		if (s[i + 1] == '>' && s[i + 2] == '>')
			return (-1);
	}
	if (s[i] == '<' && s_data->check_double % 2 == 0 && s_data->check_single
		% 2 == 0)
	{
		if (s[i + 1] == '>')
			return (-1);
		if (s[i + 1] == '<' && s[i + 2] == '<')
			return (-1);
	}
	return (0);
}

int	check_chevron(t_data *s_data)
{
	char	*s;
	int		i;

	i = 0;
	s_data->check_single = 0;
	s_data->check_double = 0;
	s = s_data->full_string;
	while (s[i])
	{
		if (s[i] == '"')
			s_data->check_double++;
		if (s[i] == '\'')
			s_data->check_single++;
		if (check_chevron_conditions(s, i, s_data) == -1)
			return (-1);
		i++;
	}
	return (0);
}

bool	vect_append_command(int *i, int *j, int *x, t_data *s_data)
{
	const char	*s = s_data->full_string;

	(void)j;
	if (ft_strchr("|", s[*i]))
	{
		if (*x > 0 && ft_isspace(s[*x - 1]))
		{
			(*x)--;
			while (ft_isspace(s[*x]))
				s_data->buffer[(*x)--] = '\0';
		}
		vector_happend(s_data->v_path, s_data->buffer);
		(*i)++;
		while (s[*i] && ft_isspace(s[*i]))
			(*i)++;
		path_to_vect(s_data, *i);
		return (true);
	}
	return (false);
}

int	is_this_ok(t_data *s_data)
{
	int		i;
	char	*s;

	if (!s_data->full_string || s_data->full_string == NULL)
		return (12);
	i = 0;
	s = s_data->full_string;
	while (s[i])
	{
		if (s[i] == 39 && s_data->check_double % 2 == 0)
		{
			s_data->count_single++;
			s_data->check_single++;
		}
		if (s[i] == '"' && s_data->check_single % 2 == 0)
		{
			s_data->count_double++;
			s_data->check_double++;
		}
		i++;
	}
	if (s_data->count_double % 2 != 0 || s_data->count_single % 2 != 0)
		return (-1);
	return (0);
}
