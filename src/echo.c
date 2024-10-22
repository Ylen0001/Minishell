/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/22 13:35:43 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	b_i_echo(t_data *data, char *cmd)
{
	char	*splited;
	int		newline;

	newline = 1;
	if (cmd[4] == '\0')
		return ;
	splited = clean_input(data, cmd);
	newline = check_newline_option(cmd);
	if (splited == NULL)
		return ;
	if (data->flag_echo_trig == 1)
		newline = 0;
	printf("%s", splited);
	if (newline)
		printf("\n");
	free(splited);
	data->exit_status = 0;
}

int	check_newline_option(char *cmd)
{
	int	i;

	i = 6;
	while (cmd[i] && cmd[i] == 'n')
	{
		i++;
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}

char	*remove_quotes_from_string_2(const char *str)
{
	char	*new_str;
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;
	int		j;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	j = 0;
	new_str = (char *)malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	option_detector(t_data *data, char *cmd, size_t *i)
{
	int	safe;

	if (cmd[(*i)] == '-')
	{
		safe = (*i);
		(*i)++;
		while (cmd[(*i)] == 'n')
			(*i)++;
		if (cmd[(*i)] == ' ' || cmd[(*i)] == '\t')
		{
			(*i)++;
			data->flag_echo_trig = 1;
		}
		else
		{
			data->checkerina = 1;
			(*i) = safe;
		}	
	}
	else
			data->checkerina = 1;
}

char	*clean_input(t_data *data, char *cmd)
{
	size_t	i;
	char	*cleaned_cmd;
	char	*temp;

	temp = remove_quotes_from_string_2(cmd);
	i = 5;
	if (temp[4] == '\0')
		return (NULL);
	while (!data->checkerina)
	{
		while (temp[i] && (temp[i] == ' ' || temp[i] == '\t'))
			i++;
		option_detector(data, temp, &i);
		while (temp[i] && (temp[i] == ' ' || temp[i] == '\t'))
			i++;
	}
	cleaned_cmd = ft_strdup(temp + i);
	free(temp);
	return (cleaned_cmd);
}
