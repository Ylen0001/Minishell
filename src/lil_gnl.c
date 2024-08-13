/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:55:16 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/08 16:43:08 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lil_gnl(char **line, t_data *data)
{
	data->tmp = NULL;
	data->tmp = lil_gnl_initializer(&data->i, &data->k, data->tmp);
	data->k = read(0, &data->c, 1);
	while (data->k && data->c != '\n' && data->c != '\0')
	{
		if (data->c != '\n' && data->c != '\0')
			data->tmp[data->i] = data->c;
		data->i++;
		data->k = read((0), &data->c, 1);
	}
	if (data->c == -1)
		return (1);
	else if (data->k != 0)
		lil_gnl_finisher(&data->i, data->tmp);
	*line = data->tmp;
	if (data->k == 0)
	{
		free(*line);
		*line = NULL;
	}
	if (data->k == -1)
		return (-1);
	else
		return (1);
}

void	lil_gnl_finisher(int *i, char *tmp)
{
	tmp[*i] = '\n';
	tmp[++*i] = '\0';
}

char	*lil_gnl_initializer(int *i, int *j, char *tmp)
{
	*i = 0;
	*j = 0;
	tmp = (char *)malloc(20000);
	if (!tmp)
		return (NULL);
	return (tmp);
}