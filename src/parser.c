/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:31 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 13:11:16 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

t_node_info	*make_node(void)
{
	t_node_info	*node;

	node = (t_node_info *)minishell_malloc(sizeof(t_node_info));
	node->kind = -1;
	node->re_node = NULL;
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->cmd = NULL;
	node->node_token = NULL;
	node->redirects = NULL;
	node->targetfd = -1;
	node->filename = NULL;
	node->delimiter = NULL;
	node->filefd = -1;
	node->stashedfd = -1;
	return (node);
}

t_node_info	*prompt_parser(t_prompt_info *info, t_token_info *token)
{
	t_node_info		*command_node;
	t_token_info	*now_token;

	command_node = make_node();
	command_node->kind = ND_SIMPLE_CMD;
	while (token->next != NULL)
	{
		now_token = append_node(info, command_node, token);
		if (info->yourser_err == 1)
			return (command_node);
		if ((ft_strncmp(token->word, "|", 1) == 0))
			return (command_node);
		token = now_token->next;
	}
	append_node(info, command_node, token);
	return (command_node);
}

t_token_info	*find_pipe(t_token_info *token)
{
	while (token->next != NULL)
	{
		if (ft_strncmp(token->word, "|", 1) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_node_info	*parser(t_prompt_info *info, t_token_info *token)
{
	t_node_info		*node;
	t_token_info	*now_token;

	node = make_node();
	node->kind = ND_PIPE;
	node->cmd = prompt_parser(info, token);
	now_token = find_pipe(token);
	if (now_token != NULL)
	{
		now_token = now_token->next;
		node->re_node = parser(info, now_token);
	}
	return (node);
}
