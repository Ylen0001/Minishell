/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/01 18:01:10 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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
		// mother_forker(&data_test); // T'as la vanne? je l'ai
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
	s_data = init_data(env);
	char *s = "cat";
	char *s2 = "rev";
	vectstr_happend(s_data.v_path.parsed[0].cmd, s);
	vectstr_happend(s_data.v_path.parsed[0].cmd, s2);
	init_data_2(&s_data);
	// vectstr_print(s_data.v_path.parsed[0].cmd);
	// printf("%s\n", s_data.v_path.parsed[1].cmd->data[0]);
	// printf("%zu\n", s_data.v_path.parsed[1].cmd->size);
	while (init_prompt() && init_signal())
	{
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		// launch_parsing(input, &s_data);
		minishell(&s_data, env);
		add_history(input);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_data *data, char **env)
{
	// size_t	j;
	(void) env;
	
	// j = 0;
	data->k = 0;
	// infile_case(data, env);
	// printf("cmd1 = %s, cmd2 = %s\n", data->v_path.parsed[0].cmd->data[0], data->v_path.parsed[0].cmd->data[1]);
	// infile_or_heredoc(data, env);
	while (data->k < data->v_path.parsed[0].cmd->size)
	{
		// printf("Tour %zu\n", data->i);
		if (pipe(data->pipefds[data->i_pipes]) == -1)
		{
			// perror("");
			ft_putstr_fd("Error : Pipe failed.\n", 2);
			exit(EXIT_FAILURE);
		}
		if(data->i_pipes >= 2)  // Fermeture des pipes qui ne sont plus utilisés
		{
			close(data->pipefds[data->i_pipes - 2][0]);
			close(data->pipefds[data->i_pipes - 2][0]);
		}	
		// data->i_pipes++;
		data->pids[data->i_pids] = fork();
		if (data->pids[data->i_pids] == -1)
		{
			// free(data->pipefds);
			ft_putstr_fd("Error : Fork Failed\n", 2);
		}
		if (data->pids[data->i_pids] == 0)
		{
			child(data, data->i, env);
		}
		else
		{
			while(data->j < data->v_path.parsed[0].cmd->size)	
			{
				waitpid(data->pids[data->i_pids], NULL, 0);
				data->i_pids--;
				data->j++;
			}
		}
		data->i_pids++;
		data->i_pipes++;
		data->k++;
	}
}
	// size_t i = 0;
	// printf("%d\n", data->i_pids)

void child(t_data *data, size_t idx, char **env) 
{
	// printf(" idx = %zu\n", idx);
	const t_vectstr *cmd = data->v_path.parsed[idx].cmd;
	// const t_vectint redir_t = data->v_path.parsed[idx].type;
	printf("BONJOUR %zu\n", data->i_pids);
	if(data->i_pids != 0)
		close(data->pipefds[data->i_pipes - 1][1]);
	close(data->pipefds[data->i_pipes][0]);
	if(data->i_pids != data->nbr_cmd) 									// If not last pipe
		if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
	if(data->i_pids != 0) 												// If not first pipe
		if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDIN\n", 2);
	if(data->i_pids == 0)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	printf("%s\n", cmd->data[0]);
	// if(data->i_pids == 0)
	// 	infile_case(data, env);
	exec_cmd(data, env, cmd->data[idx]);


	
	// cmd->data[0] = find_path(); //ls --> // /usr/ls
	// while (i < redir->size) {
	// 	open(redir->file);
	// 	if (redir->type[i] == APPEND)
	// 		dup2(redir->file);
	// }
	// exec_cmd(data, env, cmd->data[idx]);
}

void	init_data_2(t_data *data)
{
	size_t	i;
	// const size_t NBR_CMD = data->v_path.size;

	i = 0;
	data->file = ft_strdup("infile");
	data->error_nbr = 0;
	data->nbr_cmd = data->v_path.parsed[0].cmd->size;
	data->v_path.parsed[0].type.redir_type[0] = STDIN_REDIR;
	data->redir = data->v_path.parsed[0].type.redir_type[0];
	data->cmds = malloc(sizeof(char *) * 2);
	while(i < data->nbr_cmd)
	{
		data->cmds[i] = ft_strdup(data->v_path.parsed[0].cmd->data[i]);	
		i++;
	}
	// printf("%s\n", data->cmds[1]);
	// printf("redir = %d\n", data->redir);
	// printf("cmds = %zu\n", data->nbr_cmd);
	i = 0;
	data->pipefds = ft_calloc( data->nbr_cmd, sizeof(int *));
	while (i < data->nbr_cmd)
		data->pipefds[i++] = ft_calloc(2, sizeof(int));
	if (!data->pipefds)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	// printf("%zu\n", data->nbr_cmd);
	data->pids = malloc(data->nbr_cmd * sizeof(pid_t) + 1);
	if (data->pids == NULL)
	{
		ft_putstr_fd("Pid malloc failed\n", 2);
		free(data->pids);
		exit(EXIT_FAILURE);
	}
	data->i_pipes = 0;
	data->i_pids = 0;
	return ;
}

// void	infile_or_heredoc(t_data *data, char **env)
// {
// 	// char ***cmd1 = data->v_path->parsed->cmd.data[0]; 
// 	// data->cmd[0] = ft_strdup("ls");
// 	// data->cmd[1] = ft_strdup("-lr");
// 	// printf("%s\n", data->cmd[0]);
	// data->file = ft_strdup("infile");
// 	// printf("%s\n", data->file);
// 	if (data->redir == STDIN_REDIR)
// 	{
// 		infile_case(data, env);
// 		exec_cmd(data, env);
// 		return ;
// 	}
// 	else
// 	{
// 		// here_doc_case(cmd, data);
// 		// printf("ICI\n");
// 		return ;
// 	}
// }

void	infile_case(t_data *data, char **env)
{
	(void) env;
	data->file = ft_strdup("infile");
	if (access(data->file, F_OK | R_OK | W_OK) == -1)
	{
		ft_putstr_fd("File : Access Denied.\n", 2);
		// exit(EXIT_FAILURE);
	}
	data->infile = open(data->file, O_RDONLY, 0777);
	if (data->infile == -1)
	{
		close(data->infile);
		// exit(EXIT_FAILURE);
	}
	else
		ft_putstr_fd("File : Authorized Access\n", 2);
	// exec_cmd(data, env);
	// close(data->infile);
	// garbage_collector(data);
}

void	exec_cmd(t_data *data, char **env, char *cmd)
{
	// char	**cmd;
	(void) data;
	char 	*path;
	char 	**m_cmd;
	
	
	m_cmd = ft_split(cmd, ' ');
	// ft_strlcpy(m_cmd[0], data->v_path.parsed[1].cmd->data[0], 10);
	// printf("%s\n", m_cmd[1]);
	path = find_path(m_cmd[0], env);
	// printf("%s\n", data->v_path.parsed[1].cmd->data[0]);
	// printf("cmd = %s\n", cmd[0]);
	// dup2(data->infile, STDIN_FILENO);
	// close(data->infile);
	execve(path, m_cmd, env);
	// printf("LA\n");
	// printf("LA\n");
}

