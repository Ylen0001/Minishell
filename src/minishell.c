/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/03 15:55:32 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/colors.h"
#include <stdio.h>
#include <stdlib.h>

volatile int	g_signal_received = 0;

int tmp(char *input, t_data s_data, t_vectstr *env_buff, int *ex_st_buff){
        if (g_signal_received == 2 || check_spaces(input) != 0)
        {
            g_signal_received = 0;
            free_t_data(&s_data);
            return 1;
        }
		// printf("input: %s\n", input);
        if (!input)		
        {
            free_t_data(&s_data);
            free_t_vectstr(env_buff);
            exit(1);
        }
        add_history(input);
        launch_parsing(input, &s_data);
        minishell(&s_data);
        // garbage_collector(&s_data);
        env_buff = vectstr_dup(s_data.vect_env);
        *ex_st_buff = s_data.exit_status; 
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
        s_data = init_data(env, ex_st_buff, *env_buff);
        // char *input = readline(C_LIGHT_ORANGE"minishell: "C_RESET);
        // input = readline("minishell: ");
		if (isatty(STDIN_FILENO))
            input = readline("minishell: ");
		else
		{
            printf("minishell: \n");
            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
                input = ft_strdup(buffer);
        }
		if (!input){
			break;
		}
		
		char **input_list = ft_split(input, '\n');
		for (int i = 0; input_list[i]; i++){
			tmp(input_list[i], s_data, env_buff, &ex_st_buff);
		}
		
		free_charchar(input_list);
		//free input

        // if (isatty(STDIN_FILENO)) {
        // } else {
        //     printf("minishell: \n");
        //     char buffer[1024];
        //     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        //         input = strdup(buffer);
        //     }
        // }
		
    }
	free_t_data(&s_data);
    // garbage_collector(&s_data);
    rl_clear_history();
    return (0);
}


// int main(int argc, char **argv, char **env) 
// {
//     (void)argv;
//     if (argc != 1 || env == NULL || *env == NULL)
//         exit(EXIT_FAILURE);
//     t_data s_data;
//     t_vectstr *env_buff;
//     int ex_st_buff;

//     env_buff = init_vect_str();
//     init_env(env_buff, env);
//     ex_st_buff = 0;
//     char *input = NULL;
//     while (init_signal(S_PROMPT))
//     {
//         input = NULL;
//         rl_event_hook = rl_event_dummy;
//         s_data = init_data(env, ex_st_buff, *env_buff);
//         // char *input = readline(C_LIGHT_ORANGE"minishell: "C_RESET);
        // if (isatty(STDIN_FILENO)) {
        //     input = readline("minishell: ");
        // } else {
        //     printf("minishell: \n");
        //     char buffer[1024];
        //     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        //         input = strdup(buffer);
        //     }
        // }
//         if (g_signal_received == 2 || check_spaces(input) != 0)
//         {
//             g_signal_received = 0;
//             free_t_data(&s_data);
//             continue;
//         }
//         if (!input)		
//         {
//             free_t_data(&s_data);
//             free_t_vectstr(env_buff);
//             exit(1);
//         }
//         add_history(input);
//         launch_parsing(input, &s_data);
//         minishell(&s_data);
//         // garbage_collector(&s_data);
//         env_buff = vectstr_dup(s_data.vect_env);
//         ex_st_buff = s_data.exit_status; 
//         free_t_data(&s_data);
//     }
//     garbage_collector(&s_data);
//     rl_clear_history();
//     return (0);
// }


void	minishell(t_data *data)
{
	size_t it;

	init_data_2(data);
	here_doc_detector(data);
	init_signal(S_EXEC);
	while (data->v_path->size > 0 && data->i_cmd < data->v_path->size)  //  Size = 2
	{
		// sleep(1);
		built_in_detector(data, data->v_path->parsed[data->i_cmd].cmd->data[0]);
		// dprintf(2, "built_in = %zu\n", data->built_in);
		// dprintf(2, "i_cmd = %zu\nsize = %zu\n", data->i_cmd, data->v_path->size);
		// dprintf(2, "cmd = %s\n", data->v_path->parsed[data->i_cmd].cmd->data[0]);
		if(data->v_path->size > 1)
		{
			// printf("BAD\n");
			if (pipe(data->pipefds[data->i_pipes]) == -1)
			{
				perror("");
				ft_putstr_fd("Error : Pipe failed.\n", 2);
				// exit(EXIT_FAILURE);
			}
			data->pipe_trig = 1;
			if(data->v_path->size >= 3 && data->i_pipes >= 2)
			{
				close(data->pipefds[data->i_pipes - 2][0]);
				close(data->pipefds[data->i_pipes - 2][1]);
			}
			data->pids[data->i_cmd] = fork();
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd, data->built_in);
			data->i_pipes++;
		}
		else if(data->i_cmd == 0 && data->built_in == 0 && data->v_path->size == 1)
		{
			// printf("Bad\n");
			data->pids[data->i_cmd] = fork();
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd, data->built_in);
		}
		else
		{
			// dprintf(2, "Hello\n");
			data->old_fdin = dup(STDIN_FILENO);
			data->old_fdout = dup(STDOUT_FILENO);
			child(data, data->i_cmd, data->built_in);
			dup2(data->old_fdin, STDIN_FILENO);
			dup2(data->old_fdout, STDOUT_FILENO);
		}
		// dprintf(2, "SENT BON\n");
		if(data->i_cmd == data->v_path->size - 1 && data->pipe_trig)
		{
			close(data->pipefds[data->i_pipes - 1][0]);
			close(data->pipefds[data->i_pipes - 1][1]);
			close(data->pipefds[data->i_pipes - 2][0]);
			close(data->pipefds[data->i_pipes - 2][1]);
		}
		data->i_cmd++;
		data->built_in = 0;
	}
	it = -1;
	while(++it < data->i_cmd)
	{
		waitpid(data->pids[it], &data->exit_status, 0);
		if(WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		else
			data->exit_status = 1;
	}
	it = -1;
	while(++it < data->hd_count)
		unlink(data->hd_names[it]);
}

