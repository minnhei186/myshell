/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:43:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:47 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

char	*expand_heredoc_line(t_prompt_info *info, char *word)
{
	char	*new_word;

	new_word = NULL;
	while (*word)
	{
		new_word = process_word_char(info, &word, new_word);
		if (info->yourser_err)
		{
			free(new_word);
			return (NULL);
		}
	}
	return (new_word);
}

char	*read_heredoc_line(t_prompt_info *info, int *pipe_fd)
{
	char	*line;

	line = readline("> ");
	if (g_sig_status == SIG_INT || line == NULL)
	{
		handle_heredoc_interrupt(info, line, pipe_fd);
		return (NULL);
	}
	return (line);
}

char	*process_line(t_prompt_info *info, t_node_info *redirect, char *line)
{
	char	*new_line;

	if (redirect->is_delim_unquoted)
	{
		new_line = expand_heredoc_line(info, line);
		free(line);
		if (info->yourser_err)
		{
			free(new_line);
			return (NULL);
		}
		return (new_line);
	}
	return (line);
}

void	process_heredoc_lines(t_prompt_info *info, t_node_info *redirect,
		int *pipe_fd)
{
	char	*line;

	while (1)
	{
		line = read_heredoc_line(info, pipe_fd);
		if (!line)
			return ;
		if (ft_strcmp(line, redirect->delimiter->word) == 0)
		{
			free(line);
			break ;
		}
		line = process_line(info, redirect, line);
		if (!line)
			return ;
		write_line_to_pipe(pipe_fd[1], line);
		free(line);
	}
}

void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		minishell_perror(info, "failed to create a pipe");
		return ;
	}
	g_sig_status = HEREDOC;
	process_heredoc_lines(info, redirect, pipe_fd);
	close_safely(pipe_fd[1]);
	redirect->filefd = pipe_fd[0];
	redirect->targetfd = STDIN_FILENO;
	g_sig_status = IN_CMD;
}
