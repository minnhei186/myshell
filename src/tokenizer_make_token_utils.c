/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_make_token_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:56:22 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:52:00 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	init_operators(char **operators)
{
	operators[0] = "||";
	operators[1] = "&&";
	operators[2] = "&";
	operators[3] = ";;";
	operators[4] = ";";
	operators[5] = "(";
	operators[6] = ")";
	operators[7] = "|";
	operators[8] = "\n";
	operators[9] = "<<";
	operators[10] = ">>";
	operators[11] = "<";
	operators[12] = ">";
}

char	*malloc_op(char *prompt)
{
	size_t	i;
	char	*op_str;
	char	*operators[13];

	init_operators(operators);
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_same_top(prompt, operators[i]))
			break ;
		i++;
	}
	op_str = minishell_strdup(operators[i]);
	return (op_str);
}

t_token_info	*make_operand_token(char *prompt)
{
	t_token_info	*new_token;
	char			*op_str;

	op_str = malloc_op(prompt);
	new_token = (t_token_info *)minishell_calloc(1, sizeof(t_token_info));
	new_token->word = op_str;
	new_token->kind = OP;
	new_token->next = NULL;
	return (new_token);
}

int	recive_single_qout(t_prompt_info *info, char *prompt, int i)
{
	if (prompt[i] == '\'')
	{
		i++;
		while (prompt[i] != '\'')
		{
			if (prompt[i] == '\0')
			{
				tokenizer_error(info, "not_close_single_quote");
				return (-1);
			}
			i++;
		}
	}
	return (i);
}

int	recive_double_qout(t_prompt_info *info, char *prompt, int i)
{
	if (prompt[i] == '\"')
	{
		i++;
		while (prompt[i] != '\"')
		{
			if (prompt[i] == '\0')
			{
				tokenizer_error(info, "not_close_double_quote");
				return (-1);
			}
			i++;
		}
	}
	return (i);
}
