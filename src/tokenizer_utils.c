/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:45:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:14:21 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// EOFトークンのサイズは数えることができない。これは後で考えよう。
int	token_size(t_token_info *token)
{
	int	token_size;

	token_size = 0;
	while (token->next != NULL)
	{
		token = token->next;
		token_size++;
	}
	return (token_size);
}

char	**token2argv(t_token_info *token)
{
	char	**tk_argv;
	char	*tk_str;
	int		i;

	tk_argv = malloc(sizeof(char *) * token_size(token) + 1);
	i = 0;
	while (token->next != NULL)
	{
		tk_str = minishell_strdup(token->word);
		tk_argv[i] = tk_str;
		i++;
		token = token->next;
	}
	tk_argv[i] = NULL;
	return (tk_argv);
}

bool	is_meta(char c)
{
	if (c && ft_strchr("|&;()<> \t\n", c))
		return (true);
	return (false);
}

bool	is_same_top(char *s, char *keyword)
{
	if (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0)
		return (true);
	return (false);
}

bool	is_operand(char *prompt)
{
	size_t	i;
	char	*operators[13];

	init_operators(operators);
	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (is_same_top(prompt, operators[i]))
			return (true);
		i++;
	}
	return (false);
}
