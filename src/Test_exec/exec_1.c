/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:01:25 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/25 15:21:42 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 1ère étape, ligne de cmd non valide */

void	exec_core(t_data *data)
{
	while(redir[i++])
	{
		i = 0;
		if(redir[i] == "<<")
		{
			name_hd(data->hd_name);
			is_here_doc(limiter, data, nbr_hd, data->i_hd_name);
			data->i_hd_name++;
		}
		
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

int		is_dir(t_data *data)
{
	DIR	*dir;
	if((dir = opendir(data->full_string)) != NULL)
	{
		printf("%s: Is a directory\n", data->full_string);
		closedir(dir);
		return -1;
	}
	else if(access(data->full_string, F_OK | R_OK | W_OK) == -1)
	{
		printf("%s: Permission denied\n", data->full_string);
		return -1;
	}
	return (1);
}

void	infile_check(t_data *data)
{
	data->i = 0;
	if(is_dir(data))
		data->infile = open(data->lst_cmd[data->i], O_RDONLY, 0777);
	if(data->infile == -1)
	{
		close(data->infile);
		printf("%s: Permission Denied\n", data->lst_cmd[data->i]);
	}
}
void	mother_forker(pid_t *pid, t_data *data)
{
	if(pipe(data->pipefds[data->i_pipes]) == -1)
	{
		printf("Pipe %d : Failure\n", data->i_pipes);
		return ;
	}
	data->i_pipes++;
	data->pids[data->i_pids] = fork();
	if (*pid == -1)
	{
		free(data->pipefds);
		error();
	}
	return ;
}

