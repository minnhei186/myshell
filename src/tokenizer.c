/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:37:11 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/06 16:44:07 by hosokawa         ###   ########.fr       */
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
	char	*operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n",
			"<", ">"};

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
	char	*operators[] = {"||", "&&", "&", ";;", ";", "(", ")", "|", "\n",
			"<", ">"};
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

int	recive_single_qout(t_prompt_info *info, char *prompt, int i)
{
	if (prompt[i] == '\'')
	{
		i++;
		while (prompt[i] != '\'')
		{
			if (prompt[i] == '\0')
			{
				tokenizer_error(info, "not_close_single_qouat");
				return -1;
			}
			i++;
		}
	}
	return (i);
}

int	recive_double_qout(t_prompt_info *info, char *prompt, int i)
{
	if (prompt[i] == '\"')
	{
		i++;
		while (prompt[i] != '\"')
		{
			if (prompt[i] == '\0')
			{
				tokenizer_error(info, "not_close_double_qouat");
				return -1;
			}
			i++;
		}
	}
	return (i);
}

// promptのポインタは独立
t_token_info	*make_word_token(t_prompt_info *info, char *prompt)
{
	int				i;
	t_token_info	*new_token;
	char			*word_str;

	i = 0;
	while (prompt[i] && !is_meta(prompt[i]))
	{
		i = recive_single_qout(info, prompt, i);
		if (info->yourser_err == 1)
			return (NULL);
		i = recive_double_qout(info, prompt, i);
		if (info->yourser_err == 1)
			return (NULL);
		if (prompt[i] != '\0')
			i++;
	}
	word_str = minishell_calloc(i + 1, sizeof(char));
	//word_str = strncpy(word_str, prompt, i);
	ft_strlcpy(word_str, prompt, i+1);//必ず成功
	new_token = (t_token_info *)minishell_calloc(1, sizeof(t_token_info));
	new_token->word = word_str;
	new_token->kind = WORD;
	new_token->next = NULL;
	return (new_token);
}

t_token_info	*make_eof_token(void)
{
	t_token_info	*new_token;

	new_token = (t_token_info *)minishell_calloc(1, sizeof(t_token_info));
	new_token->word = NULL;
	new_token->kind = ROF;
	new_token->next = NULL;
	return (new_token);
}

t_token_info	*make_token(t_prompt_info *info, char **prompt,
		t_token_info *parent_tk)
{
	t_token_info	*token;
	int				set_size;

	if (is_operand(*prompt))
		token = make_operand_token(*prompt);
	else
		token = make_word_token(info, *prompt);
	if (info->yourser_err == 1)
	{
		parent_tk->next = make_eof_token();
		while (**prompt)
			*prompt += 1;
		return (NULL);
	}
	parent_tk->next = token;
	set_size = ft_strlen(token->word);
	(*prompt) = (*prompt) + set_size;
	return (token);
}

t_token_info	*tokenizer(t_prompt_info *info, char *prompt)
{
	t_token_info	root_tk;
	t_token_info	*token;

	root_tk.word = NULL;
	root_tk.kind = 0;
	root_tk.next = NULL;
	token = &root_tk;
	while (*prompt)
	{
		prompt = space_skip(prompt); 
		if (*prompt == '\0')
			break ;
		token = make_token(info, &prompt, token);
		if (info->yourser_err == 1)
			return (root_tk.next);
	}
	token->next = make_eof_token();
	return (root_tk.next);
}
