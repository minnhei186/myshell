/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:43:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 15:15:45 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// char	*expand_heredoc_line(t_prompt_info *info, char *word)
//{
//	char	*new_word;
//
//	new_word = NULL;
//	while (*word)
//	{
//		if (is_variable(word))
//			new_word = expand_variable_word(info, &word, new_word);
//		else if (is_special_parameter(word))
//			new_word = expand_special_parameter(info, &word, new_word);
//		else
//		{
//			new_word = append_char(new_word, *word);
//			word++;
//		}
//		if (info->yourser_err)
//			return (NULL);
//	}
//	return (new_word);
//}
//
// void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect)
//{
//	char	*line;
//	char *tmp_line;
//	int		pipe_fd[2];
//
//	if (pipe(pipe_fd) < 0)
//	{
//		minishell_perror(info, "failed to create a pipe");
//		return ;
//	}
//	g_sig_status = HEREDOC;
//	while (1)
//	{
//		line = readline("> ");
//		if (g_sig_status == SIG_INT)
//		{
//			free(line);
//			info->yourser_err = 1;
//			info->last_status = 130;
//			close(pipe_fd[0]);
//			close(pipe_fd[1]);
//			g_sig_status = IN_CMD;
//			return ;
//		}
//		if (line == NULL)
//		{
//			info->yourser_err = 1;
//			info->last_status = 130;
//			close(pipe_fd[0]);
//			close(pipe_fd[1]);
//			g_sig_status = IN_CMD;
//			return ;
//		}
//		if (ft_strcmp(line, redirect->delimiter->word)==0)
//		{
//			free(line);
//			break ;
//		}
//		if (redirect->is_delim_unquoted)
//		{
//			tmp_line=line;
//			line = expand_heredoc_line(info, line);
//			free(tmp_line);
//			if (info->yourser_err)
//			{
//				free(line);
//				return ;
//			}
//		}
//		write(pipe_fd[1], line, ft_strlen(line));
//		write(pipe_fd[1], "\n", 1);
//		free(line);
//	}
//	close(pipe_fd[1]);
//	redirect->targetfd = pipe_fd[0];
//	g_sig_status = IN_CMD;
//}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//動くコード 1

// char	*process_word_char(t_prompt_info *info, char **word_ptr, char *new_word)
//{
//	char	*word;
//
//	word = *word_ptr;
//	if (is_variable(word))
//		new_word = expand_variable_word(info, word_ptr, new_word);
//	else if (is_special_parameter(word))
//		new_word = expand_special_parameter(info, word_ptr, new_word);
//	else
//	{
//		new_word = append_char(new_word, *word);
//		(*word_ptr)++;
//	}
//	return (new_word);
//}
//
// char	*expand_heredoc_line(t_prompt_info *info, char *word)
//{
//	char	*new_word;
//
//	new_word = NULL;
//	while (*word)
//	{
//		new_word = process_word_char(info, &word, new_word);
//		if (info->yourser_err)
//		{
//			free(new_word);
//			return (NULL);
//		}
//	}
//	return (new_word);
//}
//
// void	handle_heredoc_interrupt(t_prompt_info *info, char *line, int *pipe_fd)
//{
//	free(line);
//	info->yourser_err = 1;
//	info->last_status = 130;
//	close(pipe_fd[0]);
//	close(pipe_fd[1]);
//	g_sig_status = IN_CMD;
//}
//
// void	process_heredoc_lines(t_prompt_info *info, t_node_info *redirect,
//		int *pipe_fd)
//{
//	char	*line;
//	char	*tmp_line;
//
//	while (1)
//	{
//		line = readline("> ");
//		if (g_sig_status == SIG_INT || line == NULL)
//		{
//			handle_heredoc_interrupt(info, line, pipe_fd);
//			return ;
//		}
//		if (ft_strcmp(line, redirect->delimiter->word) == 0)
//		{
//			free(line);
//			break ;
//		}
//		if (redirect->is_delim_unquoted)
//		{
//			tmp_line = line;
//			line = expand_heredoc_line(info, line);
//			free(tmp_line);
//			if (info->yourser_err)
//			{
//				free(line);
//				return ;
//			}
//		}
//		write(pipe_fd[1], line, ft_strlen(line));
//		write(pipe_fd[1], "\n", 1);
//		free(line);
//	}
//}
//
// void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect)
//{
//	int	pipe_fd[2];
//
//	if (pipe(pipe_fd) < 0)
//	{
//		minishell_perror(info, "failed to create a pipe");
//		return ;
//	}
//	g_sig_status = HEREDOC;
//	process_heredoc_lines(info, redirect, pipe_fd);
//	close(pipe_fd[1]);
//	redirect->targetfd = pipe_fd[0];
//	g_sig_status = IN_CMD;
//}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

char	*process_word_char(t_prompt_info *info, char **word_ptr, char *new_word)
{
	char	*word;

	word = *word_ptr;
	if (is_variable(word))
		new_word = expand_variable_word(info, word_ptr, new_word);
	else if (is_special_parameter(word))
		new_word = expand_special_parameter(info, word_ptr, new_word);
	else
	{
		new_word = append_char(new_word, *word);
		(*word_ptr)++;
	}
	return (new_word);
}

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

void	handle_heredoc_interrupt(t_prompt_info *info, char *line, int *pipe_fd)
{
	free(line);
	info->yourser_err = 1;
	info->last_status = 130;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	g_sig_status = IN_CMD;
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

void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
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
	close(pipe_fd[1]);
	redirect->targetfd = pipe_fd[0];
	g_sig_status = IN_CMD;
}
