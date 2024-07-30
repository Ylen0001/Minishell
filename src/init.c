/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:48:33 by aberion           #+#    #+#             */
/*   Updated: 2024/07/30 13:33:42 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

t_vectstr init_vect_str()
{
    t_vectstr self;
    
    self.size = 0;
    self.capacity = 10;
    self.data = (char **)malloc(10 * sizeof(char *));
    if (!self.data)
        EXIT_FAILURE;
    return self;
}

t_vector init_vector()
{
    t_vector self;
    int i = 0;
    
    self.parsed = (t_parsed *)malloc(10 * sizeof(t_parsed *));
    if (!self.parsed)
        EXIT_FAILURE;
    self.size = 0;
    self.capacity = 10;
    return self;
}

void init_env(t_vectstr *vect_env, char ** env)
{
    int i = 0;

    while(env[i])
    {
        vectstr_happend(vect_env, env[i]);
        i++;
    }
}
t_parsed init_parsed()
{
    t_parsed self;
    int i = 0;
    
    self.cmd
}


t_data init_data(char **env)
{
    t_data self;
    self.full_string = NULL;
    self.env = NULL;
    self.v_path = init_vector();
    size_t i = 0;
    while (i < self.v_path.capacity)
    {
        self.v_path.v_cmd[i] = malloc(sizeof(t_vectstr));
        *self.v_path.v_cmd[i] = init_vect_str();
        i++;
    }
    init_env(self.v_path.v_cmd[0], env);
    return self;
}



// t_data init()
// {
//     t_data self;

//     self.full_string = NULL;
//     self.env = NULL;
//     self = init_data();
    
//     return self;
// }

// void	init_test(t_data *data)
// {
// 	data->i = 0;
// 	data->lst_cmd = malloc(sizeof(char *) * 3 + 1);
// 	if(data->lst_cmd == NULL)
// 		printf("Lst_cmd Malloc failure\n");
// 	data->pipefds = ft_calloc(3, sizeof(int*));
// 	while(data->i < 3);
// 		data->pipefds[data->i++] = ft_calloc(2, sizeof(int));
// 	data->lst_cmd[0] = ft_strdup("infile");	
// 	printf("%s\n", data->lst_cmd[0]);
// 	data->lst_cmd[1] = ft_strdup("cat");	
// 	printf("%s\n", data->lst_cmd[1]);
// 	data->lst_cmd[2] = ft_strdup("rev");	
// 	printf("%s\n", data->lst_cmd[2]);
//     init_vector(&s_data->v_path);
//     t_vector self;
    
//     self.size = 0;
//     self.capacity = 10;
//     self.node = (t_node *)malloc(10 * sizeof(t_node));
//     if(!self.node)
//         EXIT_FAILURE;
//     self.node->v_cmd = init_vect_str();
//     self.node->v_redir = init_vect_str();
//     return self;
// }

// void init_heredoc(t_data **s_data)
// {
//     t_heredoc *new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
//     if (!new_heredoc)
//         EXIT_FAILURE;
//     new_heredoc->limiter = NULL;
//     new_heredoc->size = 0;
//     (*s_data)->s_here = new_heredoc;
    
// }