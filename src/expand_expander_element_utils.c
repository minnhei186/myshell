/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander_element_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:04:33 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 15:05:16 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	variable_error_check(char *word)
{
	if (*word == '$')
	{
		if (is_variable(word) == false && is_special_parameter(word) == false)
			return (true);
	}
	return (false);
}

char	*expand_special_parameter(t_prompt_info *info, char **word,
		char *new_word)
{
	*word = *word + 2;
	new_word = append_num(new_word, info->last_status);
	return (new_word);
}
