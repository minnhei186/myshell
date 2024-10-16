/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare_element.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:42:41 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/16 14:43:19 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	redirect_out_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_in_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDIN_FILENO;
	redirect->filefd = open(redirect->filename->word, O_RDONLY, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_append_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

