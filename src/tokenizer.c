/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:37:11 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/16 11:16:55 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//ダブルポインターオペランドの示している。サーチすればいい、
#define META "\t\n|&;()<>"
#define OPERAND "||", "&", "&&", ";", ";;", "(", ")", "|", "\n"

enum						e_token_kind
{
	RESERVE,
	WORD,
	OP,
	ROF,
};

typedef enum e_token_kind	e_kind;

typedef struct s_token		t_token;

struct						s_token
{
	char					*word;
	e_kind					kind;
	t_token					*next;
}

// unitの作成

t_token *
make_unit_token(void)
{
	return (t_token *)ft_calloc(1, sizeof(t_token));
}

int	is_c_meta(char c)
{
	if (c && ft_strchr(META, c))
		return (sizeof(c));
	return (0);
}

void	meta_prosecc(char *prompt)
{
	prompt++;
}

char	*space_skip(char *prompt)
{
	while (*prompt)
	{
		if (*prompt == ' ' || *prompt == '\t')
			prompt++;
		else
			return (prompt);
	}
}

t_token_info	*prompt_set(char *prompt)
{
	t_token_info	*token;

	if (is_operand(prompt))
		token = make_operand_token(prompt);
	else if (is_reserved(prompt))
		token = make_reserved_token(prompt);
	else
	{
		token = make_reserver_token(prompt);
		return (token);
	}
}

t_token	*tokenizer(t_prompt_info *info, t_token_info *token, char *prompt)
{
	t_token_info	*new_token;
	char			*origin_prompt;
	int				set_size;

	i = 0;
	origin_prompt = prompt;
	while (*prompt)
	{
		prompt = space_skip(prompt);
		if (*prompt == '\0')
			break ;
		new_token = token_set(prompt); //必ずトークンは作られて欲しい
		if (new_token == NULL)         //ここで何らかのエラーとしよう
		{
			set_size = 1;
			error_set("error_occurd", 0, info);
		}
		set_size = ft_strlen(new_token->word);
		prompt += set_size;
	}
	EOF_token();
	return (token);
}
