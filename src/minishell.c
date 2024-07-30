/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/30 17:46:19 by ylenoel          ###   ########.fr       */
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
// 		// mother_forker(&data_test); // T'as la vanne? je l'ai
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
	vectstr_happend(s_data.v_path.parsed[1].cmd, s);
	printf("%s\n", s_data.v_path.parsed[1].cmd->data[0]);
	// int i = 0;
	// while (s_data.v_path.parsed[0].cmd[0].data[i])
	// {
	// 	printf("%s\n", s_data.v_path.parsed[0].cmd[0].data[i]);
	// 	i++;
	// }
	// s_data = init_data(env);
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
	infile_or_heredoc(data, env);
	return;
}


void	infile_or_heredoc(t_data *data, char **env)
{
	data->redir = 0;
	// char ***cmd1 = data->v_path->parsed->cmd.data[0]; 
	// data->cmd[0] = ft_strdup("ls");
	// data->cmd[1] = ft_strdup("-lr");
	// printf("%s\n", data->cmd[0]);
	data->file = ft_strdup("infile");
	printf("%s\n", data->file);
	if (data->redir == STDIN_REDIR)
	{
		infile_case(data, env);
		exec_cmd(data, env);
		return ;
	}
	else
	{
		// here_doc_case(cmd, data);
		// printf("ICI\n");
		return ;
	}
}

void	infile_case(t_data *data, char **env)
{
	if (access(data->file, F_OK | R_OK | W_OK) == -1)
	{
		printf("File : Access Denied.\n");
		// exit(EXIT_FAILURE);
	}
	data->infile = open(data->file, O_RDONLY, 0777);
	if (data->infile == -1)
	{
		close(data->infile);
		// exit(EXIT_FAILURE);
	}
	else
		printf("File : Authorized Access\n");
	exec_cmd(data, env);
	// close(data->infile);
	// garbage_collector(data);
}

void	exec_cmd(t_data *data, char **env)
{
	// char	**cmd;
	char 	*path;
	char 	**m_cmd = malloc(sizeof(char*) * 1);
	
	m_cmd[0] = malloc(sizeof(char) * 10);	
	// cmd = ft_split(data->cmd[0], ' ');
	ft_strlcpy(m_cmd[0], data->v_path.parsed[1].cmd->data[0], 10);
	printf("%s\n", m_cmd[0]);
	path = find_path(m_cmd[0], env);
	// printf("%s\n", data->v_path.parsed[1].cmd->data[0]);
	// printf("cmd = %s\n", cmd[0]);
	dup2(data->infile, STDIN_FILENO);
	// close(data->infile);
	execve(path, m_cmd, env);
	// printf("LA\n");
	// printf("LA\n");
}

