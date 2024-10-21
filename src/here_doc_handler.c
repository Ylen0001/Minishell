/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:36 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/04 14:32:40 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_counter(t_data *data)
{
	size_t	it;
	size_t	it_2;

	it = 0;
	it_2 = 0;
	init_signal(S_HERE_DOC);
	data->hd_count = 0;
	while (it_2 < data->v_path->size)
	{
		while (it < data->v_path->parsed[it_2].type->size)
		{
			if (data->v_path->parsed[it_2].type->redir_type[it] == HERE_DOC)
				data->hd_count++;
			it++;
		}
		it = 0;
		it_2++;
	}
	it = 0;
}

void	here_doc_detector(t_data *data)
{
	size_t	it;
	size_t	it_2;

	it = 0;
	it_2 = 0;
	init_signal(S_HERE_DOC);
	here_doc_counter(data);
	while (it_2 < data->v_path->size)
	{
		while (it < data->v_path->parsed[it_2].type->size)
		{
			if (data->v_path->parsed[it_2].type->redir_type[it] == HERE_DOC)
			{
				here_doc_case(data, data->v_path->parsed[it_2].redir->data[it]);
				if (data->hd_trigger)
					return ;
				replace_hd_by_stdin(data, it, it_2);
			}
			it++;
		}
		it = 0;
		it_2++;
	}
	it = 0;
}

void	replace_hd_by_stdin(t_data *data, size_t it, size_t it_2)
{
	data->v_path->parsed[it_2].type->redir_type[it] = STDIN_REDIR;
	free(data->v_path->parsed[it_2].redir->data[it]);
	data->v_path->parsed[it_2].redir->data[it]
		= ft_strdup(data->hd_names[data->suffix]);
	data->suffix++;
	return ;
}

void	here_doc_case(t_data *data, char *limiter)
{
	char	*line;
	char	*hd_suffix;
	char	*buffer;

	line = NULL;
	hd_suffix = 0;
	if (data->suffix == 0)
		data->hd_names = ft_calloc(data->hd_count + 1, sizeof(char *));
	hd_suffix = ft_itoa(data->suffix);
	buffer = ft_strjoin("here_doc", hd_suffix);
	free(hd_suffix);
	data->hd_names[data->suffix] = ft_strjoin(buffer, ".tmp");
	free(buffer);
	data->a_file = open(data->hd_names[data->suffix],
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->a_file == -1)
		ft_putstr_fd("Error : Creating Here_doc failed.\n", 2);
	here_doc_managing(data, limiter, line);
	close(data->a_file);
	return ;
}

void	here_doc_managing(t_data *data, char *limiter, char *line)
{
	while (1)
	{
		rl_event_hook = rl_event_dummy;
		if (g_signal_received == 2)
		{
			g_signal_received = 0;
			data->hd_trigger = 1;
			break ;
		}
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n",
				2);
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(data->a_file, line, ft_strlen(line));
		write(data->a_file, "\n", 1);
		free(line);
	}
}
