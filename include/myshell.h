/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:33:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/18 09:06:09 by hosokawa         ###   ########.fr       */
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

typedef struct s_prompt_info
{
	char *str; // prompt
	char					**cmd_argv;
	char **envp; //環境
	int						status;

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
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
};
typedef enum e_node_kind	t_node_kind;

typedef struct s_node		t_node_info;

struct						s_node
{
	t_node_kind				kind;
	t_node					*next;
	// CMD
	t_token					*args;
	t_node					*redirects;
	// REDIR
	int						targetfd;
	t_token					*filename;
	int						filefd;
	int						stashed_targetfd;
};

// error_utils
void						error_set(char *err_msg, int error_type,
								t_prompt_info *info);

// prompt_info_func
void						info_init(t_prompt_info *info, char **envp);

// path_finder
char						*path_get(char *command);

// tokenizer
t_token_info				*tokenizer(t_prompt_info *info, char *prompt);
t_token_info				*make_eof_token(void);
// token_utils
char						**token2argv(t_token_info *token);

// parser
t_node_info					*parser(t_token_info *token);

#endif
