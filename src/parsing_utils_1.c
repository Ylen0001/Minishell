/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:31:53 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 17:14:03 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_n_append(t_data *s_data, char *check_var, char *str, int x_prev)
{
	int	safe;
	int	i;
	int	j;

	safe = x_prev;
	i = 0;
	while (s_data->vect_env->data[i])
	{
		if (ft_strnstr(s_data->vect_env->data[i], check_var,
				ft_strlen(check_var)) != 0
			&& s_data->vect_env->data[i][ft_strlen(check_var)] == '=')
		{
			j = ft_strlen(check_var) + 1;
			while (s_data->vect_env->data[i][j])
			{
				str[x_prev] = s_data->vect_env->data[i][j];
				x_prev++;
				j++;
			}
			return (x_prev);
		}
		i++;
	}
	return (safe);
}

int	append_redir_here(t_data *s_data, int i)
{
	const char	*str = s_data->full_string;
	char		to_add[BUFFER_SIZE2];
	int			j;

	ft_memset(to_add, '\0', BUFFER_SIZE2);
	j = 0;
	if (str[i] == '<' || str[i] == '>')
		i++;
	if (str[i] == '<' || str[i] == '>')
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '<'
			&& str[i] != '>'))
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		to_add[j] = str[i];
		i++;
		j++;
	}
	vectstr_happend(s_data->v_path->parsed[s_data->v_path->size].redir, to_add);
	return (i);
}

int	handle_variable(t_data *s_data, char *to_add, int *i, int *x)
{
	int			j;
	const char	*str = s_data->full_string;
	int			y;
	char		check_var[BUFFER_SIZE2];

	ft_memset(check_var, '\0', BUFFER_SIZE2);
	j = *i + 1;
	y = 0;
	while (str[j] && (ft_isalnum(str[j]) != 0 || str[j] == '_'))
	{
		check_var[y] = str[j];
		y++;
		j++;
	}
	*x = search_n_append(s_data, check_var, to_add, *x);
	*i = j;
	return (0);
}

int	handle_characters(t_data *s_data, char *to_add, int *i, int *x)
{
	const char	*str = s_data->full_string;

	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != '|'))
	{
		if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) != 0 || str[*i
					+ 1] == '_'))
		{
			handle_variable(s_data, to_add, i, x);
		}
		else
		{
			to_add[*x] = str[*i];
			(*i)++;
			(*x)++;
		}
	}
	return (0);
}

int	check_spaces(char *input)
{
	int		i;
	size_t	check;

	if (!input)
		return (0);
	check = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			check++;
		i++;
	}
	if (check == ft_strlen(input))
		return (-1);
	return (0);
}
