/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:47:50 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/15 20:06:33 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

// open
void	redirect_out_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_in_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDIN_FILENO;
	redirect->filefd = open(redirect->filename->word, O_RDONLY, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

void	redirect_append_init(t_prompt_info *info, t_node_info *redirect)
{
	redirect->targetfd = STDOUT_FILENO;
	redirect->filefd = open(redirect->filename->word,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redirect->filefd < 0)
		minishell_perror(info, redirect->filename->word);
}

// int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
//ここでsignalのグローバル変数を変更してあげてもいいかもね。挙動の変更
////リダイレクトのtarget変更して内と外にしている!!!

char	*expand_heredoc_line(t_prompt_info *info, char *word)
{
	char	*new_word;

	new_word = NULL;
	while (*word)
	{
		if (is_variable(word))
			new_word = expand_variable_word(info, &word, new_word);
		else if (is_special_parameter(word))
			new_word = expand_special_parameter(info, &word, new_word);
		else
		{
			new_word = append_char(new_word, *word);
			word++;
		}
		if (info->yourser_err)
			return (NULL);
	}
	return (new_word);
}

void	redirect_heredoc_init(t_prompt_info *info, t_node_info *redirect)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		minishell_perror(info, "failed to create a pipe");
		return ;
	}
	g_sig_status = HEREDOC;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			// ヒアドキュメントの入力が終了した場合
			if (g_sig_status == SIG_INT)
			{
				// シグナルによる中断
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				info->yourser_err = 130; // 終了ステータスを130に設定
				g_sig_status = IN_CMD;       // 状態をリセット
				return ;
			}
			break ;
		}
		if (ft_strncmp(line, redirect->delimiter->word,
				ft_strlen(redirect->delimiter->word)) == 0
			&& ft_strlen(line) == ft_strlen(redirect->delimiter->word))
		{
			free(line);
			break ;
		}
		if (redirect->is_delim_unquoted)
		{
			line = expand_heredoc_line(info, line);
			if (info->yourser_err)
			{
				printf("error\n");
				free(line);
				return ;
			}
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	redirect->targetfd = pipe_fd[0];
	g_sig_status= IN_CMD;
}

void	redirect_type_init(t_prompt_info *info, t_node_info *redirect)
{
	if (redirect->kind == ND_REDIR_OUT)
		redirect_out_init(info, redirect);
	else if (redirect->kind == ND_REDIR_IN)
		redirect_in_init(info, redirect);
	else if (redirect->kind == ND_REDIR_APPEND)
		redirect_append_init(info, redirect);
	else if (redirect->kind == ND_REDIR_HEREDOC)
		redirect_heredoc_init(info, redirect);
}

void	init_redirect(t_prompt_info *info, t_node_info *cmd_node)
{
	t_node_info	*redirect_node;

	redirect_node = cmd_node->redirects;
	while (redirect_node != NULL)
	{
		redirect_type_init(info, redirect_node);
		if (info->yourser_err == 1)
			return ;
		redirect_node = redirect_node->redirects;
	}
}

void	prepare_redirect(t_prompt_info *info, t_node_info *node)
{
	while (node != NULL)
	{
		init_redirect(info, node->cmd);
		if (info->yourser_err == 1)
			return ;
		node = node->re_node;
	}
}

void	redirect_do_set(t_node_info *redirect)
{
	redirect->stashedfd = fcntl(redirect->targetfd, F_DUPFD, 10); // stdoutの保持
	dup2(redirect->filefd, redirect->targetfd);
	close(redirect->filefd);
}

void	do_redirect(t_node_info *redirect_node)
{
	while (redirect_node != NULL)
	{
		redirect_do_set(redirect_node);
		redirect_node = redirect_node->redirects;
	}
}

// reset

void	redirect_reset_set(t_node_info *redirect)
{
	dup2(redirect->stashedfd, redirect->targetfd);
}

void	do_reset_redirect(t_node_info *cmd_node)
{
	t_node_info	*redirect_node;

	redirect_node = cmd_node->redirects;
	while (redirect_node != NULL)
	{
		redirect_reset_set(redirect_node);
		redirect_node = redirect_node->redirects;
	}
}

void	reset_redirect(t_node_info *node)
{
	while (1)
	{
		do_reset_redirect(node->cmd);
		if (node->re_node == NULL)
			break ;
		node = node->re_node;
	}
}
