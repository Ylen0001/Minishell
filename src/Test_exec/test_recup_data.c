/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_recup_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:48:46 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/26 14:12:05 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void recup_data(t_data *data)
{
	char **cmd1;
	char *limiter
	int	*redir;

	redir = data->v_path->v_cmd->redir_type[0];
	cmd1 = data->v_path->v_cmd->data;
	limiter = data->v_path->v_cmd->limiter[0];
	
	if(redir == HERE_DOC)
	{
		
	}
	
}

int	is_here_doc(char *limiter, t_data *data, int i_hd_name)
{
	char	*line;

	write(1, "heredoc> ", 9);
		data->infile = open(data->hd_name[i_hd_name], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->infile == -1)
		here_doc_error();
	while (lil_gnl(&line, data) != EOF)
	{
		if (line && (ft_strlen(limiter) + 1 == ft_strlen(line))
			&& ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(data->infile);
			return ;
		}
		if (line)
		{
			write(data->infile, line, ft_strlen(line));
			write(1, "heredoc> ", 9);
		}
		free(line);
	}
	close(data->infile);	
}