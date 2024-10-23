/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:08:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 15:15:04 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_token_info	*ft_tokendup(t_token_info *token)
{
	t_token_info	*cp_token;

	cp_token = (t_token_info *)minishell_malloc(sizeof(t_token_info));
	cp_token->word = minishell_strdup(token->word);
	cp_token->kind = token->kind;
	cp_token->next = NULL;
	return (cp_token);
}

void	token_append_tail(t_node_info *node, t_token_info *cp_token)
{
	t_token_info	*search_token;

	search_token = node->node_token;
	while (search_token->next != NULL)
		search_token = search_token->next;
	search_token->next = cp_token;
}

int	type_redirect_op(t_token_info *token)
{
	if (ft_strncmp(token->word, ">>", 2) == 0)
		return (3);
	else if (ft_strncmp(token->word, "<<", 2) == 0)
		return (4);
	else if (ft_strncmp(token->word, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(token->word, "<", 1) == 0)
		return (2);
	return (0);
}

int	is_pipe_op(t_token_info *token)
{
	if (ft_strncmp(token->word, "|", 1) == 0)
		return (1);
	return (0);
}

void	redirect_append_tail(t_node_info *node, t_node_info *append_redirect)
{
	t_node_info	*search_redirect;

	search_redirect = node->redirects;
	while (search_redirect->redirects != NULL)
		search_redirect = search_redirect->redirects;
	search_redirect->redirects = append_redirect;
}
