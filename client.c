/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:05:13 by aberion           #+#    #+#             */
/*   Updated: 2024/07/08 10:07:21 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_flags = 0;

void	handle_ack(int sig)
{
	if (sig == SIGUSR2)
		g_flags |= ACK_RECEIVED;
	else if (sig == SIGUSR1)
		ft_printf("Message received by server\n");
}

void	handle_interrupt(int sig)
{
	(void)sig;
	g_flags |= INTERRUPTED;
	ft_printf("\nProgram interrupted. Exiting...\n");
	_exit(0);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (g_flags & INTERRUPTED)
			return ;
		g_flags &= ~ACK_RECEIVED;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!(g_flags & ACK_RECEIVED))
		{
			usleep(10);
			if (g_flags & INTERRUPTED)
				return ;
		}
		i++;
	}
}

void	send_string(int pid, char *str)
{
	while (*str)
	{
		if (g_flags & INTERRUPTED)
			return ;
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	signal(SIGUSR1, handle_ack);
	signal(SIGUSR2, handle_ack);
	signal(SIGINT, handle_interrupt);
	send_string(server_pid, message);
	return (0);
}
