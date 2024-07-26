/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_recup_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:48:46 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/26 16:29:27 by ylenoel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **env) 
{
	(void)argv;
	if (argc != 1 || env == NULL || *env == NULL)
		exit(EXIT_FAILURE);
	t_data s_data;
	s_data = init_data();
	s_data.env = env;
	while (init_prompt() && init_signal())
	{
		char *input = readline("minishell: ");
		if (!input)
			exit(1);
		// launch_parsing(input, &s_data);
		// if(s_data.trigger == 0)
		// {
		recup_data(&s_data);
		// s_data.trigger = 1;
		add_history(input);
	}
	rl_clear_history();
    return 0;
}

void recup_data(t_data *data)
{
	char **cmd1;
	char *limiter;
	int	*redir;

	redir = &data->v_path.v_cmd.redir_type[0];
	cmd1 = data->v_path.v_cmd.data;
	limiter = data->v_path.v_cmd.limiter[0];
	here_doc_case(data, limiter);
	
	// printf("%s\n", cmd1[0]);
	// printf("%d\n", redir[0]);
	// printf("%s\n", limiter);
	
}
t_data init_data()
{
    t_data self;
    self.pipefds = NULL;
    self.pids = NULL;
    self.infile = 0;
    self.i = 0;
    self.j = 0;
    self.c = '\0';
	self.tmp = NULL;
	self.trigger = 0;
    // self.redirect = 0;
    self.errno = 0;
    self.full_string = NULL;
    self.env = NULL;
    self.v_path = init_vector();
    return self;
}

t_data init()
{
    t_data self;
    self = init_data();
    return self;
}

t_vectstr init_vect_str()
{
    t_vectstr self;
    
    self.size = 0;
    self.capacity = 10;
    self.data = (char **)malloc(10 * sizeof(char *));
    if (!self.data)
        EXIT_FAILURE;
	self.data[0] = "Hello";
    self.redir_type = (int *)malloc(10 * sizeof(int));
    if (!self.redir_type)
        EXIT_FAILURE;
	self.redir_type[0] = 1;
    self.limiter = (char **)malloc(10 * sizeof(char *));
    if (!self.limiter)
        EXIT_FAILURE;
	self.limiter[0] = "EOF";
    return self;
}

t_vector init_vector()
{
    t_vector self;
    
    self.size = 0;
    self.capacity = 10;
    self.v_cmd = init_vect_str();
    return self;
}

// int	is_here_doc(char *limiter, t_data *data, int i_hd_name)
// {
// 	char	*line;

// 	write(1, "heredoc> ", 9);
// 		data->infile = open(data->hd_name[i_hd_name], O_RDWR | O_CREAT | O_TRUNC, 0777);
// 	if (data->infile == -1)
// 		here_doc_error();
// 	while (lil_gnl(&line, data) != EOF)
// 	{
// 		if (line && (ft_strlen(limiter) + 1 == ft_strlen(line))
// 			&& ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
// 		{
// 			free(line);
// 			close(data->infile);
// 			return ;
// 		}
// 		if (line)
// 		{
// 			write(data->infile, line, ft_strlen(line));
// 			write(1, "heredoc> ", 9);
// 		}
// 		free(line);
// 	}
// 	close(data->infile);	
// }