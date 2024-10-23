/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_token_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:37:36 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:37:56 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	tokenizer_error(t_prompt_info *info, char *err_msg)
{
	info->yourser_err = 1;
	perror_prestr();
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
}

void	parser_error(t_prompt_info *info, char *token_word)
{
	char	*err_msg;

	err_msg = "syntax error near unexpected token";
	info->yourser_err = 1;
	perror_prestr();
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, " '", 2);
	write(STDERR_FILENO, token_word, ft_strlen(token_word));
	write(STDERR_FILENO, "'", 1);
	write(STDERR_FILENO, "\n", 1);
}
