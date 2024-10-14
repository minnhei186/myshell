/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:30:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 15:15:16 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	expand_variable(t_prompt_info *info, t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		if (*word == SINGLE_QUOTE)
			new_word = expand_variable_single_quote(info, &word, new_word);
		else if (*word == DOUBLE_QUOTE)
			new_word = expand_variable_double_quote(info, &word, new_word);
		else if (is_variable(word))
			new_word = expand_variable_word(&word, new_word);
		else if (is_special_parameter(word))
			new_word = expand_special_parameter(info, &word, new_word);
		else if (variable_error_check(word))
		{
			if (new_word != NULL)
				free(new_word);
			minishell_yourser_perror(info,
				"Variable must starts with alpha or underscore");
		}
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

void	token_variable_expand(t_prompt_info *info, t_token_info *token)
{
	if (token == NULL)
		return ;
	while (token != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
		{
			expand_variable(info, token);
			if (info->yourser_err)
				return ;
		}
		token = token->next;
	}
}

void	variable_expander(t_prompt_info *info, t_node_info *node)
{
	if (node == NULL)
		return ;
	token_variable_expand(info, node->node_token);
	if (info->yourser_err)
		return ;
	token_variable_expand(info, node->filename);
	if (info->yourser_err)
		return ;
	variable_expander(info, node->redirects);
	if (info->yourser_err)
		return ;
	variable_expander(info, node->cmd);
	if (info->yourser_err)
		return ;
	variable_expander(info, node->re_node);
	if (info->yourser_err)
		return ;
}
