/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/07 18:35:46 by ylenoel          ###   ########.fr       */
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
		// s_data.i_parsed++;
		free_t_data(&s_data);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_data *data)
{
	init_data_2(data);
	const size_t nbr_cmd = data->v_path.parsed[data->i_parsed].cmd->size;
	data->nbr_cmd = nbr_cmd;
	// printf("cmd size = %zu\n", data->v_path.parsed[data->i_parsed].cmd->size);
	

	// printf("cmd = %zu\n", data->nbr_cmd);
	while (data->i_cmd < nbr_cmd)
	{
		dprintf(2, "while enfant num: %zu\n", data->i_cmd);
		if(nbr_cmd > 1 || (nbr_cmd == 1 && data->built_in == 0)) // Si + d'une cmd OÙ 1 seule cmd NON BUILT-IN
		{
			if (pipe(data->pipefds[data->i_pipes]) == -1)
			{
				ft_putstr_fd("Error : Pipe failed.\n", 2);
				exit(EXIT_FAILURE);
			}
			if(data->i_pipes >= 2)  // Fermeture des pipes qui ne sont plus utilisés
			{
				close(data->pipefds[data->i_pipes - 2][0]);
				close(data->pipefds[data->i_pipes - 2][0]);
			}
			data->pids[data->i_pids] = fork(); // Création process enfant
			if (data->pids[data->i_pids] == -1) 
				ft_putstr_fd("Error : Fork Failed\n", 2);
			if (data->pids[data->i_pids] == 0)
				child(data, data->i_parsed);
			data->i_pids++; 
		}
		else												// IF une seule cmd ET c'est un BUILT-IN
			child(data, data->i_parsed);
		data->i_pipes++;
		data->i_parsed++;
		data->i_cmd++;
		// data->i_redir++;
		// data->i_redir_f++;
		while(data->k < data->i_pids)	
		{
			// dprintf(2, "while waitpid num: %zu\n", data->k);
			waitpid(data->pids[data->k], NULL, 0);
			data->k++;
		}
		data->k = 0;
		// nbr_cmd++;
	}
		// printf("BONJOUR\n");
}

void child(t_data *data, size_t i_parsed) 
{
	const 	t_vectstr *cmd = data->v_path.parsed[i_parsed].cmd;
	const 	t_vectint *redir_t = data->v_path.parsed[i_parsed].type;
	const	t_vectstr *redir_f = data->v_path.parsed[i_parsed].redir;
	char 	*path;
	char 	**m_cmd;

	data->j = 0;
	data->nbr_cmd = cmd->size;
	m_cmd = ft_split(cmd->data[data->i_cmd], ' '); 
	path = find_path(m_cmd[0], data->vect_env->data);
	// printf("cmd = %s\n", m_cmd[0]);
	// dprintf(2, "data->nbr_cmd = %zu\n", data->nbr_cmd);
	// dprintf(2, "redir_type[0] = %d\n", redir_t->redir_type[data->i_redir]);
	// dprintf(2, "redir_size = %zu\n", redir_t->size);
	// dprintf(2, "redir_f[0] = %s\n", redir_f->data[data->i_redir_f]);
	// printf("|Child : I_pids = %zu, i_parsed = %zu, i_pipes = %zu|\n", data->i_pids, i_parsed, data->i_pipes);
	// printf("|i_pids = %zu, nbr_cmd = %zu, i_cmd = %zu|\n", data->i_pids, data->nbr_cmd, data->i_cmd);
	if (data->i_pids > 0) 							// If not first pipe [ENTRE LES DEUX]
	{
		dprintf(2, "HELLO\n");
		if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDIN\n", 2);
		close(data->pipefds[data->i_pipes - 1][0]);
		close(data->pipefds[data->i_pipes - 1][1]);
	}
	if (data->i_pids != data->nbr_cmd)			   // If not last pipe [ENTRE LES DEUX]
	{
		dprintf(2, "ICI\n");
		if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
	}
	redirections(data, redir_t, redir_f->data);
	// dprintf(2, "HI\n");
	// close(data->pipefds[data->i_pipes][1]);
	// close(data->pipefds[data->i_pipes][0]);
	
	execve(path, m_cmd, data->vect_env->data);
	perror("Fatal error: ");
}

