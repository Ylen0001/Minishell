/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:31:12 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/21 15:28:29 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tmp(char *input, t_data *s_data, t_vectstr *env_buff, int *ex_st_buff)
{
	if (check_spaces(input) != 0)
	{
		g_signal_received = 0;
		return (1);
	}
	if (!input)
	{
		garbage_destructor(s_data);
		free_t_data(s_data, 0);
		free_t_vectstr(env_buff);
		return (42);
	}
	add_history(input);
	launch_parsing(input, s_data);
	minishell(s_data);
	env_buff = s_data->vect_env;
	*ex_st_buff = s_data->exit_status;
	return (0);
}

void	run_minishell(char **env, t_vectstr *env_buff, t_data *s_data,
		int *ex_st_buff)
{
	char	*input;

	while (init_signal(S_PROMPT))
	{
		input = NULL;
		rl_event_hook = rl_event_dummy;
		*s_data = init_data(env, *ex_st_buff, env_buff);
		input = get_input(s_data);
		if (!input)
			break ;
		process_input(input, s_data, env_buff, ex_st_buff);
		free_t_vector(s_data->v_path);
		s_data->v_path = NULL;
	}
}

char	*get_input(t_data *s_data)
{
	char	*input;

	input = NULL;
	if (g_signal_received == 2)
		g_signal_received = 0;
	if (isatty(STDIN_FILENO))
		input = readline("minishell: ");
	else
	{
		input = read_from_stdin(s_data);
		if (input)
			ft_putstr_fd("minishell: \n", STDOUT_FILENO);
	}
	if (!input)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return (input);
}

void	process_input(char *input, t_data *s_data, t_vectstr *env_buff,
		int *ex_st_buff)
{
	int	i;

	s_data->input_list = ft_split(input, '\n');
	free(input);
	i = 0;
	while (s_data->input_list[i])
	{
		tmp(s_data->input_list[i], s_data, env_buff, ex_st_buff);
		i++;
	}
	free_charchar(s_data->input_list);
}
