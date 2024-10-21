/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:23:01 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/01 17:12:16 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/minishell.h"

int	b_i_cd(t_data *data, char *cmd)
{
	if (!cd_init(data, cmd))
		return (0);
	if (ft_strcmp(cmd, "cd ~") == 0)
	{
		if (chdir(data->home_dir) == -1)
			ft_putstr_fd("Error : cd ~.\n", 2);
	}
	else if (ft_strcmp(cmd, "cd -") == 0)
	{
		if (chdir(data->last_dir) == -1)
			ft_putstr_fd("Error : cd -.\n", 2);
		b_i_pwd(data);
	}
	else
	{
		data->path = ft_split(cmd, ' ');
		if (cd_only(data))
			return (0);
		if_abs_or_relative_path(data);
		free_cd(data, 1);
		return (1);
	}
	free_cd(data, 0);
	return (0);
}

int	cd_init(t_data *data, char *cmd)
{
	size_t	it;

	it = 0;
	if (cd_initializer(data))
	{
		ft_putstr_fd("Error : getcwd failed.\n", 2);
		get_home_value(data);
		if (chdir(data->home_dir) == -1)
		{
			ft_putstr_fd("Chdir ; Failed to redirect to home_dir.\n", 2);
			return (0);
		}
	}
	if (too_many_args(data, it, cmd))
		return (0);
	if (home_or_last_dir_fails(data))
		return (0);
	return (1);
}

int	cd_only(t_data *data)
{
	if (data->path[1] == NULL)
	{
		if (chdir(data->home_dir) == -1)
			ft_putstr_fd("Error : Chdir().\n", 2);
		free_cd(data, 1);
		return (1);
	}
	return (0);
}

void	if_abs_or_relative_path(t_data *data)
{
	if (data->path[1][0] == '/')
	{
		if (access(data->path[1], F_OK) == 0)
		{
			if (chdir(data->path[1]) == -1)
				ft_putstr_fd("Error : Chdir().\n", 2);
		}
		else
			ft_putstr_fd("Error : Access().\n", 2);
	}
	else if (access(data->path[1], F_OK) == 0)
	{
		if (chdir(data->path[1]) == -1)
			ft_putstr_fd("Error : Chdir().\n", 2);
		b_i_pwd(data);
	}
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		data->exit_status = 1;
	}
	return ;
}

int	home_or_last_dir_fails(t_data *data)
{
	if (data->home_dir == NULL || data->last_dir == NULL)
	{
		free(data->last_dir);
		free(data->home_dir);
		return (1);
	}
	return (0);
}
