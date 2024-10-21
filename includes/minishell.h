/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylenoel <ylenoel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:37:40 by ylenoel           #+#    #+#             */
/*   Updated: 2024/10/21 15:42:31 by ylenoel          ###   ########.fr       */
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

# define BUFFER_SIZE2 16384

//<	Makefile <<eof <<slt <file1 cat file2 >file3 >chat >biere;
//execve("cat",  {"cat file2"}, ENV);
// char **data = {"cat", "file1", "file2"};
// execve(data[0], data, ENV);
extern volatile int	g_signal_received;

// <
// <<
// >
// >>
typedef enum s_redir
{
	STDIN_REDIR = 0,
	HERE_DOC = 1,
	STDOUT_REDIR = 2,
	STDOUT_APPEND = 3,
}	t_redir;

typedef enum s_sign
{
	S_HERE_DOC,
	S_EXEC,
	S_PROMPT,
}	t_type_of_signals;

// 1 type = un où plusieurs type de redir 
typedef struct s_vectint
{
	int		*redir_type;
	size_t	size;
	size_t	capacity;
}	t_vectint;

// 1 cmd = 1 cmd + args / 1 redir = 1 où plusieurs fichiers de redir
// data : cmd + opt + arg // Arg post << = limiter
typedef struct s_vectstr
{
	char	**data;
	size_t	size;
	size_t	capacity;
}	t_vectstr;

//<	Makefile <<eof <<salut <file1 cat file2 >file3 >chat >biere;
//execve("cat",  {"cat file2"}, ENV);
// 1 parsed = Entre deux pipe
// cmd : cat file2
// Redir : Makefile, eof, file1, file3, chat, biere;
// type : < << << < > > >;
typedef struct s_parsed
{
	t_vectstr	*cmd;
	t_vectstr	*redir;
	t_vectint	*type;
}	t_parsed;

// 1 v_path = 1 input
// parsed : { info cmd1, info cmd2, info cmdN....};
typedef struct s_vector
{
	t_parsed	*parsed;
	size_t		size;
	size_t		capacity;
}	t_vector;

typedef struct s_Range
{
	int		s;
	int		e;
}			t_range;

typedef struct s_data // Structure Globale
{
	char		**cmds;
	char		*file;
	char		*file2;
	int			redir;
	char		*bufffer;
	char		*home_dir;
	char		*last_dir;
	char		*cwd;
	char		**path;
	int			hd_trigger;
	char		**input_list;
	int			old_fdin;
	int			old_fdout;
	int			flag_echo_trig;
	int			cd_trigger;
	int			status;
	int			exit_status;
	size_t		hd_it;
	size_t		hd_it_2;
	int			pipe_trig;
	int			sleep_i;
	size_t		i_pipes;
	char		**hd_names;
	size_t		hd_count;
	size_t		suffix;
	int			a_file;
	size_t		nbr_cmd;
	size_t		nbr_input;
	pid_t		*pids;
	char		*tmp;
	int			**pipefds;
	int			*pipefd;
	int			infile;
	int			outfile;
	int			trigger;
	int			i;
	size_t		i_redir;
	size_t		i_cmd;
	size_t		j;
	int			k;
	char		c;
	int			errno;
	size_t		built_in;
	t_vectstr	*vect_env;
	t_vector	*v_path;
	char		**m_cmd;
	char		*full_string;
	char		**env;
	int			check_quotes_space;
	int			checkerino;
	char		buffer[BUFFER_SIZE2];
	int			count_double;
	int			count_single;
	int			check_double;
	int			check_single;
	int			in_q;
	int			too_many_args;
	int			checkerina;
}				t_data;

void		free_before_exit(t_data *s_data);
void		handle_exit_savior(t_data *data);
void		free_pids(t_data *data);
int			core_exec_3(t_data *data, size_t it_cmd, int built_in);
int			pipes_and_redirs_check_3(t_data *data, size_t it_cmd);
int			redirections_3(t_data *data, const struct s_vectint *redir_t,
				char **redir_f);
