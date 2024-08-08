/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/08 17:08:21 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char **argv, char **env) 
// {
// 	(void)argv;
// 	if (argc != 1 || env == NULL || *env == NULL)
// 		exit(EXIT_FAILURE);
// 	t_data s_data;
// 	s_data = init_data(env);
// 	//int i = 0;
// 	// while (s_data.v_path.v_cmd[0]->data[i])
// 	// {
// 	// 	printf("%s\n", s_data.v_path.v_cmd[0]->data[i]);
// 	// 	// printf("%d\n", i);
// 	// 	i++;
// 	// }
// 	while (init_prompt() && init_signal())
// 	{
// 		char *input = readline("minishell: ");
// 		if (!input)
// 			exit(1);
// 		launch_parsing(input, &s_data);
// 		// data_test.full_string = input;
// 		add_history(input);

// 		//parsing
// 		//exec
// 		// TEST //
// 		// infile_check(&data_test);
// 		mother_forker(&data_test); // T'as la vanne? je l'ai
// 	}
// 	// add_history(input);
// 	//parsing;
// 	//exec;
// 	rl_clear_history();
//     return 0;
// }


int	main(int argc, char *argv[], char *env[])
{
	(void)argv;
	if (argc != 1 || env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	t_data s_data;
	// s_data = init_data(env);
	// s_data = init_data(env);
	// vectstr_print(s_data.v_path.parsed[0].cmd);
	// printf("%s\n", s_data.v_path.parsed[1].cmd->data[0]);
	// printf("%zu\n", s_data.v_path.parsed[1].cmd->size);
	while (init_prompt() && init_signal())
	{
		s_data = init_data(env);
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		add_history(input);
		launch_parsing(input, &s_data);
		minishell(&s_data);
		// s_data.i_cmd++;
		free_t_data(&s_data);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_data *data)
{
	size_t it;
	
	it = -1;
	init_data_2(data);
	data->nbr_cmd = data->v_path.parsed[data->i_cmd].cmd->size;
	data->nbr_input = data->v_path.size;
	// printf("cmd size = %zu, nbr_input = %zu\n", data->v_path.parsed[data->i_cmd].cmd->size, data->nbr_input);
	// printf("cmd = %zu\n", data->nbr_cmd);
	here_doc_detector(data);
	while (data->i_cmd < data->nbr_cmd)
	{
		if(data->nbr_cmd > 1) // Si + d'une cmd OÙ 1 seule cmd NON BUILT-IN
		{
			if (pipe(data->pipefds[data->i_cmd]) == -1)
			{
				ft_putstr_fd("Error : Pipe failed.\n", 2);
				exit(EXIT_FAILURE);
			}
			if(data->i_cmd >= 2)  // Fermeture des pipes qui ne sont plus utilisés
			{
				close(data->pipefds[data->i_cmd - 2][0]);
				close(data->pipefds[data->i_cmd - 2][0]);
			}
			data->pids[data->i_cmd] = fork(); // Création process enfant
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd);
		}
		else if(data->nbr_cmd == 1 && data->built_in == 0)
		{
			data->pids[data->i_cmd] = fork(); // Création process enfant
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd);
		}
		else												// IF une seule cmd ET c'est un BUILT-IN
			child(data, data->i_cmd);
		data->i_cmd++;
		// dprintf(2, "Main : data->nbr_cmd = %zu, i_cmd = %zu\n", data->nbr_cmd, data->i_cmd);

	}
		while(++it < data->nbr_cmd)
			waitpid(data->pids[it], NULL, 0);
		// printf("BONJOUR\n");
}

void child(t_data *data, size_t i_cmd) 
{
	const 	t_vectstr *cmd = data->v_path.parsed[i_cmd].cmd;
	const 	t_vectint *redir_t = data->v_path.parsed[i_cmd].type;
	const	t_vectstr *redir_f = data->v_path.parsed[i_cmd].redir;
	char 	*path;
	char 	**m_cmd;

	data->j = 0;
	// data->nbr_cmd = cmd->size;
	m_cmd = ft_split(cmd->data[data->i_cmd], ' '); 
	path = find_path(m_cmd[0], data->vect_env->data);
	// printf("cmd = %s\n", m_cmd[0]);
	// dprintf(2, "Child : data->nbr_cmd = %zu, i_cmd = %zu\n", data->nbr_cmd, data->i_cmd);
	if (data->i_cmd > 0) 							// If not first pipe [ENTRE LES DEUX]
	{
		// dprintf(2, "HELLO\n");
		if(dup2(data->pipefds[data->i_cmd - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDIN\n", 2);
		close(data->pipefds[data->i_cmd - 1][0]);
		close(data->pipefds[data->i_cmd - 1][1]);
	}
	if (data->i_cmd != data->nbr_cmd)			   // If not last pipe [ENTRE LES DEUX]
	{
		if(dup2(data->pipefds[data->i_cmd][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
		close(data->pipefds[data->i_cmd][1]);
	}
	if(redir_f->size > 0)
		redirections(data, redir_t, redir_f->data);
	// dprintf(2, "HI\n");
	// close(data->pipefds[data->i_cmd][1]);
	
	execve(path, m_cmd, data->vect_env->data);
	// perror("Fatal error: ");
}

void	redirections(t_data *data, const struct s_vectint *redir_t, char **redir_f)
{
	size_t it;
	size_t hd_it;

	it = -1;
	hd_it = 0;
	while(++it < redir_t->size)
	{
	// dprintf(2, "redir_type = %d, i_redir_t = %zu, redir_t size = %zu\n", redir_t->redir_type[it], it, redir_t->size);
		if(redir_t->redir_type[it] == STDIN_REDIR)
		{
			open_file_minishell(data, redir_t->redir_type[it], redir_f[it]);
			// dprintf(2,"STDIN file = %s, fd out = %d\n", redir_f[it], data->outfile);
			// dprintf(2, "infile = %d\n", data->outfile);
			if(dup2(data->a_file, STDIN_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDIN REDIR failed.\n", 2);
			close(data->a_file);
		}
		else if(redir_t->redir_type[it] == HERE_DOC)
		{
			open_file_minishell(data, redir_t->redir_type[it], data->hd_names[hd_it]);
			hd_it++;
		}
		else // STDOUT_REDIR où STDOUT_APPEND
		{
			open_file_minishell(data, redir_t->redir_type[it], redir_f[it]);
			// dprintf(2,"|||pid = %zu, STDOUT file = %s, fd out = %d,\n", data->i_cmd, redir_f[it], data->outfile);
			// dprintf(2, "outfile = %d\n", data->outfile);
			if(dup2(data->a_file, STDOUT_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDOUT REDIR failed.\n", 2);
			close(data->a_file);
		}
	}
}
		// }
void	open_file_minishell(t_data *data, int type, char *file)
{
	int openFlags = (type == STDOUT_REDIR) * (O_WRONLY | O_TRUNC | O_CREAT);
	openFlags += (type == STDOUT_APPEND) * (O_WRONLY | O_CREAT | O_APPEND);
	openFlags += (type == STDIN_REDIR) * (O_RDONLY);
	openFlags += (type == HERE_DOC) * (O_RDONLY);
	if (access(file, F_OK | W_OK) != -1)
	{
		data->a_file = open(file, openFlags, 0644);
		if (data->a_file == -1)
			ft_putstr_fd("Error : file Redir mode opening failed.\n", 2);
	}
	else
		ft_putstr_fd("File : Access Denied.\n", 2);
}