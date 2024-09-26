/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:37:11 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/25 17:32:43 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_meta(char c)
{
	if (c && ft_strchr("|&;()<> \t\n", c))
		return (true);
	return (false);
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
	return (prompt);
}

bool	is_same_top(char *s, char *keyword)
{
	if (memcmp(s, keyword, strlen(keyword)) == 0)
		return (true);
	;
	return (false);
}

bool	is_operand(char *prompt)
{
	size_t	i;
	char	*operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n","<",">"};

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_same_top(prompt, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

char	*malloc_op(char *prompt)
{
	char	*op_str;
	char	*operators[] = {"||", "&&", "&", ";;", ";", "(", ")", "|", "\n","<",">"};
	size_t	i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_same_top(prompt, operators[i]))
			break ;
		i++;
	}
	op_str = ft_strdup(operators[i]);
	return (op_str);
}

t_token_info	*make_operand_token(char *prompt)
{
	t_token_info	*new_token;
	char			*op_str;

	op_str = malloc_op(prompt);
	new_token = (t_token_info *)ft_calloc(1, sizeof(t_token_info));
	new_token->word = op_str;
	new_token->kind = OP;
	new_token->next = NULL;
	return (new_token);
}

//めた文字がくる前に'がきた場合は、'が来るまでwordとする。
////コンティニューとか使っても面白いかもね。
t_token_info	*make_word_token(char *prompt)
{
	int				i;
	t_token_info	*new_token;
	char			*word_str;

	//先頭からどこまでコピーするかサイズを考える。
	i = 0;
	while (prompt[i] && !is_meta(prompt[i]))
	{
		if(prompt[i]=='\'')//singl qout;
		{
			i++;
			while(prompt[i]!='\'')//'が来るまで全てskip
				i++;
		}
		
		if(prompt[i]=='\"')//singl qout;
		{
			i++;
			while(prompt[i]!='\"')//'が来るまで全てskip
				i++;
		}
		
		i++;
	}
	word_str = ft_calloc(i + 1, sizeof(char));
	word_str = strncpy(word_str, prompt, i);
	new_token = (t_token_info *)ft_calloc(1, sizeof(t_token_info));
	new_token->word = word_str;
	new_token->kind = WORD;
	new_token->next = NULL;
	return (new_token);
}

t_token_info	*make_eof_token(void)
{
	t_token_info	*new_token;

	new_token = (t_token_info *)ft_calloc(1, sizeof(t_token_info));
	new_token->word = NULL;
	new_token->kind = ROF;
	new_token->next = NULL;
	return (new_token);
}

t_token_info	*make_token(char *prompt, t_token_info *parent_tk)
{
	t_token_info	*token;

	if (is_operand(prompt))
		token = make_operand_token(prompt);
	//	else if (is_reserved(prompt))
	//		token = make_reserved_token(prompt);
	else
		token = make_word_token(prompt);
	parent_tk->next = token;
	return (token);
}

//呼び出し元で
// origin_prompt = prompt; //別にいらないかも、ここでfreeする必要もないし戻る(
t_token_info	*tokenizer(t_prompt_info *info, char *prompt)
{
	t_token_info	root_tk;
	t_token_info	*token;
	int				set_size;

	token = &root_tk;
	while (*prompt)
	{
		prompt = space_skip(prompt);
		if (*prompt == '\0')
			break ;
		token = make_token(prompt, token);
		if (token == NULL)
		{
			set_size = 1;
			error_set_print("error_occurd", 0, info);
		}
		else
			set_size = ft_strlen(token->word);//うわお、これりゃ
		prompt += set_size;
	}
	token->next = make_eof_token();
	return (root_tk.next);
}
