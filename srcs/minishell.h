/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:29:48 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/24 00:01:35 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

# define MINISHELL "Minishell $ "
# define HEREDOC "> "

enum e_token_type {
	UNDEFINED,
	STR,
	FILE_IN,
	HEREDOC_IN,
	FILE_OUT,
	FILE_OUT_CONCAT
};

typedef struct s_block	t_block;
typedef struct s_token	t_token;
typedef struct s_shell	t_shell;

typedef struct s_block
{
	int		pid;
	char	*heredoc;
	t_block	*next;
	t_block	*before;
	t_token	*first_token;
}				t_block;

typedef struct s_token
{
	t_token	*next;
	t_token	*before;
	char	*str;
	int		type;
	int		fd[2];
}				t_token;

typedef struct s_execline
{
	t_shell	*shell;
	t_block	*first_block;
	int		*pipes;
}				t_execline;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
	char	exittxt[20];
	int		exit;
}				t_shell;

// UTILS

void		ft_itoa_spe(int n, char *str);
int			ft_strstartwith(char *s1, char *s2);
size_t		ft_istrchr(char *str, char c);
int			ft_strchr_i(char *s, int c);
char		*ft_strchr(char *s, int c);
char		*ft_substr(char *s, int start, int len);
int			ft_iswhitespace(char c);
void		skip_whitespaces(char **str);
int			ft_isinset(char *set, char c);
char		*get_next_line(int fd);
int			ft_strdiff(char *s1, char *s2);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strndup(char *str, size_t n, int free_str);
char		**ft_split(char *str, char *charset);
void		free_split(char **split);
int			ft_printf_return(char *txt, int r);
int			ft_printerror(char *s);
int			ft_isdigit(char c);
int			ft_isalpha(char c);
int			ft_isalphanum(char c);
int			ft_isalphanumus(char c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strdup(char *s);
int			ft_strequ(char *s1, char *s2);
void		ft_free_array(char **array);

// ENTITIES

	// EXECLINE

t_execline	init_execl(void);
t_execline	*malloc_execl(void);
void		free_execl(t_execline *execl);

	// BLOCK

t_block		init_block(void);
t_block		*malloc_block(void);
void		free_block(t_block *block);
int			get_index_block(t_block *block);

	// TOKEN

t_token		init_token(void);
t_token		*malloc_token(void);
t_token		*get_token_at_index(t_token *token, int type, int index);
void		free_token(t_token *token);

	// SHELL

void		free_shell(t_shell *shell);

// PARSING

	// EXECLINE

t_execline	*parse_execline(char *str, t_shell *shell);
void		debug_parsing(t_execline *execl);

	// BLOCK

int			parse_block(t_execline *execl, char **str, t_shell *shell);

	// TOKEN

int			is_end_of_token(char c);
int			count_token_str(char *str);
int			parse_token(t_block *block, char **str, t_shell *shell);
int			create_token_str(t_token *token, char **str);

	// HERDOC

int			fill_herdoc(t_token *token, t_shell *shell);
void		close_herdocs_files_fds(t_execline *execl);

	// MAKE PIPES

int			make_pipes(t_execline *execl);

	// GLOBAL

t_execline	*parse(char *str, t_shell *minishell);

	// TRANSLATE ENV

int			check_quotes(char *str);
char		*translate_env(char *str, t_shell *minishell);

// EXECUTION

	// LOOP

void		loop(t_shell *minishell);

	// EXECUTE

int			execute(t_execline *execl);
int			close_pipes(t_execline *execl);
char		**extract_argv(t_block *block);

	// BLOCK

void		execute_block(t_block *block, t_shell *minishell);

	// CHILD

int			open_error(t_token *token, int way, int *status);
int			redirect_to_files(t_block *block, int *status);
int			redirect_in_out(t_execline *execl, t_block *block);
int			child_exec(t_execline *execl, t_block *block);

	// FRONT EXEC

int			has_to_front_exec(t_execline *execl);
int			execute_front(t_execline *execl);

// BUILTINS
//is_a_builtin
int			is_a_builtin(char *arg);
int			launch_builtin(char *prgm, char **av, char ***envp);

//pwd
int			pwd(void);

//echo
int			echo(char **av, char **envp);

//env
size_t		get_env_count(char **envp);
int			set_env(char *env, char *new_env, char **envp);
char		**realloc_env(size_t size, char **envp, int to_free);
ssize_t		find_env(char *env, char **envp);
int			print_env(char **env);
char		*get_env(char *name, char **env);

//cd
int			cd(char **av, char **envp);

//export
char		**dup_env(char **envp);
int			ft_export(char **av, char ***envp);
void		sort_env(char **envp);
int			check_export_name(char *av);

//unset
int			unset(char **arg, char ***envp);

//exit
int			mini_exit(char **arg);

// SIGNALS

void		sigint_handler(int sign_num);

#endif