/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mlt_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:07:12 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 13:23:15 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	err_exit(const char *msg, int status)
{
	perror_prestr();
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(status);
}

void	validate_access(const char *path, const char *prompt_head)
{
	struct stat	st;

	if (path == NULL)
		err_exit("command not found", 127);
	if (ft_strcmp(prompt_head, "") == 0)
		err_exit("command not found", 127);
	if (ft_strcmp(prompt_head, "..") == 0)
		err_exit("command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit("command not found", 127);
	if (stat(path, &st) < 0)
		fatal_error_exit("fstat");
	if (S_ISDIR(st.st_mode))
		err_exit("is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit("Permission denied", 126);
}

void	child_process(t_prompt_info *info, t_node_info *node)
{
	char	**cmd_prompt;
	char	*cmd_path;
	char	**cmd_envp;

	prepare_pipe_child(node);
	if (is_builtin(node))
	{
		exec_builtin(info, node);
		exit(info->last_status);
	}
	else
	{
		destroy_signal();
		do_redirect(node->cmd->redirects);
		cmd_prompt = token2argv(node->cmd->node_token);
		cmd_path = path_get(info, cmd_prompt[0]);
		cmd_envp = item2argv(info->map->item);
		validate_access(cmd_path, cmd_prompt[0]);
		if (execve(cmd_path, cmd_prompt, cmd_envp) == -1)
		{
			do_reset_redirect(node->cmd->redirects);
			fatal_error_exit("cannot_do_execve");
		}
	}
}

void	close_final_pipe(t_node_info *node)
{
	close(node->outpipe[0]);
}

int	command_comunication(t_prompt_info *info, t_node_info *node)
{
	int	pid;

	prepare_pipe(info, node);
	if (info->yourser_err)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		minishell_perror(info, "faild to fork");
		return (-1);
	}
	else if (pid == 0)
	{
		child_process(info, node);
	}
	prepare_pipe_parent(node);
	if (node->re_node != NULL)
		return (command_comunication(info, node->re_node));
	close_final_pipe(node);
	return (pid);
}
