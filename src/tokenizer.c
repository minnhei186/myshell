/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:37:11 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 12:15:07 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*space_skip(char *prompt)
{
	while (*prompt)
	{
		if (*prompt == ' ' || *prompt == '\t')
			prompt++;
		else
			return (prompt);
	}
	return (prompt);
}

t_token_info	*tokenizer(t_prompt_info *info, char *prompt)
{
	t_token_info	root_tk;
	t_token_info	*token;

	root_tk.word = NULL;
	root_tk.kind = 0;
	root_tk.next = NULL;
	token = &root_tk;
	while (*prompt)
	{
		prompt = space_skip(prompt);
		if (*prompt == '\0')
			break ;
		token = make_token(info, &prompt, token);
		if (info->yourser_err == 1)
			return (root_tk.next);
	}
	token->next = make_eof_token();
	return (root_tk.next);
}
