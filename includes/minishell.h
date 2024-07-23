/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:06 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/22 16:56:12 by ylenoel          ###   ########.fr       */
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

typedef enum
{
	STDIN_REDIR = 0,
	HERE_DOC = 1,
	STDOUT_REDIR = 2,
	STDOUT_APPEND = 3,	
}	e_redir;

typedef struct s_data // Structure Globale
{
	/* Pour l'exec */
	int	**pipefds;
	int	**pids;
	
	t_heredoc;
	t_list;
	int	errno; // à remplir avec waitpid et avec signal
}	t_data;

typedef struct s_heredoc // Liste chaînée
{
	char *limiter; // EOF du here_doc
	int node; // Index de la node (Important pour savoir sur quel here_doc on se situe si il y en a plusieurs)
	t_heredoc *next;
}	t_heredoc;

typedef struct s_list
{
	char *full_string; // Str complète avec les redirections
	char **cmd; // cmd avec options et arguments mais sans redirections
	e_redir redirect;
	t_list *next;
}	t_list;

/* PARSING */
/* EXEC */



#endif