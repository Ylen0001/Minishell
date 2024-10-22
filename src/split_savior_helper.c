/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_savior_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:33:43 by aberion           #+#    #+#             */
/*   Updated: 2024/10/22 16:38:00 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	eat_whitespace(char const *s, int *i)
{
	while (s[*i] && ft_strchr(" ", s[*i]))
	{
		(*i)++;
	}
}

void	fill_vect_sa(bool *q, int *i, const char *s)
{
	if (s[*i] == '\'')
		q[0] = !q[0];
	if (s[*i] == '\"')
		q[1] = !q[1];
}