void	redirections(t_data *data, const struct s_vectint *redir_t, char **redir_f)
{
	while(redir_t->size > 0 && data->i_redir_t < redir_t->size)
	{
	// dprintf(2, "redir_type = %d, i_redir_t = %zu, redir_t size = %zu\n", redir_t->redir_type[data->i_redir_t], data->i_redir_t, redir_t->size);
		if(redir_t->redir_type[data->i_redir_t] == STDIN_REDIR)
		{
			open_file_minishell(data, redir_t->redir_type[data->i_redir_t], redir_f[data->i_redir_f]);
			dprintf(2,"STDIN file = %s, fd out = %d\n", redir_f[data->i_redir_f], data->outfile);
			dprintf(2, "infile = %d\n", data->outfile);
			if(dup2(data->infile, STDIN_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDIN REDIR failed.\n", 2);
			close(data->infile);
		}
		else // STDOUT_REDIR où STDOUT_APPEND
		{
			open_file_minishell(data, redir_t->redir_type[data->i_redir_t], redir_f[data->i_redir_f]);
			dprintf(2,"|||pid = %zu, STDOUT file = %s, fd out = %d,\n", data->i_pids, redir_f[data->i_redir_f], data->outfile);
			dprintf(2, "outfile = %d\n", data->outfile);
			if(dup2(data->outfile, STDOUT_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDOUT REDIR failed.\n", 2);
			close(data->outfile);
		}
		data->i_redir_t++;
		data->i_redir_f++;
	}
	return ;
}
	// printf("path = %s\n", path);

void	open_file_minishell(t_data *data, size_t type, char *file)
{
	dprintf(2, "type redir = %zu\n", type);
	if(type == STDIN_REDIR)
		infile_case(data, file);	
	else if(type == STDOUT_REDIR)
		outfile_case(data, STDOUT_REDIR, file);
	else if(type == STDOUT_APPEND)
		outfile_case(data, STDOUT_APPEND, file);
	dprintf(2, "|infile = %d\n", data->infile);
	dprintf(2, "|outfile = %d\n", data->outfile);
	return;
}

void	outfile_case(t_data *data, int type, char *file)
{
	if(type == STDOUT_REDIR)
	{
		if (access(file, F_OK) == -1 && access(file, W_OK) == -1)
		{
			ft_putstr_fd("File : Access Denied.\n", 2);
			// exit(EXIT_FAILURE);
		}
		data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile == -1)
		{
			ft_putstr_fd("Error : Outfile Redir mode opening failed.\n", 2);
			// exit(EXIT_FAILURE);
		}
		else
			ft_putstr_fd("File : Authorized AccessA\n", 2);
		// dprintf(2, "outfile = %d\n", data->outfile);
	}
	else if(type == STDOUT_APPEND)
	{
		if (access(file, F_OK | R_OK | W_OK) == -1)
		{
			ft_putstr_fd("File : Access Denied.\n", 2);
			// exit(EXIT_FAILURE);
		}
		data->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->outfile == -1)
		{
			ft_putstr_fd("Error : Outfile Append mode opening failed.\n", 2);
			// exit(EXIT_FAILURE);
		}
		else
			ft_putstr_fd("File : Authorized Access\n", 2);
	}
}

void	infile_case(t_data *data, char *file)
{
	// dprintf(2, "file = %s\n", file);
	if (access(file, F_OK | R_OK) == -1)
	{
		ft_putstr_fd("File : Access Denied.\n", 2);
		// exit(EXIT_FAILURE);
	}
	data->infile = open(file, O_RDONLY, 0777);
	if (data->infile == -1)
	{
		ft_putstr_fd("Error : Infile opening failed.\n", 2);
		// exit(EXIT_FAILURE);
	}
	else
		ft_putstr_fd("File : Authorized Access\n", 2);
	// dprintf(2, "infile = %d\n", data->infile);
}