/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:36 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/19 13:38:09 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	g_signal_received;

void	here_doc_detector(t_data *data)
{
	size_t it;

	init_signal(S_HERE_DOC);

	it = 0;
	data->hd_count = 0;
	while(it < data->v_path->parsed->type->size) // Compte le nbr d'here_doc
	{
		// printf("size = %zu\n", data->v_path->parsed->type->size);
		// printf("redir type = %d\n", data->v_path->parsed->type->redir_type[it]);
		if(data->v_path->parsed->type->redir_type[it] == HERE_DOC)
			data->hd_count++;
		it++;
	}
	it = 0;
	// printf("hd_count = %zu\n", data->hd_count);
	if(data->hd_count > 0)
		while(it < data->hd_count)
		{
			here_doc_case(data, data->v_path->parsed->redir->data[it]);
			it++;
		}
	return ;
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
	// ft_strlcat(data->hd_names[data->suffix], hd_suffix, 10);
	// ft_strlcat(data->hd_names[data->suffix], ".tmp", 15);
	// printf("hd_name = %s\n", data->hd_names[data->suffix]);
	// printf("EOF = %s\n", limiter);
	printf("File hd = %s, suffix = %zu\n", data->hd_names[data->suffix], data->suffix);
	// write(1, "heredoc> ", 9);
	data->a_file = open(data->hd_names[data->suffix], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->a_file == -1)
		ft_putstr_fd("Error : Creating Here_doc failed.\n", 2);
	// if(data->a_file == 0)
	// 	dprintf(2, "Mayday on a un problème!\n");
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
	// while (lil_gnl(&line, data) != EOF)
	// {
	// 	if (line && (ft_strlen(limiter) + 1 == ft_strlen(line))
	// 		&& ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
	// 	{
	// 		free(line);
	// 		close(data->a_file);
	// 		return;
	// 	}
	// 	if (line)
	// 	{
	// 		write(data->a_file, line, ft_strlen(line));
	// 		write(1, "heredoc> ", 9);
	// 	}
	// 	free(line);
	// }
	dprintf(2, "Bonjour\n");
	close(data->a_file);
	return ;
}