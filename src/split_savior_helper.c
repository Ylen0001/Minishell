/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_savior_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:33:43 by aberion           #+#    #+#             */
/*   Updated: 2024/10/03 16:34:39 by aberion          ###   ########.fr       */
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
