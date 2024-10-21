/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:19:27 by aberion           #+#    #+#             */
/*   Updated: 2024/10/08 12:44:45 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_characters_qotes(t_data *s_data, char *to_add, int *i, int *x)
{
	const char	*str = s_data->full_string;
	int			j;
	int			y;
	char		check_var[BUFFER_SIZE2];

	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) != 0
				|| str[*i + 1] == '_'))
		{
			j = *i + 1;
			y = 0;
			ft_memset(check_var, '\0', BUFFER_SIZE2);
			while (str[j] && (ft_isalnum(str[j]) != 0 || str[j] == '_'))
				check_var[y++] = str[j++];
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

int	manage_stdout_redir(t_data *s_data, int i)
{
	const char	*str = s_data->full_string;

	if (str[i] == '>' && str[i + 1] != '>')
	{
		vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type,
			STDOUT_REDIR);
		i = append_redir(s_data, i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type,
			STDOUT_APPEND);
		i = append_redir(s_data, i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (i);
}

int	manage_stdin_redir(t_data *s_data, int i)
{
	const char	*str = s_data->full_string;

	if (str[i] == '<' && str[i + 1] != '<')
	{
		vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type,
			STDIN_REDIR);
		i = append_redir(s_data, i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		vectint_happend(s_data->v_path->parsed[s_data->v_path->size].type,
			HERE_DOC);
		i = append_redir_here(s_data, i);
		i++;
		while (i < (int)ft_strlen(str) && str[i] && str[i] == ' ')
			i++;
	}
	return (i);
}

int	handle_chevron(t_data *s_data, int i)
{
	const char	*str = s_data->full_string;

	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != '|'
		&& str[i] != ' ')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>')
				i = manage_stdout_redir(s_data, i);
			else if (str[i] == '<')
				i = manage_stdin_redir(s_data, i);
			break ;
		}
		i++;
	}
	return (i);
}

int	manage_chevron(t_data *s_data, int prev_i)
{
	int	i;

	i = prev_i;
	i = handle_chevron(s_data, i);
	if (i < (int)ft_strlen(s_data->full_string)
		&& s_data->full_string[i] == '"')
		i++;
	return (i);
}
