/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:09:32 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 16:41:48 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

#define ERROR_PRESTR "minishell: "

void	fatal_error_exit(char *err_msg) __attribute__((noreturn));

void	perror_prestr(void)
{
	write(STDERR_FILENO, ERROR_PRESTR, ft_strlen(ERROR_PRESTR));
}

void	fatal_error_exit(char *err_msg)
{
	perror_prestr();
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void yourser_error_exit(char *err_msg)
{
	perror_prestr();
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO,"\n", 1);
	exit(EXIT_FAILURE);
}

void minishell_yourser_perror(t_prompt_info *info,char *err_msg)
{
	info->yourser_err=1;
	perror_prestr();
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO,"\n", 1);
}

void minishell_perror(t_prompt_info *info,char *err_msg)
{
	info->yourser_err=1;
	perror_prestr();
	perror(err_msg);
}





void tokenizer_error(t_prompt_info *info,char *err_msg)
{
	info->yourser_err=1;
	perror_prestr();
	write(STDERR_FILENO,err_msg,ft_strlen(err_msg));
	write(STDERR_FILENO,"\n",ft_strlen("\n"));
}

void parser_error(t_prompt_info *info,char *token_word)
{
	char *err_msg="syntax error near unexpected token";
	info->yourser_err=1;
	perror_prestr();
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg)); 
	write(STDERR_FILENO, " '", 2); 
	write(STDERR_FILENO, token_word, ft_strlen(token_word)); 
	write(STDERR_FILENO, "'", 1); 
	write(STDERR_FILENO, "\n", 1); 
}





