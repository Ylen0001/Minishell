/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:20:44 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/03 14:24:00 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_from_stdin(t_data *s_data)
{
	ssize_t	bytes_read;
	size_t	len;
	char	buffer[2];
	char	*line;

	bytes_read = 0;
	len = 0;
	ft_memset(buffer, '\0', 2);
	line = ft_calloc(2048, sizeof(char));
	if (line == NULL)
	{
		free_broken_malloc(s_data);
		return (NULL);
	}
	return (if_failures(line, buffer, &len, &bytes_read));
}

char	*if_failures(char *line, char *buffer, size_t *len, ssize_t *bytes_read)
{
	lil_gnl(line, buffer, len, bytes_read);
	if ((*bytes_read) < 0 || strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	line[(*len)] = '\0';
	if (strlen(line) > 0)
		return (line);
	else
	{
		free(line);
		return (NULL);
	}
}

void	free_broken_malloc(t_data *s_data)
{
	free_t_data(s_data, 0);
	garbage_destructor(s_data);
	perror("calloc");
}

void	lil_gnl(char *line, char *buffer, size_t *len, ssize_t *bytes_read)
{
	*bytes_read = read(STDIN_FILENO, buffer, 1);
	while (*bytes_read > 0)
	{
		line[(*len)++] = buffer[0];
		if (buffer[0] == '\n' || buffer[0] == '\0')
			break ;
		*bytes_read = read(STDIN_FILENO, buffer, 1);
	}
}
