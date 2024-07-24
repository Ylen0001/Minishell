/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:06 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/24 10:48:25 by ylenoel          ###   ########.fr       */
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

typedef struct s_heredoc // Liste chaînée
{
	char *limiter; // EOF du here_doc
	int node; // Index de la node (Important pour savoir sur quel here_doc on se situe si il y en a plusieurs)
	struct t_heredoc *prev;
	struct t_heredoc *next;
}			t_heredoc;

typedef struct s_liste
{
	char *full_string; // Str complète avec les redirections
	char **cmd; // cmd avec options et arguments mais sans redirections
	e_redir redirect;
	struct t_liste *prev;
	struct t_liste *next;
}			t_liste;

typedef struct s_data // Structure Globale
{
	/* Pour l'exec */
	int		**pipefds;
	int		**pids;
	int		infile;
	int		i;
	int		j;
	char	c;
	char	*tmp;
	char	*limiter;
	
	/* Pour le parsing */
	char *input;
	
	struct t_heredoc *s_here;
	struct t_liste *s_list;
	int	errno; // à remplir avec waitpid et avec signal
}				t_data;


/* Prompt display + signaux */

bool	init_prompt();
void 	sigint_handler(int sig_code);
bool 	init_signal();

/* Error Handling */

void	here_doc_error(void);

#endif