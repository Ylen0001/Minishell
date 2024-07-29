/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:05:57 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/29 18:23:10 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infile_or_heredoc(t_data *data)
{
	if (ft_strncmp(data->v_path->v_cmd, "here_doc", 8) == 0)
	{
		here_doc_case(argv, data);
		return ;
	}
	else
	{
		infile_case(argv, data);
		return ;
	}
}



