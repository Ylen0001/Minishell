/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/23 17:41:31 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

bool init_prompt() {
	// rl_on_new_line();
	rl_redisplay();
	rl_replace_line("minishell: ", 0);
	return true;
}

void sigint_handler(int sig_code) {
	(void)sig_code;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	// rl_replace_line("minishell: ", 0);
	// rl_on_new_line();
	return ;
}

bool init_signal() {
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	return true;
}

int main(int argc, char **argv, char **env) 
{
	(void)argv;
	if (argc != 1 || env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	while (init_prompt() && init_signal())
	{
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		add_history(input);

		//parsing;
		//exec;
	}

	rl_clear_history();
    return 0;
}