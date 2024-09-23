/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:47:51 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/17 13:48:52 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	g_signal_received;

bool	init_prompt()
{
	rl_redisplay();
	rl_replace_line("minishell: ", 0);
	return (true);
}

void	sigint_handler(int sig_code)
{
	g_signal_received = sig_code;
	rl_done = 1;
	// rl_redisplay();
	// rl_replace_line("minishell: ", 0);
	return;
}

int rl_event_dummy() 
{ 
	return 0; 
}

// void	sigquit_hd_handler(int sig_code)
// {
// 	g_signal_received = sig_code;
// 	ft_putstr_fd("Minishell : Warning here-document delimited by end-of-file (wanted `eof')", 2);
// 	free()
// }

bool	init_signal(type_of_signals type)
{
	if (type == S_PROMPT) 
	{
		signal(SIGQUIT, SIG_IGN);	
		signal(SIGINT, sigint_handler);
		return (true);
	}
	else if (type == S_HERE_DOC) 
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		return (true);	
	} 
	else if  (type == S_EXEC) 
	{
		signal(SIGQUIT, SIG_IGN);	
		signal(SIGINT, sigint_handler);
		return (true);
	}
	return (true);
}