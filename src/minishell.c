/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/07 11:54:34 by aberion          ###   ########.fr       */
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
	// s_data = init_data(env);
	while (init_prompt() && init_signal())
	{
		s_data = init_data(env);
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		add_history(input);
		launch_parsing(input, &s_data);
		free_t_data(&s_data);

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
