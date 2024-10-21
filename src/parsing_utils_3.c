/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:44:26 by aberion           #+#    #+#             */
/*   Updated: 2024/10/21 08:16:23 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_chev(t_data *s_data, int *i)
{
	if (s_data->full_string[*i] == '<' || s_data->full_string[*i] == '>')
		(*i)++;
	if (s_data->full_string[*i] == '<' || s_data->full_string[*i] == '>')
		(*i)++;
}

int	append_redir(t_data *s_data, int i)
{
	char	to_add[BUFFER_SIZE2];
	int		x;

	x = 0;
	ft_memset(to_add, '\0', BUFFER_SIZE2);
	skip_chev(s_data, &i);
	while (s_data->full_string[i] && ft_isspace(s_data->full_string[i]))
		i++;
	if (s_data->full_string[i] == '"')
	{
		i++;
		handle_characters_qotes(s_data, to_add, &i, &x);
		vectstr_happend(s_data->v_path->parsed[s_data->v_path->size].redir,
			to_add);
		return (i);
	}
	if (handle_characters(s_data, to_add, &i, &x))
	{
		vectstr_happend(s_data->v_path->parsed[s_data->v_path->size].redir,
			to_add);
		return (i);
	}
	vectstr_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);
	return (i);
}

int	handle_variable_expansion(t_data *s_data, const char *s, int i, int *x)
{
	int		j;
	int		y;
	char	check_var[BUFFER_SIZE2];

	ft_memset(check_var, '\0', BUFFER_SIZE2);
	j = i + 1;
	y = 0;
	if (s[i + 1] && s[i] == '$' && s[i + 1] == '?')
	{
		*x = handle_exit_code(s_data, s_data->buffer, *x);
		i += 2;
	}
	if (s[i] && s[i] == '$' && (ft_isalnum(s[i + 1]) != 0 || s[i + 1] == '_'))
	{
		while (s[j] && (ft_isalnum(s[j]) != 0 || s[j] == '_'))
			check_var[y++] = s[j++];
		*x = search_n_append(s_data, check_var, s_data->buffer, *x);
		i = j;
	}
	if (s[i] == '$' && s_data->in_q == 0 && !ft_isspace(s[i + 1]) && s[i + 1] != '\0')
		i++;
	return (i);
}

int	handle_exit_code(t_data *s_data, char *str, int x)
{
	char	*to_add;
	int		i;

	i = 0;
	to_add = ft_itoa(s_data->exit_status);
	while (to_add[i])
	{
		str[x] = to_add[i];
		i++;
		x++;
	}
	free(to_add);
	return (x);
}

int	handle_double_quotes(t_data *s_data, const char *s, int i, int *x)
{
	s_data->buffer[*x] = s[i];
	(*x)++;
	i++;
	while (s[i] && s[i] != '"')
	{
		s_data->in_q = 1;
		i = handle_variable_expansion(s_data, s, i, x);
		s_data->in_q = 0;
		if (s[i] != '"')
		{
			s_data->buffer[*x] = s[i];
			i++;
			(*x)++;
		}
	}
	if (s[i] == '"')
	{
		s_data->buffer[*x] = s[i];
		(*x)++;
		i++;
	}
	if (s[i] == '\0')
		s_data->check_quotes_space = 1;
	return (i);
}
