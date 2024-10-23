/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:30:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:04:57 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

static void	check_free_perror(t_prompt_info *info, char *new_word,
		char *err_msg)
{
	if (new_word != NULL)
		free(new_word);
	minishell_yourser_perror(info, err_msg);
}

static char	*expand_variable_step(t_prompt_info *info, char **word_ptr,
		char *new_word)
{
	char	*word;

	word = *word_ptr;
	if (*word == SINGLE_QUOTE)
		new_word = e_v_s_q(info, word_ptr, new_word);
	else if (*word == DOUBLE_QUOTE)
		new_word = e_v_d_q(info, word_ptr, new_word);
	else if (is_variable(word))
		new_word = expand_variable_word(info, word_ptr, new_word);
	else if (is_special_parameter(word))
		new_word = expand_special_parameter(info, word_ptr, new_word);
	else if (variable_error_check(word))
		check_free_perror(info, new_word, "valeable need alpha or under");
	else
	{
		new_word = append_char(new_word, *word);
		(*word_ptr)++;
	}
	return (new_word);
}

void	expand_variable(t_prompt_info *info, t_token_info *token)
{
	char	*word;
	char	*new_word;

	word = token->word;
	new_word = NULL;
	while (*word)
	{
		new_word = expand_variable_step(info, &word, new_word);
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
