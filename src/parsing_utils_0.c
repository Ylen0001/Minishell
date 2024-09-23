/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:54:55 by aberion           #+#    #+#             */
/*   Updated: 2024/09/20 10:57:25 by aberion          ###   ########.fr       */
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

int	check_chevron(t_data *s_data)
{
	int check_double;
	int check_single;
	char *s;
	int i;

    i = 0;
    check_single = 0;
	check_double = 0;
    s = s_data->full_string;
	while (s[i])
	{
		if (s[i] == '"')
			check_double++;
		if (s[i] == '\'')
			check_single++;
		if (s[i] == '>' && check_double % 2 == 0 && check_single % 2 == 0)
		{
			if (s[i + 1] == '<')
				return (-1);
			if (s[i + 1] == '>' && s[i + 2] == '>')
				return (-1);
		}
		if (s[i] == '<' && check_double % 2 == 0 && check_single % 2 == 0)
		{
			if (s[i + 1] == '>')
				return (-1);
			if (s[i + 1] == '<' && s[i + 2] == '<')
				return (-1);
		}
		i++;
	}
	return (0);
}
