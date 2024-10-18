/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:33:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/18 17:19:19 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>


#define HEREDOC 1
#define HEREDOC_PARENT 2
#define IN_CMD 3
#define SIG_INT 4


# define FALSE 0
# define TRUE 1

# define YOURSER_ERROR 0
# define SYSTEM_ERROR 1


#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '\"'

# define OPERATORS                                                             \
	{                                                                         \
		"||", "&&", "&", ";;", ";", "(", ")", "|", "\n", "<<", ">>", "<", ">" \
	}

extern char						**environ;
extern volatile sig_atomic_t	g_sig_status;

typedef struct s_item			t_item;

struct							s_item
{
	char						*name;
	char						*value;
	t_item						*next;
};

typedef struct s_map
{
	t_item						*item;
	char						**envp;
}								t_map;

typedef struct s_prompt_info
{
	char						*str;
	t_map						*map;
	int							last_status;
	int							yourser_err;
	int							shell_finish;

}								t_prompt_info;

enum							e_token_kind
{
	RESERVE,
	WORD,
	OP,
	ROF,
};

typedef enum e_token_kind		e_kind;

typedef struct s_token			t_token_info;

struct							s_token
{
	char						*word;
	e_kind						kind;
	t_token_info				*next;
};

enum							e_node_kind
{
	ND_PIPE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};
typedef enum e_node_kind		t_node_kind;

typedef struct s_node			t_node_info;

struct							s_node
{
	t_node_kind					kind;

	// pipe_node
	t_node_info					*re_node;
	int							inpipe[2];
	int							outpipe[2];

	// cmd_node
	t_node_info					*cmd;
	t_token_info				*node_token;

	// redirects_node
	t_node_info					*redirects;
	int							targetfd;
	t_token_info				*filename;
	t_token_info				*delimiter;
	int							filefd;
	int							stashedfd;
	bool		is_delim_unquoted;
};

typedef struct s_operation_info
{
	t_token_info				*token;
	t_node_info					*node;
}								t_operation_info;



/////////////////////////////////
//signal
/////////////////////////////////
void	handler(int signum);
void	ready_signal(void);
void	init_signal(void);
///////////////////////////////
//info_data
void	info_null_init(t_prompt_info *info);
void	info_envp2item(t_prompt_info *info, char **envp);
void	info_map_init(t_prompt_info *info, char **envp);
void	info_init(t_prompt_info *info, char **envp);
///////////////////////////////
//shell_map
///////////////////////////////
//main
bool	is_identifier(const char *s);
t_item	*make_unit_item(const char *name, const char *value);
t_map	*minishell_make_map(void);
char	*search_value(t_item *item, const char *find_name);
char	*item_value_get(t_map *map, const char *find_name);
//shell_map_set_unset
void	item_set(t_map *map, const char *name, const char *value);
int	item_unset(t_map *map, const char *name);
void	item_put(t_prompt_info *info, t_map *map, const char *string,
		bool empty_value);
//shell_map_utils.c
size_t	item_len(t_item *item, bool null_value_flag);
char	*get_variable_str(const char *name, const char *value);
char	**item2argv(t_item *item);
/////////////////////////////////
// tokenizer
// ////////////////////////////
// main
t_token_info					*tokenizer(t_prompt_info *info, char *prompt);
char							*space_skip(char *prompt);
// tokenizer_make_token
t_token_info					*make_token(t_prompt_info *info, char **prompt,
									t_token_info *parent_tk);
t_token_info					*make_eof_token(void);
t_token_info					*make_word_token(t_prompt_info *info,
									char *prompt);
void							init_operators(char **operators);

// tokenizer_make_token_utils
int								recive_double_qout(t_prompt_info *info,
									char *prompt, int i);
int								recive_single_qout(t_prompt_info *info,
									char *prompt, int i);
t_token_info					*make_operand_token(char *prompt);
char							*malloc_op(char *prompt);
// tokenizer_utils
int								token_size(t_token_info *token);
char							**token2argv(t_token_info *token);
bool							is_meta(char c);
bool							is_same_top(char *s, char *keyword);
bool							is_operand(char *prompt);
////////////////////////////////
//parser
////////////////////////////////
// main
t_node_info	*make_node(void);
t_node_info	*prompt_parser(t_prompt_info *info, t_token_info *token);
t_token_info	*find_pipe(t_token_info *token);
t_node_info	*parser(t_prompt_info *info, t_token_info *token);
//parser_append
t_token_info	*redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
t_token_info	*op_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
void	word_token(t_node_info *node, t_token_info *token);
void	eof_token(t_node_info *node);
t_token_info	*append_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
//parser_append_redirect
t_token_info	*output_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);

t_token_info	*input_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
t_token_info	*append_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
t_token_info	*heredoc_redirect_node(t_prompt_info *info, t_node_info *node,
		t_token_info *token);
//parser_append_utils
t_token_info	*ft_tokendup(t_token_info *token);
void	token_append_tail(t_node_info *node, t_token_info *cp_token);
int	type_redirect_op(t_token_info *token);
int	is_pipe_op(t_token_info *token);
void	redirect_append_tail(t_node_info *node, t_node_info *append_redirect);
//////////////////////////////////////
//expand
////////////////////////////////////////
//main
void	expand(t_prompt_info *info, t_node_info *node);
//expand_memory_utils
char	*ft_char_recalloc(char *old, size_t count);
char	*append_char(char *old, char append_c);
//expand_expander
void	expand_variable(t_prompt_info *info, t_token_info *token);
void	token_variable_expand(t_prompt_info *info, t_token_info *token);
void	variable_expander(t_prompt_info *info, t_node_info *node);
//expand_expander_element
bool	variable_error_check(char *word);
char	*expand_special_parameter(t_prompt_info *info, char **word,
		char *new_word);
