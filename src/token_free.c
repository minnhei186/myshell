/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:27:39 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/27 14:27:53 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"


void	do_free_token(t_token_info *token)
{
	free(token->word);
	free(token);
}

//ここで重要なのはtokenは別の格納庫であり、そこの同じアドレスが入っている
//そうそう、構造体を解放するとはnextの保管庫をを解放するということである。その中身とはまた異なる。
void	free_token(t_token_info *token)
{
	t_token_info	*next_token;

	while (token->next != NULL)
	{
		next_token = token->next;
		do_free_token(token);
		token = next_token;
	}
	if (token != NULL)
		do_free_token(token);
	return ;
}
