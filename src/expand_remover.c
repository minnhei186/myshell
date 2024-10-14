/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:38:02 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 16:28:43 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*remove_single_quote(t_prompt_info *info, char **word_ppt,
		char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != SINGLE_QUOTE)
	{
		if (**word_ppt == '\0')
		{
			minishell_yourser_perror(info, "not_close_double_quote");
			free(new_word);
			return (NULL);
		}
		new_word = append_char(new_word, **word_ppt);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

char	*remove_double_quote(t_prompt_info *info, char **word_ppt,
		char *new_word)
{
	(*word_ppt) = (*word_ppt) + 1;
	while (**word_ppt != DOUBLE_QUOTE)
	{
		if (**word_ppt == '\0')
		{
			minishell_yourser_perror(info, "not_close_double_quote");
			free(new_word);
			return (NULL);
		}
		new_word = append_char(new_word, **word_ppt);
		(*word_ppt) = (*word_ppt) + 1;
	}
	(*word_ppt) = (*word_ppt) + 1;
	return (new_word);
}

void	remove_quote(t_prompt_info *info, t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		if (*word == SINGLE_QUOTE)
			new_word = remove_single_quote(info, &word, new_word);
		else if (*word == DOUBLE_QUOTE)
			new_word = remove_double_quote(info, &word, new_word);
		else
		{
			new_word = append_char(new_word, *word);
			word++;
		}
		if (info->yourser_err)
			return ;
	}
	free(token->word);
	token->word = new_word;
}

void	token_quote_removal(t_prompt_info *info, t_token_info *token)
{
	if (token == NULL)
		return ;
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
		{
			remove_quote(info,token);
			if (info->yourser_err)
				return ;
		}
		token = token->next;
	}
}

void	quote_remover(t_prompt_info *info, t_node_info *node)
{
	if (node == NULL)
		return ;
	token_quote_removal(info,node->node_token);
	if (info->yourser_err)
		return ;
	token_quote_removal(info,node->filename);
	if (info->yourser_err)
		return ;
	token_quote_removal(info,node->delimiter);
	if (info->yourser_err)
		return ;
	quote_remover(info,node->redirects);
	if (info->yourser_err)
		return ;
	quote_remover(info,node->cmd);
	if (info->yourser_err)
		return ;
	quote_remover(info,node->re_node);
	if (info->yourser_err)
		return ;
}
