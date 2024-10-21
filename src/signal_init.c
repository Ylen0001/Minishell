/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:45:16 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/07 16:43:21 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile int	g_signal_received;

bool	init_prompt(void)
{
	rl_redisplay();
	rl_replace_line("minishell: ", 0);
	return (true);
}

int	rl_event_dummy(void)
{
	return (0);
}

bool	init_signal(t_type_of_signals type)
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
	else if (type == S_EXEC)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, sigint_handler_exec);
		return (true);
	}
	return (true);
}
