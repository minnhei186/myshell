/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/16 16:51:26 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

__attribute__((destructor)) static void destructor()
{
	system("leaks -q myshell");
}
void	err_exit(const char *msg, int status)
{
	perror_prestr();
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(status);
}

void	validate_access(const char *path, const char *filename)
{
	struct stat	st;

	if (path == NULL)
		err_exit("command not found", 127);
	if (strcmp(filename, "") == 0)
		err_exit("command not found", 127);
	if (strcmp(filename, "..") == 0)
		err_exit("command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit("command not found", 127);
	// if (stat(path, &st) < 0)
	//	fatal_error("fstat");
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
		exit(info->last_status); //パイプでbuiltinが実行されるならな
	}
	else
	{
		do_redirect(node->cmd);
		cmd_prompt = token2argv(node->cmd->node_token);
		cmd_path = path_get(info, cmd_prompt[0]);
		cmd_envp = item2argv(info->map->item);
		validate_access(cmd_path, cmd_prompt[0]);
		if (execve(cmd_path, cmd_prompt, cmd_envp) == -1)
		{
			// free(cmd_prompt);
			do_reset_redirect(node->cmd); //エラー出力に対するリダイレクトの影響
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
		child_process(info, node);
	prepare_pipe_parent(node);
	if (node->re_node != NULL)
		return (command_comunication(info, node->re_node));
	close_final_pipe(node); //最後のnode、生かすpipeがないため。
	return (pid);
}

int	wait_all_processes(int last_pid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = 0;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else
				last_status = status; // その他の場合
		}
	}
	return (last_status);
}

void	exec(t_prompt_info *info, t_node_info *node)
{
	int	last_pid;

	if (node->re_node == NULL && is_builtin(node))
		exec_builtin(info, node);
	else
	{
		last_pid = command_comunication(info, node);
		if (info->yourser_err)
			return ;
		info->last_status = wait_all_processes(last_pid);
	}
}

void	shell_operation(t_prompt_info *info, t_operation_info *operation)
{
	operation->token = tokenizer(info, info->str);
	if (info->yourser_err)
		return ;
	operation->node = parser(info, operation->token);
	if (info->yourser_err)
		return ;
	expand(info, operation->node);
	if (info->yourser_err)
		return ;
	prepare_redirect(info, operation->node);
	if (info->yourser_err)
		return ;
	exec(info, operation->node);
	if (info->yourser_err)
		return ;
}

void	shell_loop(t_prompt_info *info)
{
	t_operation_info	operation;

	// g_sig_status=IN_CMD;
	operation.token = NULL;
	operation.node = NULL;
	info->str = readline("myshell:");
	if (info->str == NULL)
	{
		info->shell_finish = 1;
		write(STDOUT_FILENO, "exit\n", 5);
	}
	else
	{
		if (*(info->str))
		{
			add_history(info->str);
			shell_operation(info, &operation);
			free_operation(operation);
		}
		free(info->str);
		info->str = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt_info	info;

	(void)argc;
	(void)argv;
	init_signal();
	info_init(&info, envp);
	if (info.shell_finish != 1)
	{
		while (info.shell_finish != 1)
		{
			shell_loop(&info);
			info.yourser_err = 0;
		}
		clear_history();
	}
	clear_info(&info); // info_errも含む
	return (info.last_status);
}
