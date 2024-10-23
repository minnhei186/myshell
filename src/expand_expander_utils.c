/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:34:25 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 16:42:19 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_alpha_or_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_or_under_or_digit(char c)
{
	return (is_alpha_or_under(c) || ft_isdigit(c));
}

bool	is_variable(char *word)
{
	if (word[0] == '$' && is_alpha_or_under(word[1]))
		return (true);
	return (false);
}

bool	is_special_parameter(char *word)
{
	if (word[0] == '$' && word[1] == '?')
		return (true);
	return (false);
}

char	*append_num(char *new_word, int num)
{
	if (num == 0)
	{
		new_word = append_char(new_word, '0');
		return (new_word);
	}
	if (num / 10 != 0)
		new_word = append_num(new_word, num / 10);
	new_word = append_char(new_word, '0' + (num % 10));
	return (new_word);
}
