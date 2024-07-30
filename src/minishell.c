/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/30 15:54:18 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int main(int argc, char **argv, char **env) 
{
	(void)argv;
	if (argc != 1 || env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	t_data s_data;
	s_data = init_data(env);
	// int i = 0;
	// while (s_data.v_path.parsed[0].cmd[0].data[i])
	// {
	// 	printf("%s\n", s_data.v_path.parsed[0].cmd[0].data[i]);
	// 	i++;
	// }
	while (init_prompt() && init_signal())
	{
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		launch_parsing(input, &s_data);
		
		add_history(input);

		//parsing
		//exec
		// TEST //
		// infile_check(&data_test);
		// mother_forker(&data_test); // T'as la vanne? je l'ai
	}
	// add_history(input);
	//parsing;
	//exec;
	rl_clear_history();
    return 0;
}
