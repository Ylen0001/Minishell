/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:26:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/28 14:51:08 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/colors.h"

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
	printf(C_PEACH"%s\n"C_RESET, buffer);
	data->exit_status = 0;
	return;
}