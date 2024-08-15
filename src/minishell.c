/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/15 16:02:20 by aberion          ###   ########.fr       */
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
	setup_signal_handlers();
	while (init_prompt() && init_signal())
	{
		s_data = init_data(env);
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		add_history(input);
		if (g_signal_received)
        {
        	if (g_signal_received == SIGINT)
            {
				g_signal_received = 0;
				write(1, "\n", 1);
			}
			else if (g_signal_received == SIGQUIT)
			{
				g_signal_received = 0;
			}
		}
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
