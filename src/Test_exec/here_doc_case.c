/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:31:53 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 17:30:10 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc_case(t_data *data)
{
	char *line;

	printf("heredoc> ");
	data->infile = open("here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->infile == -1)
		here_doc_error();
	while (lil_gnl(&line, data) != EOF)
	{
		if (line && (ft_strlen(data->limiter) + 1 == ft_strlen(line))
			&& ft_strncmp(line, data->limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(data->infile);
			return ;
		}
		if (line)
		{
			write(data->infile, line, ft_strlen(line));
			printf("heredoc> ");
		}
		free(line);
	}
	close(data->infile);
	return ;
}