int			if_stdin_redir_3(t_data *data, int redir_type, char *redir_file);
int			if_stdout_redir_3(t_data *data, int redir_type, char *redir_file);
int			open_file_minishell_3(t_data *data, int type, char *file);
void		run_minishell(char **env, t_vectstr *env_buff,
				t_data *s_data, int *ex_st_buff);
char		*get_input(t_data *s_data);
void		process_input(char *input, t_data *s_data,
				t_vectstr *env_buff, int *ex_st_buff);
t_vector	*init_vector(void);
t_vectstr	*init_vect_str(void);
void		minishell(t_data *data);
int			tmp(char *input, t_data *s_data,
				t_vectstr *env_buff, int *ex_st_buff);
char		*read_from_stdin(t_data *s_data);
void		free_broken_malloc(t_data *s_data);
void		lil_gnl(char *line, char *buffer, size_t *len, ssize_t *bytes_read);
char		*if_failures(char *line, char *buffer,
				size_t *len, ssize_t *bytes_read);
void		infile_or_heredoc(t_data *data, char **env);
void		garbage_destructor_hd(t_data *data);
void		garbage_collector(t_data *data);
void		exec_cmd(t_data *data, char **env, char *cmd);
char		*find_path(char *cmd, char *env[]);
char		*get_env_path(char *env[]);
void		free_paths(char **paths);
char		*construct_path(char *dir, char *cmd);
char		*check_file(t_data *data, char *cmd);
int			there_is_slash(char *cmd);
void		init_data_2(t_data *data);
bool		status(void);
void		core_exec(t_data *data, size_t idx, int built_in);
int			open_file_minishell(t_data *data, int type, char *file);
void		redirections(t_data *data, const struct s_vectint *redir_t,
				char **redir_f);
void		stdout_redir(t_data *data, int redir_type, char *redir_file);
void		heredoc_redir(t_data *data, int redir_type, char *redir_file);
void		stdin_redir(t_data *data, int redir_type, char *redir_file);
void		here_doc_counter(t_data *data);
void		here_doc_detector(t_data *data);
void		here_doc_case(t_data *data, char *limiter);
void		garbage_destructor(t_data *data);
void		mult_cmd_exec(t_data *data);
void		cmds_exec(t_data *data);
void		single_cmd_not_bi_exec(t_data *data);
void		single_bi_cmd_exec(t_data *data);
void		close_pipes(t_data *data);
void		waitpids_and_unlink(t_data *data);
void		pipes_and_redirs_check(t_data *data, size_t it_cmd);
void		if_absolute_cmd(t_data *data);
void		if_relative_cmd(t_data *data);
char		*check_file_1(t_data *data, struct stat *file_stat, char *cmd);
void		if_stdin_redir(t_data *data, int redir_type, char *redir_file);
void		if_heredoc_redir(t_data *data, int redir_type);
void		if_stdout_redir(t_data *data, int redir_type, char *redir_file);
void		here_doc_managing(t_data *data, char *limiter, char *line);
void		init_exec(t_data *data);
void		free_charchar(char **s);
void		free_pipefds(t_data *data);
int			get_open_flags(int type);
void		unlink_hd(t_data *data);
void		sigint_handler_exec(int sig_code);
void		replace_hd_by_stdin(t_data *data, size_t it, size_t it_2);
void		built_in_detector(t_data *data, char *cmd);
void		built_in_manager(t_data *data, char *cmd);
int			b_i_cd(t_data *data, char *cmd);
int			cd_init(t_data *data, char *cmd);
void		free_cd(t_data *data, int trigger);
int			cd_initializer(t_data *data);
int			too_many_args(t_data *data, size_t it, char *cmd);
int			home_or_last_dir_fails(t_data *data);
void		if_abs_or_relative_path(t_data *data);
int			cd_only(t_data *data);
int			get_oldpwd_value(t_data *data);
void		update_oldpwd_env(t_data *data);
char		*get_home_value(t_data *data);
void		swap_dir(t_data *data);
void		variables_initializer(t_data *data);
void		b_i_echo(t_data *data, char *cmd);
int			check_newline_option(char *cmd);
char		*clean_input(t_data *data, char *cmd);
int			flag_is_ok(char *flag);
void		b_i_pwd(t_data *data);
void		debug(t_data *data);
bool		init_prompt(void);
void		sigint_handler(int sig_code);
bool		init_signal(t_type_of_signals type);
int			rl_event_dummy(void);
void		handle_sigquit(int sig_code);
t_data		init_data(char **env, int ex_data_buff, t_vectstr *env_buff);
t_parsed	init_parsed(void);
void		launch_parsing(char *input, t_data *s_data);
void		vectstr_happend(t_vectstr *vect, char *data);
void		vectstr_print(t_vectstr *vect);
void		vectstr_free(t_vectstr *vect);
void		free_t_vector(t_vector *vector);
void		vectint_print(t_vectint *vect);
void		vectint_happend(t_vectint *vect, int number);
void		free_t_data(t_data *data, int check);
void		v_path_double(t_vector *vector);
void		vector_happend(t_vector *vect, char *n);
void		vector_print(t_vector *vect);
t_vectint	*init_vect_int(void);
int			check_spaces(char *input);
void		setup_signal_handlers(void);
void		send_builtin(t_data *s_data);
t_vectstr	*init_vect_str(void);
void		init_env(t_vectstr *vect_env, char **env);
t_vectstr	*vectstr_dup(t_vectstr *vect);
void		free_t_vectstr(t_vectstr *vect);
void		*ft_realloc(void *ptr, size_t capacity,
				size_t size, size_t elemSize);
