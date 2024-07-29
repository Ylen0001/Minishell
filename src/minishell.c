/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/29 18:04:14 by ylenoel          ###   ########.fr       */
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
	s_data.cmds[0] = s_data.v_path.v_cmd[1]->data[0] = "ls";
	s_data.cmds[1] = s_data.v_path.v_cmd[2]->data[0] = "rev";
	// printf("%s\n", s_data.cmds[1]);
	while (init_prompt() && init_signal())
	{
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		launch_parsing(input, &s_data);
		
		add_history(input);
	}
	rl_clear_history();
	while(s_data.cmds[s_data.i])
		free(s_data.cmds[s_data.i]);
	free(s_data.cmds);
	s_data.i = 0;
	return (0);
}