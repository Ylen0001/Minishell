/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/08/30 17:03:33 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int		flag_is_ok(char *flag)
{
	size_t i;

	i = 1;
	if(flag[0] != '-')
		return (0);
	while(flag[i])
	{
		if(flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	b_i_echo(t_data *data, char *cmd)
{
	// char 	**splited;
	char 	*splited;
	int		newline;
	size_t	i;

	newline = 1;
	splited = clean_input(data, cmd);
	if(splited == NULL)
		return ;
	// splited = ft_split(cmd, ' ');	
	i = 1;
	if(data->flag_echo_trig == 1)
		newline = 0;
	while(splited)
		printf("%s", splited);
	if (newline)
		printf("\n");
	data->exit_status = 0;
	// builtin_exit(data, "OUI");
	return;
}

char *clean_input(t_data *data, char *cmd)
{
	char *clean_input;
	size_t i;
	size_t j;

	clean_input = NULL;
	i = 0;
	j = 0;

	while(cmd[i])
	{
		if(strncmp(cmd, "echo ", 5)) // On skip echo
			i += 5;
		if(cmd[i] == '-') // Si option
			i++;
		while(cmd[i] == 'n') // Tant que n 
			i++;
		if (cmd[i] == ' ' && cmd[i] == '\t')	// On skip le last whitespace avant la str à echo.
		{
			i++;
			data->flag_echo_trig = 1;
		}
		else									// Si invalid flag.
			i = 5;
		clean_input = ft_calloc((ft_strlen(cmd) - i) + 1, sizeof(char));
		while(cmd[i]) // On cpy le reste de cmd dans clean_input.
		{
			clean_input[j] = cmd[i];
			j++;
			i++; 
		}
		return (clean_input);
	}
	return (NULL);
}