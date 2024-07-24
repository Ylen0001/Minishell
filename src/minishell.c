/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 11:03:08 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main() 
{
	char	*input;
	while (init_prompt() && init_signal())
	{
		input = readline("minishell: ");
		if (!input)
		{
			printf("exit\n");
			exit(1);
		}
	}
	add_history(input);
	//parsing;
	//exec;
	rl_clear_history();
    return (0);
}