void child(t_data *data, size_t it_cmd, int	built_in) 
{
	const 	t_vectstr *cmd = data->v_path->parsed[it_cmd].cmd;
	const 	t_vectint *redir_t = data->v_path->parsed[it_cmd].type;
	const	t_vectstr *redir_f = data->v_path->parsed[it_cmd].redir;
	char 	*path;
	char 	**m_cmd;

	// built_in_detector(data, cmd->data[it_cmd]);
	if (data->i_pipes > 0)
	{
		// dprintf(2, "REDIR IN, i_cmd = %zu\n", it_cmd);
		if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			perror("Dup2: Error\n");
		close(data->pipefds[data->i_pipes - 1][0]);
		close(data->pipefds[data->i_pipes - 1][1]);
	}
	if (it_cmd != data->v_path->size - 1 || (it_cmd == 0 && data->v_path->size >= 2))
	{
		// dprintf(2, "REDIR out\n");
		if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			perror("Dup2: Error\n");
	}
	// printf(C_ORANGE"built_in = %d\n"C_RESET, built_in);
	if(data->pipe_trig)
	{
		close(data->pipefds[data->i_pipes][1]);
		close(data->pipefds[data->i_pipes][0]);
	}
	if(redir_f->size > 0)
		redirections(data, redir_t, redir_f->data);
	if(built_in == 1)
	{
		// dprintf(2, C_YELLOW"ICI\n"C_RESET);
		built_in_manager(data, cmd->data[0]);
		if(data->v_path->size > 1)
			exit(0);
		return;
	}
	else if(built_in == 0)
	{
		m_cmd = ft_split(cmd->data[0], ' ');
		// if(check_file(m_cmd[0]) == NULL)
		// {
		// 	data->exit_status = 1;
		// 	return;
		// }
		if (m_cmd[0] && (access(m_cmd[0], X_OK) == 0 && access(m_cmd[0], F_OK) == 0))
		{
			if(execve(m_cmd[0], m_cmd, data->vect_env->data) == -1)
			{
				perror("execve: Error\n");
				exit(EXIT_FAILURE);
			}
		}
		path = find_path(m_cmd[0], data->vect_env->data);
		// dprintf(2, "path = %s\n", path);
		if(execve(path, m_cmd, data->vect_env->data) == -1)
		{
			perror("");
			ft_putstr_fd("0: command not found\n", 2);
			exit(0);
		}
	}
	return;
}

char	*check_file(char *cmd)
{
	struct stat file_stat;

	if (stat(cmd, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			dprintf(2, "%s: Is a directory\n", cmd);
			return (NULL);
		}
		if (file_stat.st_mode & S_IXUSR){
			return (cmd);
		}
		else
		{
			dprintf(2, "%s: Permission Denied\n", cmd);
			return (NULL);
		}
	}
	else if (there_is_slash(cmd))
	{
		dprintf(2, "%s: No such file or directory\n", cmd);
		return (NULL);
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
			open_file_minishell(data, redir_t->redir_type[it], redir_f[it]);
			if(dup2(data->a_file, STDIN_FILENO) == -1)
			{	
				data->exit_status = 2;
				perror("Dup2: STDIN REDIR failed.\n");
				// exit(2);
			}
			close(data->a_file);
		}
		else if(redir_t->redir_type[it] == HERE_DOC)
		{
			open_file_minishell(data, redir_t->redir_type[it], data->hd_names[hd_it]);
			if(dup2(data->a_file, STDIN_FILENO) == -1)
			{
				data->exit_status = 2;
				// perror("Dup2: HERE_DOC REDIR failed.\n");
				// exit(2);
			}
			close(data->a_file);
			hd_it++;
		}
		else
		{
			open_file_minishell(data, redir_t->redir_type[it], redir_f[it]);
			if(dup2(data->a_file, STDOUT_FILENO) == -1)
			{	
				perror("Dup2: STDOUT REDIR failed.\n");
				// exit(2);
				data->exit_status = 2;
			}
			close(data->a_file);
		}
	}
}



void	open_file_minishell(t_data *data, int type, char *file)
{
	int openFlags = (type == STDOUT_REDIR) * (O_WRONLY | O_CREAT | O_TRUNC);
	openFlags += (type == STDOUT_APPEND) * (O_WRONLY | O_CREAT | O_APPEND);
	openFlags += (type == STDIN_REDIR) * (O_RDONLY);
	openFlags += (type == HERE_DOC) * (O_RDONLY);
	if((type == STDIN_REDIR && access(file, F_OK | W_OK) != -1) || type >= HERE_DOC)
	{
		data->a_file = open(file, openFlags, 0644);
		if (data->a_file == -1)
			perror("Error : file Redir mode opening failed.\n");
		if(data->a_file == 0)
			perror("Error : Open failed\n");
	}
	else
		return;
}
