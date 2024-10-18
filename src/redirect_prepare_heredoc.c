/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:43:37 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/18 17:50:21 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

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
		if (g_sig_status == SIG_INT)//cntl_c
		{
			printf("SIG_INT_COMMIN\n");
			info->yourser_err = 1;   // 終了ステータスを130に設定
			info->last_status = 130; // heredocの中断の終了ステータス
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			g_sig_status = IN_CMD; // 状態をリセット
			return ;
		}
		if (line == NULL)//cntl_d
		{
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
	g_sig_status = IN_CMD;
}



//	info->yourser_err = 1;   // 終了ステータスを130に設定
//			info->last_status = 130; // heredocの中断の終了ステータス
//			close(pipe_fd[0]);
//			close(pipe_fd[1]);
//			g_sig_status = IN_CMD; // 状態をリセット
//			open_fd = open("/dev/tty", O_RDONLY);
//			if (open_fd == -1)
//			{
//				minishell_perror(info, "failed to open fd");
//				return ;
//			}
//			dup2(open_fd, STDIN_FILENO);
//			close(open_fd);
//			return ;
//
