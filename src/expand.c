/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/30 15:51:22 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	remove_single_quote(char *new_word, char *old_word, int *i, int *j)
{
	*i = (*i) + 1;
	while (old_word[*i] != '\'')
	{
		new_word[*j] = old_word[*i];
		*j = (*j) + 1;
		*i = (*i) + 1;
	}
	*i = (*i) + 1;
}

void	remove_double_quote(char *new_word, char *old_word, int *i, int *j)
{
	*i = (*i) + 1;
	while (old_word[*i] != '\"')
	{
		new_word[*j] = old_word[*i];
		*j = (*j) + 1;
		*i = (*i) + 1;
	}
	*i = (*i) + 1;
}

void	remove_quote(t_token_info *token)
{
	char	*new_word;
	char	*old_word;
	int		i;
	int		j;

	old_word = token->word;
	i = strlen(old_word);
	new_word = calloc(i + 1, sizeof(char));
	i = 0;
	j = 0;
	while (old_word[i])
	{
		if (old_word[i] == '\'')
			remove_single_quote(new_word, old_word, &i, &j);
		else if (old_word[i] == '\"')
			remove_double_quote(new_word, old_word, &i, &j);
		else
		{
			new_word[j] = old_word[i];
			j++;
			i++;
		}
	}
	free(token->word);
	token->word = new_word;
}

//ただし、そもそも処理されていないtokenもある
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

/// name_value

//void	expand_variable(t_token_info *token)
//{
//	char	*new_word;
//	char	*old_word;
//	int		i;
//	int		j;
//
//	old_word = token->word;
//	i = strlen(old_word);
//	new_word = calloc(i + 1, sizeof(char));
//	i = 0;
//	j = 0;
//	while (old_word[i])
//	{
//		if (old_word[i] == '\'')
//			remove_single_quote(new_word, old_word, &i, &j);
//		else if (old_word[i] == '\"')
//			remove_double_quote(new_word, old_word, &i, &j);
//		else
//		{
//			new_word[j] = old_word[i];
//			j++;
//			i++;
//		}
//	}
//	free(token->word);
//	token->word = new_word;
//}
//
//void	token_variable_expand(t_token_info *token)
//{
//	if (token == NULL)
//		return ;
//	while (token->next != NULL)
//	{
//		if ((token->kind == WORD) && (token->word != NULL))
//			expand_variable(token);
//		token = token->next;
//	}
//}
//
//void	variable_expander(t_node_info *node)
//{
//	if (node == NULL)
//		return ;
//	token_variable_expand(node->node_token);
//	token_variable_expand(node->filename);
//	variable_expander(node->redirects);
//	variable_expander(node->cmd);
//	variable_expander(node->re_node);
//}
//
void	expand(t_node_info *node)
{
	// variable_expander(node);
	quote_remover(node);
}
