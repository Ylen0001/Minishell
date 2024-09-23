/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/20 10:51:53 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_signal_received = 0;

int tmp(char *input, t_data *s_data, t_vectstr *env_buff, int *ex_st_buff)
{
        if (g_signal_received == 2 || check_spaces(input) != 0)
        {
            g_signal_received = 0;
            free_t_data(s_data, 1);
            return 1;
        }
        if (!input)		
        {
            free_t_data(s_data, 0);
            free_t_vectstr(env_buff);
            return 42;
        }
        add_history(input);
        launch_parsing(input, s_data);
        minishell(s_data);
        // garbage_collector(&s_data);
        env_buff = s_data->vect_env;
        *ex_st_buff = s_data->exit_status; 
	return (0);
}


void free_charchar(char **s){
	int i;
	
	i = 0;
	while(s[i]){
		free(s[i]);
		i++;
	}
	free(s);
}

int main(int argc, char **argv, char **env) 
{
	// char **input_list;
    (void)argv;
    if (argc != 1 || env == NULL || *env == NULL)
        exit(EXIT_FAILURE);
    t_data s_data;
    t_vectstr *env_buff;
    int ex_st_buff;

    env_buff = init_vect_str();
    init_env(env_buff, env);
    ex_st_buff = 0;
    char *input = NULL;
    while (init_signal(S_PROMPT))
    {
        input = NULL;
        rl_event_hook = rl_event_dummy;
        s_data = init_data(env, ex_st_buff, env_buff);
		if (isatty(STDIN_FILENO))
            input = readline("minishell: ");
		else
		{
			ssize_t bytes_read = 0;
			size_t len = 0;
			char buffer[2] = {0}; // Used to store the character read
			char *line = calloc(1024, sizeof(char)); // Allocate memory for the line
				
			if (line == NULL)
			{
				free_t_data(&s_data, 0);
				perror("calloc");
				return 1;
			}
			while ((bytes_read = read(STDIN_FILENO, buffer, 1)) > 0) {
				line[len++] = buffer[0];
			if (buffer[0] == '\n' || buffer[0] == '\0') 
				break;
			}
			if (bytes_read < 0 || strlen(line) == 0)
			{
				input = NULL;
				break;
			}
			line[len] = '\0';
			if (strlen(line) > 0)
				input = line;
			else
			{ 
				input = NULL;
				break;
			}
			ft_putstr_fd("minishell: \n", STDOUT_FILENO);
        }
		if (!input)
		{
			break;
		}
		char **input_list = ft_split(input, '\n');
		for (int i = 0; input_list[i]; i++)
		{
			if (tmp(input_list[i], &s_data, env_buff, &ex_st_buff) == 42)
			{
				free_charchar(input_list);
				exit(1);
			}
		}
		free_charchar(input_list);
		free_t_vector(s_data.v_path);
		s_data.v_path = NULL;
    }
	free_t_data(&s_data, 0);
    // garbage_collector(&s_data);
    rl_clear_history();
    return (0);
}

char	*check_file(t_data *data, char *cmd)
{
	struct stat file_stat;

	if (stat(cmd, &file_stat) != -1) // Si relatif (Est-ce que la cmd existe)
	{
		if (there_is_slash(cmd) && S_ISDIR(file_stat.st_mode))
		{
			ft_putstr_fd(" Is a directory\n", 2);
			data->exit_status = 126;
			builtin_exit(data, NULL);
		}
		if (file_stat.st_mode & S_IXUSR){
			return (cmd);
		}
		else if(access(cmd, X_OK) == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			data->exit_status = 126;
			builtin_exit(data, NULL);
		}
		else
		{
			ft_putstr_fd(" command not found\n", 2);
			data->exit_status = 127;
			builtin_exit(data, NULL);
		}
	}
	else if(there_is_slash(cmd)) // Si absolu
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		data->exit_status = 127;
		builtin_exit(data, NULL);
	}
	return (NULL);
}

int		there_is_slash(char *cmd)
{
	size_t i;

	i = 0;
	while(cmd[i])
	{
		if(cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	redirections(t_data *data, const struct s_vectint *redir_t, char **redir_f)
{
	size_t it;
	size_t hd_it;

	it = -1;
	hd_it = 0;
	while(++it < redir_t->size)
	{
		if(redir_t->redir_type[it] == STDIN_REDIR)
		{
			if(open_file_minishell(data, redir_t->redir_type[it], redir_f[it]) == 0)
			{
				builtin_exit(data, NULL);
				return;
			}
			if(dup2(data->a_file, STDIN_FILENO) == -1)
			{	
				data->exit_status = 0;
				ft_putstr_fd("Dup2: STDIN REDIR failed.\n", 2);
			}
			close(data->a_file);
		}
		else if(redir_t->redir_type[it] == HERE_DOC)
		{
			if(open_file_minishell(data, redir_t->redir_type[it], data->hd_names[hd_it]) == 0)
				return;
			if(dup2(data->a_file, STDIN_FILENO) == -1)
			{
				data->exit_status = 2;
				ft_putstr_fd("Dup2: HERE_DOC REDIR failed.\n", 2);
			}
			close(data->a_file);
			hd_it++;
		}
		else
		{
			if(open_file_minishell(data, redir_t->redir_type[it], redir_f[it]) == 0)
				return;
			if(dup2(data->a_file, STDOUT_FILENO) == -1)
			{	
				ft_putstr_fd("Dup2: STDOUT REDIR failed.\n", 2);
				data->exit_status = 2;
			}
			close(data->a_file);
		}
	}
}



int	open_file_minishell(t_data *data, int type, char *file)
{
	int openFlags = (type == STDOUT_REDIR) * (O_WRONLY | O_CREAT | O_TRUNC);
	openFlags += (type == STDOUT_APPEND) * (O_WRONLY | O_CREAT | O_APPEND);
	openFlags += (type == STDIN_REDIR) * (O_RDONLY);
	openFlags += (type == HERE_DOC) * (O_RDONLY);
	if((type == STDIN_REDIR && access(file, F_OK | R_OK) != -1) || type >= HERE_DOC)
	{
		// dprintf(2, "file = %s\n", file);
		data->a_file = open(file, openFlags, 0644);
		if (data->a_file == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			data->exit_status = 1;
			builtin_exit(data, NULL);
		}
		if(data->a_file == 0)
			ft_putstr_fd("Error : Open failed\n", 2);
		return (1);
	}
	else
	{
		data->exit_status = 1;
		return (0);
	}
}
