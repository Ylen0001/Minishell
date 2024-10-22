/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:24:43 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/22 15:17:32 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	b_i_echo(t_data *data, char *cmd)
// {
// 	char	**result;
// 	char	*splited;
// 	int		newline;

// 	newline = 1;
// 	if (cmd[4] == '\0')
// 		return ;
// 	splited = clean_input(data, cmd);
// 	result = ft_split(splited, ' ');
// 	if(result == NULL)
// 		free(result);
// 	// newline = check_newline_option(cmd);
// 	if (splited == NULL)
// 	{
// 		free(result);
// 		return ;
// 	}
// 	if (data->flag_echo_trig == 1)
// 		newline = 0;
// 	printf("%s", splited);
// 	if (newline)
// 		printf("\n");
// 	free(result);
// 	free(splited);
// 	data->exit_status = 0;
// }

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
		if (cmd[(*i)] == ' ' || cmd[(*i)] == '\t' || cmd[(*i)] == '\0')
		{
			data->flag_echo_trig = 1;
			while (cmd[(*i)] == ' ')
				(*i)++;
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
	while (!data->checkerina && temp[i])
	{
		while (temp[i] && (temp[i] == ' ' || temp[i] == '\t'))
			i++;
		option_detector(data, temp, &i);
	}
	cleaned_cmd = ft_strdup(temp + i);
	free(temp);
	return (cleaned_cmd);
}

int check_option(char *str, t_data *data)
{
	size_t i;
	
	i = 0;
	if(!str)
		return 1;
	if(str[0] == '-' && str[1] == 'n')
	{
		i = 1;
		while(str[i] && str[i] == 'n')
			i++;
		if (i == ft_strlen(str))
		{
			data->flag_echo_trig = 1;
			return 1;
		}
	}
	return 0;
}

void print_echo(t_data *data, char **charc, int index)
{
	while(charc[index])
	{
		printf("%s", charc[index++]);
		if(charc[index])
			printf(" ");
	}
	if(!data->flag_echo_trig)
		printf("\n");
	return;
}

void	b_i_echo(t_data *data, char *cmd)
{
	char	**splitted;
	int		i;
	int		index;
	
	index = 0;
	splitted = ft_split_sa(cmd);
	if (splitted[1])
	{	
		i = 1;
		while(splitted[i])
		{
			if(!check_option(splitted[i], data))
			{
				print_echo(data, splitted, ++index);
				break;
			}
			i++;
			index++;	
		}
	}
	free_charchar(splitted);
	return;
}


