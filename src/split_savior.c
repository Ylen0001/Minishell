/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_savior.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:13:05 by aberion           #+#    #+#             */
/*   Updated: 2024/10/07 16:46:39 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	fill_vect_helper(t_vectstr *vect, const char *s, t_range range)
{
	char	*str;

	str = ft_substr(s, range.s, range.e - range.s);
	vectstr_happend(vect, str);
	free(str);
}

static void	fill_vector(t_vectstr *vect, const char *s, int *i, int end)
{
	bool	q[2];
	t_range	range;

	q[0] = false;
	q[1] = false;
	eat_whitespace(s, i);
	range.s = *i;
	range.e = *i;
	while (*i < end)
	{
		if (s[*i] == '\'')
			q[0] = !q[0];
		if (s[*i] == '\"')
			q[1] = !q[1];
		if (!q[0] && !q[1] && s[*i] == ' ')
		{
			fill_vect_helper(vect, s, range);
			return (fill_vector(vect, s, i, end));
		}
		range.e++;
		(*i)++;
	}
	if (range.e > range.s && !q[0] && !q[1])
		fill_vect_helper(vect, s, range);
}

char	*remove_quotes_from_string(char *str)
{
	char	*new_str;
	bool	in_quotes[2];
	int		j;
	int		k;

	new_str = (char *)malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	in_quotes[0] = false;
	in_quotes[1] = false;
	j = 0;
	k = 0;
	while (str[k])
	{
		if (str[k] == '\'' && !in_quotes[1])
			in_quotes[0] = !in_quotes[0];
		else if (str[k] == '"' && !in_quotes[0])
			in_quotes[1] = !in_quotes[1];
		else
			new_str[j++] = str[k];
		k++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	clean_quotes(char **strings)
{
	int		i;
	char	*new_str;

	i = 0;
	while (strings[i])
	{
		new_str = remove_quotes_from_string(strings[i]);
		if (new_str)
		{
			free(strings[i]);
			strings[i] = new_str;
		}
		i++;
	}
}

char	**ft_split_sa(const char *s)
{
	t_vectstr	*vect;
	int			i;
	char		**tmp;
	int			end;

	end = ft_strlen(s);
	if (s[end] == ' ')
		end--;
	vect = init_vect_str();
	i = 0;
	fill_vector(vect, s, &i, end);
	clean_quotes(vect->data);
	tmp = vect->data;
	free(vect);
	return (tmp);
}
