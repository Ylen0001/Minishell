/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:33:52 by aberion           #+#    #+#             */
/*   Updated: 2024/10/12 13:36:27 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_variable(t_vectstr *env, char *to_add, int i)
{
	free(env->data[i]);
	env->data[i] = (char *)ft_strdup(to_add);
}

void	skip_spaces_co(char *str, int *it)
{
	while (str[*it] && ft_isspace(str[*it]))
		(*it)++;
	while (str[*it] && !ft_isspace(str[*it]))
		(*it)++;
	while (str[*it] && ft_isspace(str[*it]))
		(*it)++;
}

int	extract_token(char *s, char *to_add, int *i)
{
	int	j;
	int	check_qote;

	j = 0;
	check_qote = 0;
	while (s[*i])
	{
		if ((s[*i] == '"' || s[*i] == '\'') && check_qote == 0)
		{
			check_qote = 1;
			(*i)++;
		}
		else if ((s[*i] == '"' || s[*i] == '\'') && check_qote == 1)
		{
			check_qote = 0;
			(*i)++;
			break ;
		}
		if (ft_isspace(s[*i]) == 1 && check_qote == 0)
			break ;
		to_add[j++] = s[*i];
		(*i)++;
	}
	to_add[j] = '\0';
	return (check_qote);
}

void	export_helper(t_data *s_data, int *i, char *s, char *to_add)
{
	while (s[(*i)])
	{
		if (extract_token(s, to_add, i) == 1)
		{
			s_data->exit_status = 1;
			return ;
		}
		if (to_add[0] == '=')
		{
			s_data->exit_status = 1;
			return ;
		}
		if (to_add[0])
		{
			if (check_presence(s_data, to_add) == 0)
				vectstr_happend(s_data->vect_env, to_add);
		}
		if (s[*i] == '\0')
			break ;
		(*i)++;
	}
}

void	builtin_export(t_data *s_data)
{
	int		i;
	char	*s;
	char	to_add[BUFFER_SIZE2];

	ft_memset(to_add, '\0', BUFFER_SIZE2);
	i = 0;
	s = s_data->v_path->parsed[s_data->i_cmd].cmd->data[0];
	skip_spaces_co(s, &i);
	if (s[i] == '\0')
	{
		print_export(s_data);
		return ;
	}
	if (check_equal(s_data, s) == 1)
		return ;
	export_helper(s_data, &i, s, to_add);
}
