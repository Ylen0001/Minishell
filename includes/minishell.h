/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:06 by ylenoel           #+#    #+#             */
/*   Updated: 2024/09/20 12:15:47 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../includes/colors.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/signal.h>
# include <dirent.h>
# include <signal.h>

//<	Makefile <<eof <<slt <file1 cat file2 >file3 >chat >biere;
//execve("cat",  {"cat file2"}, ENV);
// char **data = {"cat", "file1", "file2"};
// execve(data[0], data, ENV);

typedef enum
{
	STDIN_REDIR = 0, // <
	HERE_DOC = 1,    // <<
	STDOUT_REDIR = 2, // >
	STDOUT_APPEND = 3,	// >>
}	e_redir;

typedef enum {
	S_HERE_DOC,
	S_EXEC,
	S_PROMPT,
} type_of_signals;

typedef struct s_vectint {		// 1 type = un où plusieurs type de redir 
    int *redir_type; // Enum
    size_t size;
    size_t capacity;
}    t_vectint;

typedef struct s_vectstr {		// 1 cmd = 1 cmd + args / 1 redir = 1 où plusieurs fichiers de redir
    char **data; // cmd + opt + arg // Arg post << = limiter
    size_t size;
    size_t capacity;
}    t_vectstr;

//<	Makefile <<eof <<salope <file1 cat file2 >file3 >chat >biere;
//execve("cat",  {"cat file2"}, ENV);

typedef struct s_parsed { 		// 1 parsed = Entre deux pipe
	t_vectstr *cmd; //cat file2
	t_vectstr *redir; //Makefile, eof, file1, file3, chat, biere;
	t_vectint *type; //< << << < > > >;
} t_parsed;


typedef struct s_vector { 		// 1 v_path = 1 input
	t_parsed *parsed; //{ info cmd1, info cmd2, info cmdN....};
	size_t size;
	size_t capacity;
}	t_vector; // v_path

#define BUFFER_SIZE2 65536

typedef struct s_data // Structure Globalem
{

	/* Pour les tests */
	
	char 	**cmds;
	char	*file;
	char 	*file2;
	int		redir;

	/* Pour l'exec */
	
	int			old_fdin;
	int			old_fdout;
	int			flag_echo_trig;
	int			cd_trigger;
	int			status;
	int			exit_status;
	size_t 		hd_it;
	int			pipe_trig;
	int			sleep_i;
	size_t		i_pipes;
	char		**hd_names;
	size_t		hd_count;
	size_t		suffix;
	int			a_file;
	size_t		nbr_cmd;
	size_t		nbr_input; // Nbr de cmd dans une ligne
	pid_t		*pids; // tableau de pids pour childs process
	char		*tmp;
	int			**pipefds; // Tableau de pipes
	int			*pipefd; // Pipe basique
	int			infile; // fd
	int			outfile;
	int			trigger;
	int			i;
	size_t		i_redir;
	size_t		i_cmd;
	size_t		j;
	int			k;
	char		c;
	int			errno; // à remplir avec waitpid et avec signal
	size_t		built_in;
	// int			flag_echo_trig;
	
	/* Pour le parsing */
	t_vectstr *vect_env;
	t_vector 	*v_path;
	char buffer[BUFFER_SIZE2];
	char **m_cmd;
	char *full_string; // Str complète avec les redirections
	char **env;
	int check_quotes_space;
	int checkerino;
}				t_data;


