/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/16 16:42:44 by ylenoel          ###   ########.fr       */
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
	while (init_prompt() && init_signal())
	{
		s_data = init_data(env);
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		add_history(input);
		launch_parsing(input, &s_data);
		minishell(&s_data);
		// garbage_collector(&s_data);
		free_t_data(&s_data);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_data *data)
{
	size_t it;
	
	init_data_2(data);
	here_doc_detector(data);
	while (data->v_path->size > 0 && data->i_cmd < data->v_path->size) // while(data->i_cmd < data->nbr_cmd)
	{
		if(data->v_path->size > 1) // Si + d'une cmd
		{
			if (pipe(data->pipefds[data->i_pipes]) == -1)
			{
				perror("");
				ft_putstr_fd("Error : Pipe failed.\n", 2);
				// exit(EXIT_FAILURE);
			}
			if(data->v_path->size >= 3 && data->i_cmd >= 3)  // Fermeture des pipes qui ne sont plus utilisés
			{
				// dprintf(2, "PAS OK\n");
				close(data->pipefds[data->i_pipes - 2][0]);
				close(data->pipefds[data->i_pipes - 2][1]);
			}
			data->pids[data->i_cmd] = fork(); // Création process enfant
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd);
			close(data->pipefds[data->i_pipes][1]); // Celui là est important.
		}
		else if(data->i_cmd == 0 && data->built_in == 0 && data->v_path->size == 1)
		{
			// dprintf(2, "ICI\n");		// IF une seule cmd ET c'est un BUILT-IN
			data->pids[data->i_cmd] = fork(); // Création process enfant
			if (data->pids[data->i_cmd] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_cmd] == 0)
				child(data, data->i_cmd);
		}
		else
			child(data, data->i_cmd);
		// close(data->pipefds[data->i_pipes][0]);
		data->i_cmd++;
		data->i_pipes++;
	}
	it = -1;
	while(++it < data->i_cmd)
		waitpid(data->pids[it], NULL, 0);
	it = -1;
	while(++it < data->hd_count)
		unlink(data->hd_names[it]);
}

void child(t_data *data, size_t it_cmd) 
{
	const 	t_vectstr *cmd = data->v_path->parsed[it_cmd].cmd;
	const 	t_vectint *redir_t = data->v_path->parsed[it_cmd].type;
	const	t_vectstr *redir_f = data->v_path->parsed[it_cmd].redir;
	char 	*path;
	char 	**m_cmd;


	
	if (data->i_pipes > 0) 							// If not first pipe [ENTRE LES DEUX]
	{
		if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDIN\n", 2);
		close(data->pipefds[data->i_pipes - 1][0]);
		close(data->pipefds[data->i_pipes - 1][1]);
	}
	if (it_cmd != data->v_path->size - 1 || (it_cmd == 0 && data->v_path->size >= 2))			   // If first pipe? Donc i_cmd = 0 et la size est au moins de 2.
	{
		if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
		close(data->pipefds[data->i_pipes][1]);
		close(data->pipefds[data->i_pipes][0]);
	}
	if(redir_f->size > 0)
		redirections(data, redir_t, redir_f->data);
	close(data->pipefds[data->i_pipes][1]);
	close(data->pipefds[data->i_pipes][0]);
	m_cmd = ft_split(cmd->data[0], ' ');
	if (m_cmd[0] && (access(m_cmd[0], X_OK) == 0 && access(m_cmd[0], F_OK) == 0))
	{
		// dprintf(2, "Bonjour\n");
		execve(m_cmd[0], m_cmd, data->vect_env->data);
	}
	// dprintf(2, "cmd = %s", cmd->data[0]);
	path = find_path(m_cmd[0], data->vect_env->data);
	// else
	// {
	execve(path, m_cmd, data->vect_env->data);
	perror("");
	// }
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
				ft_putstr_fd("Error : Dup2 STDIN REDIR failed.\n", 2);
			close(data->a_file);
		}
		else if(redir_t->redir_type[it] == HERE_DOC)
		{
			open_file_minishell(data, redir_t->redir_type[it], data->hd_names[hd_it]);
			if(dup2(data->a_file, STDIN_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 HERE_DOC failed.\n", 2);
			close(data->a_file);
			hd_it++;
		}
		else // STDOUT_REDIR où STDOUT_APPEND
		{
			open_file_minishell(data, redir_t->redir_type[it], redir_f[it]);
			if(dup2(data->a_file, STDOUT_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDOUT REDIR failed.\n", 2);
			close(data->a_file);
		}
	}
}
		// }
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
			ft_putstr_fd("Error : file Redir mode opening failed.\n", 2);
		if(data->a_file == 0)
			ft_putstr_fd("Open a foiré!\n", 2);
	}
	else
		ft_putstr_fd("File : Access Denied.\n", 2);
}