/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/02 19:00:55 by ylenoel          ###   ########.fr       */
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
	char *s = "ls";
	char *s2 = "rev";
	char *s3 = "infile";
	char *s6 = "outfile";
	int	 s4 = 0;
	int	 s5 = 2;
	vectstr_happend(s_data.v_path.parsed[0].cmd, s);
	vectstr_happend(s_data.v_path.parsed[0].cmd, s2);
	vectstr_happend(s_data.v_path.parsed[0].redir, s3);
	vectstr_happend(s_data.v_path.parsed[0].redir, s6);
	vectint_happend(&s_data.v_path.parsed[0].type, s4);
	vectint_happend(&s_data.v_path.parsed[0].type, s5);
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
		s_data.i_parsed++;
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
	// printf("cmd1 = %s, cmd2 = %s\n", data->v_path.parsed[0].cmd->data[0], data->v_path.parsed[0].cmd->data[1]);
	// infile_or_heredoc(data, env);
	while (data->i_cmd < data->v_path.parsed[data->i_parsed].cmd->size)
	{
		// printf("|size %zu|\n", data->v_path.parsed[data->i_parsed].cmd->size);
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
			child(data, data->i_parsed, env);
		data->i_pids++;
		data->i_pipes++;
		data->i_cmd++;
		data->i_redir++;
		data->i_redir_f++;
		// printf("|%zu|\n", data->i_pids);
		// printf("HEY\n");
		while(data->k < data->i_pids - 1)	
		{
			waitpid(data->pids[data->k], NULL, 0);
			data->k++;
			// printf("%zu\n", data->k);
		}
	}
}
	// size_t i = 0;
	// printf("%d\n", data->i_pids)

