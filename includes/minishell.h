/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:06 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 16:24:32 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/signal.h>

typedef enum
{
	STDIN_REDIR = 0,
	HERE_DOC = 1,
	STDOUT_REDIR = 2,
	STDOUT_APPEND = 3,	
}	e_redir;

// typedef struct s_heredoc // Liste chaînée
// {
// 	char **limiter; // EOF du here_doc
// 	size_t size;
// 	size_t capacity;
// }			t_heredoc;

typedef struct s_data // Structure Globale
{
	/* Pour l'exec */
	int		**pipefds;
	int		**pids;
	int		infile;
	int		i;
	int		j;
	char	**limiter;
	char	*tmp;
	char	c;
	
	/* Pour le parsing */
	char *full_string; // Str complète avec les redirections
	char **cmd; // cmd avec options et arguments mais sans redirections
	e_redir redirect;
	int	errno; // à remplir avec waitpid et avec signal
}				t_data;


/* Prompt display + signaux */

bool	init_prompt();
void 	sigint_handler(int sig_code);
bool 	init_signal();

/* Error Handling */

void	here_doc_error(void);


void init_data(t_data *s_data);
void launch_parsing(char *input, t_data *s_data);

#endif