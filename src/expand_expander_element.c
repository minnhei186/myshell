/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_expander_element.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:31:54 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/14 14:34:55 by hosokawa         ###   ########.fr       */
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

char	*expand_variable_word(char **word, char *new_word)
{
	char	*variable_name;
	char	*variable_word;

	variable_name = NULL;
	variable_word = NULL;
	// skip_$
	*word = *word + 1;
	while (is_alpha_or_under_or_digit(**word))
	{
		variable_name = append_char(variable_name, **word);
		*word = *word + 1;
	}
	variable_word = getenv(variable_name);
	if (variable_word != NULL)
	{
		while (*variable_word != '\0')
		{
			new_word = append_char(new_word, *variable_word);
			variable_word++;
		}
	}
	return (new_word);
}

char	*expand_variable_single_quote(t_prompt_info *info, char **word,
		char *new_word)
{
	new_word = append_char(new_word, **word);
	*word = *word + 1;
	while (**word != SINGLE_QUOTE)
	{
		if (**word == '\0')
		{
			minishell_yourser_perror(info, "not_close_single_quote");
			free(new_word);
			return (NULL);
		}
		new_word = append_char(new_word, **word);
		*word = *word + 1;
	}
	new_word = append_char(new_word, **word);
	*word = *word + 1;
	return (new_word);
}

char	*expand_variable_double_quote(t_prompt_info *info, char **word,
		char *new_word)
{
	new_word = append_char(new_word, **word);
	*word = *word + 1;
	while (**word != DOUBLE_QUOTE)
	{
		if (**word == '\0')
		{
			minishell_yourser_perror(info, "not_close_double_quote");
			free(new_word);
			return (NULL);
		}
		else if (is_variable(*word))
			new_word = expand_variable_word(word, new_word);
		else if (is_special_parameter(*word))
			new_word = expand_special_parameter(info, word, new_word);
		else
		{
			new_word = append_char(new_word, **word);
			*word = *word + 1;
		}
	}
	new_word = append_char(new_word, **word);
	*word = *word + 1;
	return (new_word);
}
