/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:26:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/27 14:31:44 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	b_i_pwd(t_data *data)
{
	char *buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if(buffer == NULL)
	{
		data->exit_status = 1;
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putstr_fd("\n", 2);
	data->exit_status = 0;
	return;
}