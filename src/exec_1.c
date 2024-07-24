/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:01:25 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 15:48:44 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 1ère étape, ligne de cmd non valide */

void	is_dir(t_data *data)
{
	DIR	*dir;
	if((dir = opendir(data->full_string)) != NULL)
	{
		printf("%s: Is a directory\n", data->full_string);
		closedir(dir);
	}
	else if(access(data->full_string, F_OK | R_OK | W_OK) == -1)
	{
		printf("%s: Permission denied\n", data->full_string);
	}
	return;
}

// void	test_exec(t_data *data)
// {
	
// }


// void	exec_core(t_data *data)
// {
// 	data->i = 0;

// 	while(data->cmd[0][data->i])
// 	{
// 		if(data->cmd[0][data->i] == "<<")
// 			here_doc_case(data);
// 		data->i++;
// 	}
// 	data->i = 0;
// 	while(data->cmd[0][data->i])
// 	{
// 		if(data->cmd[0][data->i] == ">")
// 			outfile_case(data);
// 		else if(data->cmd[0][data->i] = "<")
// 			infile_case(data);
// 		else if (data->cmd[0][data->i] == ">>")
// 			append_case(data);
// 		else if (data->cmd[0][data->i] == "|")
// 			pipe_case(data);
// 		data->i++;
// 	}

// }