void		builtin_unset(t_data *data, char *cmd);
void		builtin_exit(t_data *s_data, char *cmd);
void		builtin_env(t_data *s_data);
void		builtin_export(t_data *s_data);
int			ft_isspace(char c);
int			check_chevron(t_data *s_data);
bool		vect_append_command(int *i, int *j, int *x, t_data *s_data);
void		path_to_vect(t_data *s_data, int i);
int			is_this_ok(t_data *s_data);
int			handle_characters(t_data *s_data, char *to_add, int *i, int *x);
int			append_redir_here(t_data *s_data, int i);
int			search_n_append(t_data *s_data, char *check_var,
				char *str, int x_prev);
void		handle_characters_qotes(t_data *s_data, char *to_add,
				int *i, int *x);
int			manage_chevron(t_data *s_data, int prev_i);
int			append_redir(t_data *s_data, int i);
int			handle_exit_code(t_data *s_data, char *str, int x);
int			handle_variable_expansion(t_data *s_data, const char *s,
				int i, int *x);
int			handle_double_quotes(t_data *s_data, const char *s, int i, int *x);
int			handle_exit_code(t_data *s_data, char *str, int x);
void		fill_command(t_data *s_data, int *i, int *x);
void		handle_simple_quotes(int *i, int *x, t_data *s_data);
void		skip_whitespaces(t_data *s_data, int *it);
int			ft_strncmp_index(const char *s1, const char *s2,
				size_t n, size_t start_index);
void		replace_variable(t_vectstr *env, char *to_add, int i);
int			check_presence(t_data *s_data, char *to_check);
void		print_export(t_data *s_data);
void		free_t_vectint(t_vectint *vect);
int			check_args_ex(char *cmd, t_data *data);
long long	c_toll(const char *str);
char		**ft_split_sa(const char *s);
void		clean_quotes(char **strings);
void		eat_whitespace(char const *s, int *i);
int			check_empty_pipes(t_data *s_data);
int			check_equal(t_data *s_data, char *s);

#endif
