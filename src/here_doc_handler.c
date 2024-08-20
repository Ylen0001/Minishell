/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:36 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/20 16:06:55 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	g_signal_received;

void	here_doc_detector(t_data *data)
{
	size_t it;
	size_t it_2;

	init_signal(S_HERE_DOC);

	it = 0;
	it_2 = 0;
	data->hd_count = 0;
	// dprintf(2, "size1 = %zu\n", data->v_path->size);
	while(it_2 < data->v_path->size)
	{
		while(it < data->v_path->parsed[it_2].type->size) // Compte le nbr d'here_doc
		{
			// printf("size = %zu\n", data->v_path->parsed[it_2].type->size);
			// printf("redir type = %d\n", data->v_path->parsed->type->redir_type[it]);
			if(data->v_path->parsed[it_2].type->redir_type[it] == HERE_DOC)
			{
				here_doc_case(data, data->v_path->parsed[it_2].redir->data[it]);
				data->hd_count++;
			}
			it++;
		}
		it = 0;
		it_2++;
	}
	it = 0;
	printf("hd_count = %zu\n", data->hd_count);
}

void	 here_doc_case(t_data *data, char *limiter)
{
	char 	*line;
	char	*hd_suffix;
	char	*buffer;
	
	
	// printf("hd_count : %zu\n", data->hd_count);
	hd_suffix = 0;
	if(data->suffix == 0)
		data->hd_names = malloc(sizeof(char*) * data->hd_count);
	hd_suffix = ft_itoa(data->suffix);
	buffer = ft_strjoin("here_doc", hd_suffix);
	data->hd_names[data->suffix] = ft_strjoin(buffer, ".tmp");
	// printf("hd_name = %s\n", data->hd_names[data->suffix]);
	// printf("EOF = %s\n", limiter);
	// printf("File hd = %s, suffix = %zu\n", data->hd_names[data->suffix], data->suffix);
	data->a_file = open(data->hd_names[data->suffix], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->a_file == -1)
		ft_putstr_fd("Error : Creating Here_doc failed.\n", 2);
	data->suffix++;
	while(1)
	{
		rl_event_hook = rl_event_dummy;
		line = readline("> ");
		if(!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
			// close(data->a_file);
			break;
		}
		if(ft_strncmp(line, limiter, ft_strlen(limiter) - 1) == 0)
		{
			free(line);
			break;
		}
		write(data->a_file, line, ft_strlen(line));
		write(data->a_file, "\n", 1);
		free(line);	
	}
	close(data->a_file);
	return ;
}