/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:38:02 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 14:39:42 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*remove_single_quote(char **word_ppt, char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != SINGLE_QUOTE)
	{
		new_word = append_char(new_word, **word_ppt);
		if (new_word == NULL)
			return (NULL);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

char	*remove_double_quote(char **word_ppt, char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != DOUBLE_QUOTE)
	{
		new_word = append_char(new_word, **word_ppt);
		if (new_word == NULL)
			return (NULL);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

void	remove_quote(t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		if (*word == SINGLE_QUOTE)
			new_word = remove_single_quote(&word, new_word);
		else if (*word == DOUBLE_QUOTE)
			new_word = remove_double_quote(&word, new_word);
		else
		{
			new_word = append_char(new_word, *word);
			word++;
		}
	}
	free(token->word);
	token->word = new_word;
}

void	token_quote_removal(t_token_info *token)
{
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
			remove_quote(token);
		token = token->next;
	}
}

void	quote_remover(t_node_info *node)
{
	if (node == NULL)
		return ;
	token_quote_removal(node->node_token);
	token_quote_removal(node->filename);
	token_quote_removal(node->delimiter);
	quote_remover(node->redirects);
	quote_remover(node->cmd);
	quote_remover(node->re_node);
}
