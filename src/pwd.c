/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:26:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/03 12:01:20 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/colors.h"

void	b_i_pwd(t_data *data)
{
	char *buffer;

	// dprintf(2, "BONJ\n");
	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if(buffer == NULL)
	{
		data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	printf("%s\n", buffer);
	data->exit_status = 0;
	return;
}