/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:06 by ylenoel           #+#    #+#             */
/*   Updated: 2024/07/30 17:06:07 by aberion          ###   ########.fr       */
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
# include <dirent.h>

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

// typedef struct s_vectstr {
// 	char **data;
// 	size_t size;
// 	size_t capacity;
// }	t_vectstr;

// typedef struct s_node {
// 	t_vectstr v_cmd;
// 	t_vectstr v_redir;
// 	int *redir_type;
// } t_node;

typedef struct s_vectint {
    int *redir_type; // Enum
    size_t size;
    size_t capacity;
}    t_vectint;

typedef struct s_vectstr {
    char **data; // cmd + opt + arg // Arg post << = limiter
    size_t size;
    size_t capacity;
}    t_vectstr;


//<	Makefile <<eof <<salope <file1 cat file2 >file3 >chat >biere;
//execve("cat",  {"cat file2"}, ENV);
typedef struct s_parsed {
	t_vectstr *cmd; //cat file2
	t_vectstr *redir; //Makefile, eof, salope, file1, file3, chat, biere; 
	t_vectint type; //< << << < > > >;
} t_parsed;


typedef struct s_vector {
	t_parsed *parsed; //{ info cmd1, info cmd2, info cmdN....};
	size_t size;
	size_t capacity;
}	t_vector;

typedef struct s_data // Structure Globale
{

	/* Pour les tests */
	
	char 	**lst_cmd;
	char 	**hd_names;
	char	**cmds;
	char 	*hd_name;
	int		trigger;
	int		*hd_nbr;

	/* Pour l'exec */
	char	*tmp;
	int		**pipefds; // Tableau de pipes
	int		*pipefd; // Pipe basique
	pid_t	*pids; // tableau de pids pour childs process
	int		i_pids; // idx de pids
	int		i_pipes; // idx des pipes
	int		infile; // fd
	int		i;
	int		j;
	char	c;
	int	errno; // à remplir avec waitpid et avec signal
	
	/* Pour le parsing */
	t_vector v_path;
	char *full_string; // Str complète avec les redirections
	char **env;
}				t_data;


/* TEST */

// int		is_dir(t_data *data);
// void	infile_check(t_data *data);
// void	init_test(t_data *data);
void		nbr_of_here_doc(t_data *data);
void 		recup_data(t_data *data);
t_vector	init_vector();
t_vectstr 	init_vect_str();
void		here_doc_case(t_data *data, char *limiter);
int			lil_gnl(char **line, t_data *data);
void		lil_gnl_finisher(int *i, char *tmp);
char		*lil_gnl_initializer(int *i, int *j, char *tmp);
void		here_doc_error(void);



/* Prompt display + signaux */

bool	init_prompt();
void 	sigint_handler(int sig_code);
bool 	init_signal();

/* Error Handling */

void	here_doc_error(void);


t_data init_data(char **env);
void launch_parsing(char *input, t_data *s_data);
void vectstr_happend(t_vectstr *vect, char *data);
void vector_append(t_vector *vect, t_vectstr new_vect);
void vectstr_print(t_vectstr *vect);
void vectstr_free(t_vectstr *);

#endif