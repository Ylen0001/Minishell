/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:47:51 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 10:57:29 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	init_prompt()
{
	rl_redisplay();
	rl_replace_line("minishell: ", 0);
	return (true);
}

void	sigint_handler(int sig_code)
{
	(void)sig_code;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return;
}

bool	init_signal()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	return (true);
}