void child(t_data *data, size_t i_parsed, char **env) 
{
	const 	t_vectstr *cmd = data->v_path.parsed[i_parsed].cmd;
	const 	t_vectint redir_t = data->v_path.parsed[i_parsed].type;
	const	t_vectstr *redir_f = data->v_path.parsed[i_parsed].redir;
	char 	*path;
	char 	**m_cmd;
	
	data->j = 0;
	m_cmd = ft_split(cmd->data[data->i_cmd], ' '); 
	path = find_path(m_cmd[0], env);
	// printf("|Child : I_pids = %zu, i_parsed = %zu, i_pipes = %zu|\n", data->i_pids, i_parsed, data->i_pipes);
	// printf("|i_pids = %zu, nbr_cmd = %zu, i_cmd = %zu|\n", data->i_pids, data->nbr_cmd, data->i_cmd);
	if(data->i_pids != data->i_cmd && data->i_pids > 0) 				// If not last pipe
	{
		dprintf(2, "HEY\n");
		if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDIN\n", 2);
	}
	if(data->i_pids != data->nbr_cmd - 1 && data->i_pids != 1)				// If not first pipe nor last pipe
	{
		if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
			ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
		dprintf(2, "HO\n");
	}
	close(data->pipefds[data->i_pipes][0]);
	close(data->pipefds[data->i_pipes][1]);
	// dprintf(2, "redir_type[0] = %d, i_redir = %zu\n", redir_t.redir_type[data->i_redir], data->i_redir);
	// dprintf(2, "redir_size = %zu\n", redir_t.size);
	// dprintf(2, "redir_f[0] = %s\n", redir_f->data[data->i_redir_f]);
	// dprintf(2, "i_redir = %zu\n", data->i_redir);

	// while(data->j < redir_t.size - 1)
	// {
		dprintf(2, "%s\n", redir_f->data[data->i_redir_f]);
		if(redir_t.redir_type[data->i_redir] == STDIN_REDIR)
		{
			dprintf(2, "LA %zu\n", data->i_pipes);
			open_file_minishell(data, redir_t.redir_type[data->i_redir], redir_f->data[data->i_redir_f]);
			if(dup2(data->infile, STDIN_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDIN REDIR failed.\n", 2);
		}
		else if(redir_t.redir_type[data->i_redir] == STDOUT_REDIR)
		{
			dprintf(2, "ICI %zu \n", data->i_pipes);
			open_file_minishell(data, redir_t.redir_type[data->i_redir], redir_f->data[data->i_redir_f]);
			if(dup2(data->outfile, STDOUT_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDOUT REDIR failed.\n", 2);
		}
		else if(redir_t.redir_type[data->i_redir] == STDOUT_APPEND)
		{
			open_file_minishell(data, redir_t.redir_type[data->i_redir], redir_f->data[data->i_redir_f]);
			if(dup2(data->outfile, STDOUT_FILENO) == -1)
				ft_putstr_fd("Error : Dup2 STDOUT APPEND failed.\n", 2);
		}
	execve(path, m_cmd, env);
}

	
	// dprintf(2,"|%s|\n", cmd->data[data->i_cmd]);
	// if(data->i_pids == 1)
	// {
	// 	dprintf(2, "i_pipes dans P2  = %d\n", data->i_pipes);
	// 	if(dup2(data->outfile, STDOUT_FILENO) == -1)
	// 		ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
	// 	if(dup2(data->pipefds[data->i_pipes - 1][0], STDIN_FILENO) == -1)
	// 		ft_putstr_fd("Error : Dup2 STDIN\n", 2);
	// 	close(data->outfile);
	// 	close(data->infile);
	// 	if(close(data->pipefds[data->i_pipes][0]) == -1)
	// 		ft_putstr_fd("Error : Closing pipe[0]\n", 2);
	// 	close(data->pipefds[data->i_pipes - 1][1]);
	// }
	// close(data->infile);
	// close(data->outfile);
	// if(data->i_pids == 0)
	// {
	// 	if(close(data->pipefds[data->i_pipes][0]) == -1)
	// 		ft_putstr_fd("Error : Closing pipe[0]\n", 2);
	// 	if(dup2(data->infile, STDIN_FILENO) == -1)
	// 		ft_putstr_fd("Error : Dup2 INFILE\n", 2);
	// 	if(dup2(data->pipefds[data->i_pipes][1], STDOUT_FILENO) == -1)
	// 		ft_putstr_fd("Error : Dup2 STDOUT\n", 2);
	// 	if(close(data->pipefds[data->i_pipes][1]) == -1)
	// 		ft_putstr_fd("Error : Closing pipe[1]\n", 2);
	// 	close(data->infile);
	// }
	// cmd->data[0] = find_path(); //ls --> // /usr/ls
	// while (i < redir->size) {
	// 	open(redir->file);
	// 	if (redir->type[i] == APPEND)
	// 		dup2(redir->file);
	// }
	// exec_cmd(data, env, cmd->data[idx]);
void	open_file_minishell(t_data *data, size_t type, char *file)

{
	if(type == STDIN_REDIR)
		infile_case(data, file);	
	else if(type == STDOUT_REDIR)
		outfile_case(data, STDOUT_REDIR, file);
	else if(type == STDOUT_APPEND)
		outfile_case(data, STDOUT_APPEND, file);
	return;
}

void	init_data_2(t_data *data)
{
	size_t	i;
	// const size_t NBR_CMD = data->v_path.size;

	i = 0;
	data->i_redir_f = 0;
	data->i_parsed = 0;
	data->i_cmd = 0;
	data->j = 0;
	data->i_redir = 0;
	data->file = ft_strdup("infile");
	data->file2 = ft_strdup("outfile");
	data->error_nbr = 0;
	data->nbr_cmd = data->v_path.parsed[0].cmd->size;
	data->v_path.parsed[0].type.redir_type[0] = STDIN_REDIR;
	data->v_path.parsed[0].type.redir_type[1] = STDOUT_REDIR;
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
void	outfile_case(t_data *data, int type, char *file)
{
	// data->file = ft_strdup("infile");
	if(type == STDOUT_REDIR)
	{
		if (access(file, F_OK | R_OK | W_OK) == -1)
		{
			ft_putstr_fd("File : Access Denied.\n", 2);
			// exit(EXIT_FAILURE);
		}
		data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->outfile == -1)
		{
			close(data->outfile);
			ft_putstr_fd("Error : Outfile Redir mode opening failed.\n", 2);
			// exit(EXIT_FAILURE);
		}
		else
			ft_putstr_fd("File : Authorized Access\n", 2);
	}
	else if(type == STDOUT_APPEND)
	{
		if (access(file, F_OK | R_OK | W_OK) == -1)
		{
			ft_putstr_fd("File : Access Denied.\n", 2);
			// exit(EXIT_FAILURE);
		}
		data->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (data->outfile == -1)
		{
			ft_putstr_fd("Error : Outfile Append mode opening failed.\n", 2);
			close(data->outfile);
			// exit(EXIT_FAILURE);
		}
		else
			ft_putstr_fd("File : Authorized Access\n", 2);
	}
}

void	infile_case(t_data *data, char *file)
{
	// data->file = ft_strdup("infile");
	if (access(file, F_OK | R_OK | W_OK) == -1)
	{
		ft_putstr_fd("File : Access Denied.\n", 2);
		// exit(EXIT_FAILURE);
	}
	data->infile = open(file, O_RDONLY, 0777);
	if (data->infile == -1)
	{
		ft_putstr_fd("Error : Infile opening failed.\n", 2);
		close(data->infile);
		// exit(EXIT_FAILURE);
	}
	else
		ft_putstr_fd("File : Authorized Access\n", 2);
}

// void	exec_cmd(t_data *data, char **env, char *cmd)
// {
// 	// char	**cmd;
// 	(void) data;
// 	char 	*path;
// 	char 	**m_cmd;
	
	
// 	m_cmd = ft_split(cmd, ' ');
// 	path = find_path(m_cmd[0], env);
// 	// printf("%s\n", data->v_path.parsed[1].cmd->data[0]);
// 	dprintf(2, "cmd = %s\n", path);
// 	execve(path, m_cmd, env);
// 	// printf("LA\n");
// }

