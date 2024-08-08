/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:36 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/08 17:20:01 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_detector(t_data *data)
{
	size_t it;

	it = 0;
	data->hd_count = 0;
	while(it < data->v_path.parsed->type->size) // Compte le nbr d'here_doc
	{
		printf("size = %zu\n", data->v_path.parsed->type->size);
		printf("redir type = %d\n", data->v_path.parsed->type->redir_type[it]);
		if(data->v_path.parsed->type->redir_type[it] == HERE_DOC)
			data->hd_count++;
		it++;
	}
	it = 0;
	printf("hd_count = %zu\n", data->hd_count);
	if(data->hd_count > 0)
		while(it < data->hd_count)
		{
			here_doc_case(data, data->v_path.parsed->redir->data[it]);
			it++;
		}
	return ;
}

void	 here_doc_case(t_data *data, char *limiter)
{
	char 	*line;
	char	*hd_suffix;
	
	
	hd_suffix = 0;
	data->hd_names = malloc(sizeof(char*) * data->hd_count);
	data->hd_names[data->suffix] = ft_strdup("here_doc");	
	hd_suffix = ft_itoa(data->suffix);
	ft_strlcat(data->hd_names[data->suffix], hd_suffix, 10);
	ft_strlcat(data->hd_names[data->suffix], ".tmp", 15);
	// printf("hd_name = %s\n", data->hd_names[data->suffix]);
	printf("EOF = %s\n", limiter);
	write(1, "heredoc> ", 9);
	data->a_file = open(data->hd_names[data->suffix], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->a_file == -1)
		ft_putstr_fd("Error : Opening Here_doc failed.\n", 2);
	while (lil_gnl(&line, data) != EOF)
	{
		if (line && (ft_strlen(limiter) + 1 == ft_strlen(line))
			&& ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(data->a_file);
			return ;
		}
		if (line)
		{
			write(data->a_file, line, ft_strlen(line));
			write(1, "heredoc> ", 9);
		}
		free(line);
	}
	close(data->a_file);
	data->suffix++;
	return ;
}