char	*expand_variable_word(t_prompt_info *info,char **word, char *new_word);
char	*expand_variable_single_quote(t_prompt_info *info, char **word,
		char *new_word);
char	*expand_variable_double_quote(t_prompt_info *info, char **word,
		char *new_word);
//expand_expander_utils
bool	is_alpha_or_under(char c);
bool	is_alpha_or_under_or_digit(char c);
bool	is_variable(char *word);
bool	is_special_parameter(char *word);
char	*append_num(char *new_word, int num);
//expand_remover
char	*remove_single_quote(t_prompt_info *info,char **word_ppt, char *new_word);
char	*remove_double_quote(t_prompt_info *info,char **word_ppt, char *new_word);
void	remove_quote(t_prompt_info *info,t_token_info *token);
void	token_quote_removal(t_prompt_info *info,t_token_info *token);
void	quote_remover(t_prompt_info *info,t_node_info *node);
////////////////////////////////////
//redirect
///////////////////////////////////
//redirect_prepare
void	redirect_type_init(t_prompt_info *info, t_node_info *redirect);
void	init_redirect(t_prompt_info *info, t_node_info *cmd_node);
void	prepare_redirect(t_prompt_info *info, t_node_info *node);
//redirect_preparer_element
void	redirect_out_init(t_prompt_info *info, t_node_info *redirect);
void	redirect_in_init(t_prompt_info *info, t_node_info *redirect);
void	redirect_append_init(t_prompt_info *info, t_node_info *redirect);
void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect);
//heredoc
//char	*expand_heredoc_line(t_prompt_info *info, char *word)
//void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect);
//rediredt_do_and_reset
void	redirect_do_set(t_node_info *redirect);
void	do_redirect(t_node_info *redirect_node);
bool	is_redirect(t_node_info *node);
void	do_reset_redirect(t_node_info *node);
//////////////////////////////////////////////
//exec
//////////////////////////////////////////////
int	wait_all_processes(int last_pid);
void	exec(t_prompt_info *info, t_node_info *node);
//////////////////////////////////////////////
//ecec_mlt_process
//////////////////////////////////////////////
void	err_exit(const char *msg, int status);
void	validate_access(const char *path, const char *filename);
void	child_process(t_prompt_info *info, t_node_info *node);
void	close_final_pipe(t_node_info *node);
int	command_comunication(t_prompt_info *info, t_node_info *node);
////////////////////////////////////
//path_finder
////////////////////////////////////
char	*cut_and_move_env(char **path_env);
char	*make_command_path(char *command, char *unit_path);
char	*path_get(t_prompt_info *info,char *command);
////////////////////////////////////
///pipe
////////////////////////////////////
void	prepare_pipe(t_prompt_info *info,t_node_info *node);
void	prepare_pipe_child(t_node_info *node);
void	prepare_pipe_parent(t_node_info *node);
////////////////////////////////////
//builtin
///////////////////////////////////
//main
bool	is_numeric(char *s);
bool	is_builtin(t_node_info *node);
void	exec_builtin(t_prompt_info *info, t_node_info *node);
//builtin_cd
bool check_skip_path(char **path_ppt,char *path,char *check_str);
void delete_last_path_element(char *path);
void append_path_element(char *new_pwd,char **path_ppt,char *path);
char	*make_pwd(char *old_pwd, char *path);
int	builtin_cd(t_prompt_info *info, char **argv);
//builtin_echo
int	builtin_echo(t_prompt_info *info, char **argv);
//builtin_env
int	builtin_env(t_prompt_info *info);
//builtin_exit
int	builtin_exit(t_prompt_info *info, char **argv);
//builtin_export
void	print_all_env(t_prompt_info *info);
int	builtin_export(t_prompt_info *info, char **argv);
//builtin_pwd
bool	equal_path(const char *path1, const char *path2);
int	builtin_pwd(t_prompt_info *info, char **argv);
//builtin_unset
int	builtin_unset(t_prompt_info *info, char **argv);

/////////////////////////////////
//free
////////////////////////////////
//free_operation
void	token_free(t_token_info *token);
void	node_free(t_node_info *node);
void	free_operation(t_operation_info operation);
//free
void	clear_info(t_prompt_info *info);
void	map_free(t_map *map);
void	ppt_free(char **ppt);
void	item_free(t_item *item);
/////////////////////////////////
// error_utils
/////////////////////////////////
void							perror_prestr(void);
void							fatal_error_exit(char *err_msg);
void							tokenizer_error(t_prompt_info *info,
									char *err_msg);
void							parser_error(t_prompt_info *info,
									char *token_word);
void							minishell_perror(t_prompt_info *info,
									char *err_msg);
void							minishell_yourser_perror(t_prompt_info *info,
									char *err_msg);
void							yourser_error_exit(char *err_msg);
/////////////////////////////////
// free_utils
/////////////////////////////////
void							token_free(t_token_info *token);
void							node_free(t_node_info *node);
void							free_operation(t_operation_info operation);
void							clear_info(t_prompt_info *info);
void							item_free(t_item *item);

/////////////////////////////////
// shell_refunc
/////////////////////////////////
char *ft_strncpy(char *dest, const char *src, size_t n);
int ft_strcmp(const char *s1, const char *s2);
void							*minishell_malloc(size_t size);
void							*minishell_calloc(size_t count, size_t size);
char							*minishell_strdup(const char *s1);
char							*minishell_strndup(const char *s, size_t len);
/////////////////////////////////
/////////////////////////////////


#endif
