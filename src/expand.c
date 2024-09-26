/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/26 10:54:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//ひとつ一つのtokenを見ていく。
//サイズが大きくてもちゃんと終端文字があればいいか。
//つまりそう、別に大きくてもいいかもね。

// tokenはそのままに、tokenのwordだけを変更か、こうすれば新しくメモリ空間をその構造体分確保しなくてもいい、その構造体のアドレスを格納している場所が消失しないですむ。
//関数の移動において。

void	do_quote_removal(t_token_info *token)
{
	char	*new_word;
	char	*old_word;
	int		i;
	int		j;

	old_word = token->word;
	i = strlen(old_word);
	new_word = calloc(i + 1, sizeof(char)); // new_wordポインタ自体はマロックしなくていい
	//なぜなら、この格納庫ではなくて
	//アドレスはマロックされている構造体のポインタに格納するので。
	i = 0;
	j = 0;
	while (old_word[i])
	{
		if (old_word[i] == '\'')//必ずこれが来るなら次の'もある
		{
			i++;
			while (old_word[i] != '\'')
			{
				new_word[j] = old_word[i];
				j++;
				i++;
			}
			i++;
		}
		else if(old_word[i] == '\"')
		{
			i++;
			while (old_word[i] != '\"')
			{
				new_word[j] = old_word[i];
				j++;
				i++;
			}
			i++;
		}
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

void	quote_removal(t_token_info *token)
{
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
			do_quote_removal(token);
		token = token->next;
	}
}

void	expand(t_token_info *token)
{
	if (token != NULL)
		quote_removal(token);
}
