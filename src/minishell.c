/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/07 12:19:17 by ylenoel          ###   ########.fr       */
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
	s_data = init_data(env);
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
		minishell(&s_data);
		// s_data.i_parsed++;
		add_history(input);
	}
	rl_clear_history();
	return (0);
}

void	minishell(t_data *data)
{
	const size_t nbr_cmd = data->v_path.parsed[data->i_parsed].cmd->size;
	
	while (data->i_cmd < nbr_cmd) // ET NON BUILT_IN
	{
		if(nbr_cmd >= 1) // Gestion des pipes.
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
		}
		data->i_pids++; // À vérifier 
		data->i_pipes++;
		data->i_cmd++;
		data->i_redir++;
		data->i_redir_f++;
		while(data->k < data->i_pids - 1)	
		{
			waitpid(data->pids[data->k], NULL, 0);
			data->k++;
		}
	}
}

void child(t_data *data, size_t i_parsed) 
{
	const 	t_vectstr *cmd = data->v_path.parsed[i_parsed].cmd;
	const 	t_vectint *redir_t = data->v_path.parsed[i_parsed].type;
	const	t_vectstr *redir_f = data->v_path.parsed[i_parsed].redir;
	char 	*path;
	char 	**m_cmd;

	data->j = 0;
	

}