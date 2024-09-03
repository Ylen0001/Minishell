/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:23:01 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/03 12:07:19 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/colors.h"

int b_i_cd(t_data *data, char *cmd) // Chemin absolu / relatif
{
	char 		*home_dir;
	char		*last_dir;
	char		*cwd;
	char		**path;
	size_t it;
		
	it = 0;
	path = NULL;
	cwd = NULL;
	last_dir = NULL;
	home_dir = NULL;
	cwd = getcwd(cwd, 0);
	last_dir = get_oldpwd_value(data, last_dir);
	home_dir = get_home_value(data, home_dir);		// Penser à free.
	update_oldpwd_env(data, cwd);				// Update old_pwd avant tout changement de dir. 
	path = ft_split(cmd, ' ');
	while(path[it])
		it++;
	// dprintf(2, "data %zu = %s\n", it, data->v_path->parsed[data->i_cmd].cmd->data[0]);
	// dprintf(2, "size data = %zu\n", it);
	if(it > 2)
	{	
		data->exit_status = 1;
		ft_putstr_fd("Too many arguments\n", 2);
		return(0);
	}
	path = NULL;
	it = 0;
	if(home_dir == NULL|| last_dir == NULL)
	{
		free(last_dir);
		free(home_dir);
		return (0);
	}
	// printf("last_dir = %s\nhome_dir = %s\ncwd = %s\n", last_dir, home_dir, cwd);
	if(ft_strcmp(cmd, "cd ~") == 0)
	{
		if(chdir(home_dir) == -1)
			perror("chdir() error.\n");			// Changement de dir vers home.
	}
	else if(ft_strcmp(cmd, "cd -") == 0)
	{
		if(chdir(last_dir) == -1)
			perror("chdir() error.\n");
		b_i_pwd(data);
	}
	else
	{
		path = ft_split(cmd, ' ');
		if(path[1] == NULL)
		{
			if(chdir(home_dir) == -1)
				perror("chdir() error.\n");
			return(0);
		}
		// printf("path[1] = %s\n", path[1]);
		if(path[1][0] == '/')							// Absolute path
		{
			if(access(path[1], F_OK) == 0)
			{
				if(chdir(path[1]) == -1)
					perror("chdir() error.\n");
			}
			else
				perror("access() error\n");
		}
		else if(access(path[1], F_OK) == 0)					// relative path
		{
			cwd = ft_strjoin(cwd, "/");
			cwd = ft_strjoin(cwd, path[1]);
			// printf("Relative path = %s\n", cwd);
			if(chdir(path[1]) == 0)
				perror("chdir() error.\n");
			b_i_pwd(data);
		}
		else
			perror("Access: Error\n");
	}
	free(path);
	free(cwd);
	free(last_dir);
	return (1);
}

	
char	*get_home_value(t_data *data, char *cwd)
{
	char **env_data;
	size_t	i;
	
	i = 0;
	// env_data = malloc(sizeof(char*) * 2);
	// printf("%zu\n", data->vect_env->size);
	while(i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "HOME=", 5) == 0)
		{
			// printf("%s\n", data->vect_env->data[i]);
			env_data = ft_split(data->vect_env->data[i], '=');
			cwd = malloc(sizeof(char) * ft_strlen(env_data[1]) + 1);
			ft_strlcpy(cwd, env_data[1], ft_strlen(env_data[1]) + 1);
			i = 0;
			while(env_data[i])
			{
				free(env_data[i]);
				i++;
			}
			return(cwd);
		}
		i++;
	}
	return (NULL);
}

char *get_oldpwd_value(t_data *data, char *last_dir)
{
	char **env_data;
	size_t	i;
	
	i = 0;
	// env_data = malloc(sizeof(char*) * 2);
	// printf("%zu\n", data->vect_env->size);
	while(i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "OLDPWD=", 7) == 0)
		{
			// printf("%s\n", data->vect_env->data[i]);
			env_data = ft_split(data->vect_env->data[i], '=');
			last_dir = malloc(sizeof(char) * ft_strlen(env_data[1]) + 1);
			ft_strlcpy(last_dir, env_data[1], ft_strlen(env_data[1]) + 1);
			i = 0;
			while(env_data[i])
			{
				free(env_data[i]);
				i++;
			}
			free(env_data);
			return(last_dir);
		}
		i++;
	}
	return (NULL);
}

void	update_oldpwd_env(t_data *data, char *updated_oldpwd)
{
	char	*new_pwd;
	size_t	i;
	
	i = 0;
	// printf("%zu\n", data->vect_env->size);
	while(i < data->vect_env->size)
	{
		if (ft_strncmp(data->vect_env->data[i], "OLDPWD=", 7) == 0)
		{
			// printf("%s\n", data->vect_env->data[i]);
			new_pwd = ft_strjoin("OLDPWD=", updated_oldpwd);
			free(data->vect_env->data[i]);
			data->vect_env->data[i] = ft_strdup(new_pwd);
			// printf("newpwd = %s\n", new_pwd);
			free(new_pwd);
			return;
		}
		i++;
	}
	return;
}

	
	 	// if(access(path[1], F_OK) != 0) 				//		// relative
		// {	
		// 	printf("Dans if\n");
		// 	buffer = NULL;
		// 	buffer = ft_strjoin(home_dir, "/");
		// 	buffer = ft_strjoin(buffer, path[1]);
		// 	printf("%s\n", buffer);
		// 	if(chdir(path[1]) == 0)
		// 		printf("Moves to new directory\n");
		// 	else
		// 		perror("chdir() error.\n");
		// 	it = 0;
		// 	while(path)
		// 	{
		// 		free(path[it]);
		// 		it++;
		// 	}
		// 	b_i_pwd(data);
		// }

	// if(data->cd_trigger == 0)
	// {
	// 	ft_strlcpy(last_dir, buffer, ft_strlen(buffer) + 1); // 1ère fois qu'on rentre dans cd, last_dir = cwd.
	// 	data->cd_trigger = 1;
	// }
	// printf("%s\n", last_dir);