/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:11:24 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/01 17:10:02 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_initializer(t_data *data)
{
	data->cwd = getcwd(data->cwd, 0);
	if (data->cwd == NULL)
		return (1);
	get_home_value(data);
	get_oldpwd_value(data);
	update_oldpwd_env(data);
	return (0);
}

int	too_many_args(t_data *data, size_t it, char *cmd)
{
	size_t	i;

	i = 0;
	data->path = ft_split(cmd, ' ');
	while (data->path[it])
		it++;
	if (it > 2)
	{
		data->exit_status = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	while (i < it)
		free(data->path[i++]);
	free(data->path);
	return (0);
}

void	update_oldpwd_env(t_data *data)
{
	char	*new_pwd;
	size_t	i;

	i = 0;
	while (i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "OLDPWD=", 7) == 0)
		{
			new_pwd = ft_strjoin("OLDPWD=", data->cwd);
			free(data->vect_env->data[i]);
			data->vect_env->data[i] = ft_strdup(new_pwd);
			free(new_pwd);
			return ;
		}
		i++;
	}
	return ;
}

int	get_oldpwd_value(t_data *data)
{
	char	**env_data;
	size_t	i;

	i = 0;
	while (i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "OLDPWD=", 7) == 0)
		{
			env_data = ft_split(data->vect_env->data[i], '=');
			data->last_dir = malloc(sizeof(char) * ft_strlen(env_data[1]) + 1);
			ft_strlcpy(data->last_dir, env_data[1], ft_strlen(env_data[1]) + 1);
			i = 0;
			while (env_data[i])
			{
				free(env_data[i]);
				i++;
			}
			free(env_data);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_home_value(t_data *data)
{
	char	**env_data;
	size_t	i;

	i = 0;
	while (i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "HOME=", 5) == 0)
		{
			env_data = ft_split(data->vect_env->data[i], '=');
			data->home_dir = malloc(sizeof(char) * ft_strlen(env_data[1]) + 1);
			ft_strlcpy(data->home_dir, env_data[1], ft_strlen(env_data[1]) + 1);
			i = 0;
			free(env_data[1]);
			free(env_data[0]);
			free(env_data);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
