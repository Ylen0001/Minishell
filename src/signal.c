/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:39:26 by aberion           #+#    #+#             */
/*   Updated: 2024/08/15 16:02:16 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void signal_handler(int signum)
{
    g_signal_received = signum;
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
