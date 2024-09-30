/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/30 14:00:05 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//ひとつ一つのtokenを見ていく。
//サイズが大きくてもちゃんと終端文字があればいいか。
//つまりそう、別に大きくてもいいかもね。

// tokenはそのままに、tokenのwordだけを変更か、こうすれば新しくメモリ空間をその構造体分確保しなくてもいい、その構造体のアドレスを格納している場所が消失しないですむ。
//関数の移動において。

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

//全てのtokenはeofが存在する
//ただし、そもそも処理されていないtokenもある
void	token_quote_removal(t_token_info *token)
{
	if(token==NULL)
		return;
	while (token->next != NULL)
	{
		if ((token->kind == WORD) && (token->word != NULL))
			remove_quote(token);
		token = token->next;
	}
}

void quote_remover(t_node_info *node)
{
	if(node==NULL)
		return;

	token_quote_removal(node->node_token);
	token_quote_removal(node->filename);
	token_quote_removal(node->delimiter);
	quote_remover(node->redirects);
	quote_remover(node->cmd);
	quote_remover(node->re_node);

}
	

///name_value


void	expand(t_node_info *node)
{
	quote_remover(node);
}




