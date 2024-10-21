/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:05:16 by aberion           #+#    #+#             */
/*   Updated: 2024/07/08 13:27:48 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*g_message = NULL;

void	write_message(int message_capacity, int message_index, siginfo_t *info)
{
	(void)message_capacity;
	g_message[message_index] = '\0';
	write(1, g_message, message_index);
	write(1, "\n", 1);
	free(g_message);
	g_message = NULL;
	kill(info->si_pid, SIGUSR1);
}

void	handle_signal_bis(char *character, int *message_index,
		int *message_capacity, siginfo_t *info)
{
	size_t	old_capacity;

	old_capacity = 0;
	if (*character == '\0')
	{
		write_message(*message_capacity, *message_index, info);
		*message_index = 0;
		*message_capacity = 1024;
	}
	else
	{
		if (*message_index >= *message_capacity - 1)
		{
			old_capacity = *message_capacity;
			*message_capacity *= 2;
			g_message = ft_realloc(g_message, *message_capacity, old_capacity);
			if (!g_message)
				exit(1);
			ft_memset(g_message + old_capacity, 0, *message_capacity
				- old_capacity);
		}
		g_message[(*message_index)++] = *character;
	}
	*character = 0;
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_index = 0;
	static char	character = 0;
	static int	message_index = 0;
	static int	message_capacity = 0;

	(void)context;
	if (!g_message)
	{
		message_capacity = 1024;
		g_message = malloc(message_capacity);
		if (!g_message)
			exit(1);
		ft_memset(g_message, 0, message_capacity);
	}
	if (signal == SIGUSR1)
		character |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		handle_signal_bis(&character, &message_index, &message_capacity, info);
		bit_index = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	handle_exit(int sig)
{
	(void)sig;
	if (g_message)
	{
		free(g_message);
		g_message = NULL;
	}
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sa_exit;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa_exit.sa_handler = handle_exit;
	sigemptyset(&sa_exit.sa_mask);
	sa_exit.sa_flags = 0;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa_exit, NULL);
	sigaction(SIGTERM, &sa_exit, NULL);
	while (1)
		pause();
	return (0);
}
