/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:33:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/12 13:50:46 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_signal_received = 0;

void	free_charchar(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data		s_data;
	t_vectstr	*env_buff;
	int			ex_st_buff;

	(void)argv;
	if (argc != 1 || env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	env_buff = init_vect_str();
	init_env(env_buff, env);
	ex_st_buff = 0;
	run_minishell(env, env_buff, &s_data, &ex_st_buff);
	free_t_data(&s_data, 0);
	rl_clear_history();
	printf("exit\n");
	return (0);
}
