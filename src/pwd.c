/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:26:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/21 17:04:27 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_data *data)
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
	data->exit_status = 0;
	return;
}