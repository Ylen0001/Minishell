/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:26:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/01 16:45:21 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/minishell.h"

void	b_i_pwd(t_data *data)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
	{
		data->exit_status = 1;
		free(buffer);
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return ;
	}
	printf("%s\n", buffer);
	data->exit_status = 0;
	free(buffer);
	return ;
}
