/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:17:27 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 13:45:23 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//そのtoken構造体自体の解放について
//それとメンバの中について
// tokenのセグフォとその風について
void	token_free(t_token_info *token)
{
	t_token_info	*next_token;

	while (token != NULL)
	{
		free(token->word);
		next_token = token->next;
		free(token);
		token = next_token;
	}
}

void	node_free(t_node_info *node)
{
	if (node == NULL)
		return ;
	token_free(node->node_token);
	token_free(node->filename);
	token_free(node->delimiter);
	node_free(node->redirects);
	node_free(node->cmd);
	node_free(node->re_node);
	free(node);
}

void	free_operation(t_operation_info operation)
{
	token_free(operation.token);
	node_free(operation.node);
}
