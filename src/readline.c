/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 16:27:35 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	child_process(t_node_info *node)
{
	char	**cmd_prompt;
	char	*cmd_path;
	char	**cmd_envp;

	//	int		i;
	prepare_pipe_child(node);
	do_redirect(node->cmd);
	cmd_prompt = token2argv(node->cmd->node_token);
	cmd_path = path_get(cmd_prompt[0]);
	cmd_envp = environ;
	//	i = 0;
	//	while (cmd_prompt[i])
	//		printf("%s\n", cmd_prompt[i++]);
	//	printf("%s \n", cmd_path);
	if (cmd_path == NULL)
		yourser_error_exit("command_not_found");
	if (execve(cmd_path, cmd_prompt, cmd_envp) == -1)
	{
		reset_redirect(node); //エラー出力に対するリダイレクトの影響
		fatal_error_exit("cannot_do_execve");
	}
}

void	close_final_pipe(t_node_info *node)
{
	close(node->outpipe[0]);
}

int	command_comunication(t_node_info *node)
{
	int	pid;

	prepare_pipe(node);
	pid = fork();
	if (pid == -1)
		fatal_error_exit("faild to fork");
	else if (pid == 0)
		child_process(node);
	prepare_pipe_parent(node);
	if (node->re_node != NULL)
		return (command_comunication(node->re_node));
	close_final_pipe(node); //最後のnodeでは、活かすものがない。closeでいい
	return (pid);
}

int	wait_process(int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	return (status);
}

void	exec(t_prompt_info *info, t_node_info *node)
{
	int	last_pid;

	if (node->re_node == NULL && is_builtin(node))
		exec_bultin(info, node);
	else
	{
		last_pid = command_comunication(node);
		info->last_status = wait_process(last_pid);
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

	operation.token = NULL;
	operation.node = NULL;
	info->str = readline("myshell:");
	if (info->str == NULL)
	{
		if (sig == SIGINT)
		{
			info->yourser_err = 1;
			sig = 0;
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			info->shell_finish = 1;
		}
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
	//	clear_info(info);//ここで初めてinfoをクリアする//initエラーも含められる
	return (info.last_status);
}
