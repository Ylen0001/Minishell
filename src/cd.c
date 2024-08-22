/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:23:01 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/22 16:57:17 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int cd(t_data *data, char **cmd) // Chemin absolu / relatif
{
	static char last_dir[1024];
	// char		current_dir[1024];
	char	*path;
	size_t it;

	it = 0;
	if(ft_strcmp(cmd[1], '-') == 0)
	{
		
	}
	else if(ft_strcmp(cmd[1], '~') == 0)
	{
		path = ft_strdup("/home/ylenoel");
		
	}
	
	// if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	// {
	// 	perror("cd: getcwd");
	// 	return -1;
    // }
	// dprintf(2, "cwd : %s\n", current_dir);
	// if(path == NULL || *path == '\0')
	// {
	// 	ft_putstr_fd("CD : Invalid path\n", 2);
	// 	return (-1);
	// }
	// if(ft_strcmp(path, "~") == 0)
	// {
	// 	path = getenv("HOME");
	// 	if(path == NULL)
	// 	{
	// 		ft_putstr_fd("CD : Home isn't set\n", 2);
	// 		return -1;
	// 	}
	// }
	// if(chdir(path) == 1)
	// {	
	// 	perror("cd");
	// 	return (-1);
	// }
	// if (setenv("PWD", path, 1) == -1)
	// {
	// 	perror("cd: setenv\n");
	// 	return (-1);
	// }

	return (0);	
}

void	modify_pwd(t_data *data, char former_dir)
{
	char 	*current_dir;
	char	buffer[1024];

	if(!former_dir)
	{
		
	}
}