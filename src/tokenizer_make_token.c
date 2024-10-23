/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_make_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:10:34 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 12:15:16 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

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
	ft_strlcpy(word_str, prompt, i + 1);
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
