/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:44:22 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/03 14:45:51 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_exec(int sig_code)
{
	g_signal_received = sig_code;
	rl_replace_line("", 0);
	rl_done = 1;
	rl_redisplay();
	return ;
}

void	sigint_handler(int sig_code)
{
	g_signal_received = sig_code;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
	rl_redisplay();
	return ;
}

void	handle_sigquit(int sig_code)
{
	(void)sig_code;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	g_signal_received = 0;
	rl_done = 1;
}
