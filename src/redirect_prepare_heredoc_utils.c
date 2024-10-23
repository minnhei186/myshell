/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare_heredoc_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:20:47 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:12 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	handle_heredoc_interrupt(t_prompt_info *info, char *line, int *pipe_fd)
{
	free(line);
	info->yourser_err = 1;
	info->last_status = 130;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	g_sig_status = IN_CMD;
}

void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

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
