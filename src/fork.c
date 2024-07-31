/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:43:50 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/31 14:20:42 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mother_forker(t_data *data)
{
	data->pids[data->i_pids] = fork();
	if (data->pids[data->i_pids] == -1)
	{
		free(data->pipefds);
		ft_putstr_fd("Error: Pipefds mother_forker.\n", 2);
	}
	return ;
}

// void	child_process_a(char *env[], t_data *data)
// {
// 	if (data->v_path.parsed[data->nbr_cmd].redir == HERE_DOC)
// 		data->infile = open("here_doc.tmp", O_RDONLY, 0777);
// 	close(data->pipefds[data->i_pipes][0]);
// 	if (dup2(data->infile, STDIN_FILENO) == -1)
// 		ft_putstr_fd("Dup STDIN error.\n", 2);
// 	if (dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
// 		ft_putstr_fd("Dup STDOUT error.\n", 2);
// 	close(data->infile);
// 	close(data->pipefds[data->i_pipes][1]);
// 	exec_cmd(argv, env, data);
// }