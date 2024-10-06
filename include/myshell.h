/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:33:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/06 18:07:40 by hosokawa         ###   ########.fr       */
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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1

# define YOURSER_ERROR 0
# define SYSTEM_ERROR 1

extern char					**environ;

typedef struct s_item		t_item;

struct						s_item
{
	char					*name;
	char					*value;
	t_item					*next;
};

typedef struct s_map
{
	t_item					*item;
	char					**environment;
}							t_map;

typedef struct s_prompt_info
{
	char *str; // prompt
	int						shell_finish;
	int						last_status;
	int						yourser_err;
	t_map					*map;

}							t_prompt_info;
// tokenizer_header
enum						e_token_kind
{
	RESERVE,
	WORD,
	OP,
	ROF,
};

typedef enum e_token_kind	e_kind;

typedef struct s_token		t_token_info;

struct						s_token
{
	char					*word;
	e_kind					kind;
	t_token_info			*next;
};

///
/// parser_header
enum						e_node_kind
{
	ND_PIPE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
};
typedef enum e_node_kind	t_node_kind;

typedef struct s_node		t_node_info;

struct						s_node
{
	t_node_kind				kind;

	// pipe_node
	t_node_info				*re_node;
	int						inpipe[2];
	int						outpipe[2];

	// cmd_node
	t_node_info				*cmd;
	t_token_info			*node_token;

	// redirects_node
	t_node_info				*redirects;
	int						targetfd;
	t_token_info			*filename;
	t_token_info			*delimiter;
	int						filefd;
	int						stashedfd;
};

typedef struct s_operation_info
{
	t_token_info			*token;
	t_node_info				*node;
}							t_operation_info;

// error_utils
void						perror_prestr(void);
void						fatal_error_exit(char *err_msg);
void						tokenizer_error(t_prompt_info *info, char *err_msg);
void						parser_error(t_prompt_info *info, char
								* token_word);
// free_utils
void						token_free(t_token_info *token);
void						node_free(t_node_info *node);
void						free_operation(t_operation_info operation);

// shell_refunc
void						*minishell_malloc(size_t size);
void						*minishell_calloc(size_t count, size_t size);

// pipe
void						prepare_pipe(t_node_info *node);
void						prepare_pipe_child(t_node_info *node);
void						prepare_pipe_parent(t_node_info *node);

// prompt_info_func
void						info_init(t_prompt_info *info, char **envp);

// path_finder
char						*path_get(char *command);

// tokenizer
t_token_info				*tokenizer(t_prompt_info *info, char *prompt);
t_token_info				*make_eof_token(void);
// token_utils
char						**token2argv(t_token_info *token);

// expand
void						expand(t_node_info *token);

// parser
t_node_info					*parser(t_prompt_info *info,t_token_info *token);

// redirect
void						do_redirect(t_node_info *node);
void						prepare_redirect(t_node_info *node);
void						reset_redirect(t_node_info *node);

// is_identifier
bool						is_alpha_or_under(char c);
bool						is_alpha_or_under_or_digit(char c);
bool						is_variable(char *word);
bool						is_identifier(const char *s);

// shell_map
t_item						*make_unit_item(const char *name,
								const char *value);
t_map						*make_map(void);
char						*search_value(t_item *item, const char *find_name);
char						*item_value_get(t_map *map, const char *find_name);
int							item_set(t_map *map, const char *name,
								const char *value);
int							item_unset(t_map *map, const char *name);
int							item_put(t_map *map, const char *string,
								bool empty_value);

#endif