/* TEST */
void 		recup_data(t_data *data);
t_vector	*init_vector();
t_vectstr 	*init_vect_str();
void		minishell(t_data *data);
int			tmp(char *input, t_data *s_data, t_vectstr *env_buff, int *ex_st_buff);
void		infile_or_heredoc(t_data *data, char **env);
void		garbage_collector(t_data *data);
void		exec_cmd(t_data *data, char **env, char *cmd);
char		*find_path(char *cmd, char *env[]);
char		*get_env_path(char *env[]);
void		free_paths(char **paths);
char		*construct_path(char *dir, char *cmd);
char    	*check_file(t_data *data, char *cmd);
int			there_is_slash(char *cmd);
void		init_data_2(t_data *data);
bool		status();
void		core_exec(t_data *data, size_t idx, int built_in);
int			open_file_minishell(t_data *data, int type, char *file);
void		redirections(t_data *data, const struct s_vectint *redir_t, char **redir_f);
void		stdout_redir(t_data *data, int redir_type, char *redir_file);
void		heredoc_redir(t_data *data, int redir_type, char *redir_file);
void		stdin_redir(t_data *data, int redir_type, char *redir_file);
void		here_doc_detector(t_data *data);
void		here_doc_case(t_data *data, char *limiter);
int			lil_gnl(char **line, t_data *data);
void		lil_gnl_finisher(int *i, char *tmp);
char		*lil_gnl_initializer(int *i, int *j, char *tmp);
void		garbage_destructor(t_data *data);
void		mult_cmd_exec(t_data *data);
void		single_cmd_not_bi_exec(t_data *data);
void		single_bi_cmd_exec(t_data *data);
void		close_pipes(t_data *data);
void		waitpids_and_unlink(t_data *data);
void		pipes_and_redirs_check(t_data *data, size_t it_cmd);
void		if_absolute_cmd(t_data *data);
void		if_relative_cmd(t_data *data);

// int		is_dir(t_data *data);
// void		here_doc_error(void);

/* ABOUT BUILT_IN */
void	built_in_detector(t_data *data, char *cmd);
void	built_in_manager(t_data *data, char *cmd);
int 	b_i_cd(t_data *data, char *cmd);
char 	*get_oldpwd_value(t_data *data, char *last_dir);
void	update_oldpwd_env(t_data *data, char *updated_oldpwd);
char	*get_home_value(t_data *data, char *home_dir);
void	b_i_echo(t_data *data, char *cmd);
char	*clean_input(t_data *data, char *cmd);
int		flag_is_ok(char *flag);
void	b_i_pwd(t_data *data);

/* Prompt display + signaux */

bool	init_prompt();
void 	sigint_handler(int sig_code);
bool 	init_signal(type_of_signals);
int		rl_event_dummy();
	
/* Error Handling */

void	here_doc_error(void);


t_data init_data(char **env, int ex_data_buff, t_vectstr *env_buff);
t_parsed init_parsed();
void launch_parsing(char *input, t_data *s_data);
void vectstr_happend(t_vectstr *vect, char *data);
void vectstr_print(t_vectstr *vect);
void vectstr_free(t_vectstr *);
void free_t_vector(t_vector *vector);
void vectint_print(t_vectint *vect);
void vectint_happend(t_vectint *vect, int number);
void free_t_data(t_data *data, int check);
void v_path_double(t_vector *vector);
void vector_happend(t_vector *vect, char *n);
void vector_print(t_vector *vect);
t_vectint *init_vect_int();
int check_spaces(char *input);
void setup_signal_handlers(void);
void send_builtin(t_data *s_data);
t_vectstr *init_vect_str();
void init_env(t_vectstr *vect_env, char **env);
t_vectstr *vectstr_dup(t_vectstr *vect);
void free_t_vectstr(t_vectstr *vect);
void *ft_realloc(void *ptr, size_t capacity, size_t size, size_t elemSize);
void builtin_unset(t_data *data, char *cmd);
void builtin_exit(t_data *s_data, char *cmd);
void builtin_env(t_data *s_data);
void builtin_export(t_data *s_data, char *cmd);
int ft_isspace(char c);
int check_chevron(t_data *s_data);
void free_charchar(char **s);

#define vect_print(param) _Generic((param), \
	t_vector *: vector_print,	\
    t_vectstr *: vectstr_print,   \
    t_vectint *: vectint_print,   \
    default : printf("Format not supported yet\n") \
)(param)

#define vect_happend(param, data) _Generic((param), \
	t_vector *: vector_happend,		\
    t_vectstr *: vectstr_happend,   \
    t_vectint *: vectint_happend,   \
    default : printf("Format not supported yet\n") \
)(param, data)

#endif