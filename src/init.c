/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/25 13:17:07 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// void init_heredoc(t_data **s_data)
// {
//     t_heredoc *new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
//     if (!new_heredoc)
//         EXIT_FAILURE;
//     new_heredoc->limiter = NULL;
//     new_heredoc->size = 0;
//     (*s_data)->s_here = new_heredoc;
    
// }

void init_vector(t_vector *vect)
{
    vect->size = 0;
    vect->capacity = 10;
    vect->node = (t_node *)malloc(10 * sizeof(t_node));
        if(!vect->node)
            EXIT_FAILURE;
}

void init_data(t_data *s_data)
{
    if (!s_data)
        EXIT_FAILURE;
    s_data->pipefds = NULL;
    s_data->pids = NULL;
    s_data->infile = 0;
    s_data->i = 0;
    s_data->j = 0;
    s_data->limiter = NULL;
    s_data->tmp = NULL;
    s_data->c = '\0';
    s_data->redirect = 0;
    s_data->errno = 0;
    s_data->v_path.size = 0;
    s_data->v_path.capacity = 10;
}

void init(t_data *s_data)
{
    init_data(s_data);
}

void	init_test(t_data *data)
{
	data->i = 0;
	data->lst_cmd = malloc(sizeof(char *) * 3 + 1);
	if(data->lst_cmd == NULL)
		printf("Lst_cmd Malloc failure\n");
	data->pipefds = ft_calloc(3, sizeof(int*));
	while(data->i < 3);
		data->pipefds[data->i++] = ft_calloc(2, sizeof(int));
	data->lst_cmd[0] = ft_strdup("infile");	
	printf("%s\n", data->lst_cmd[0]);
	data->lst_cmd[1] = ft_strdup("cat");	
	printf("%s\n", data->lst_cmd[1]);
	data->lst_cmd[2] = ft_strdup("rev");	
	printf("%s\n", data->lst_cmd[2]);
    init_vector(&s_data->v_path);
}