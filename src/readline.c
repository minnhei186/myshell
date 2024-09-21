/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/21 12:14:08 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q myshell");
//}

void	child_process(t_node_info *node)
{
	char	**cmd_prompt;
	char	*cmd_path;
	char	**cmd_envp;

	cmd_prompt = token2argv(node->node_token);
	cmd_path = path_get(cmd_prompt[0]);
	cmd_envp = environ; 
	if (cmd_path == NULL)
	{
		printf("not_exist_commnad\n");
		//error_set("not_exist_command", 0, info);
		return ;
	}
	execve(cmd_path, cmd_prompt, cmd_envp);
	//error_set("cannot_exe_command", 0, info);
}

//void	parent_process(t_prompt_info *info, int pid)
//{
//	int	recive_status;
//
//	if (waitpid(pid, &recive_status, 0) == -1)
//	{
//		error_set("waitpid_error", 0, info);
//		return ;
//	}
//	info->status = recive_status;
//}

int	command_comunication(t_node_info *node)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
	//	error_set("cannot_fork", 1, info);
		return (-1);
	}
	else if (pid == 0)
		child_process(node);
	if (node->re_node!= NULL)
		return (command_comunication(node->re_node));
	return (pid);
}

int	wait_process(int last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	return (status);
}

int	exec(t_node_info *node)
{
	int	status;
	int	last_pid;

	last_pid = command_comunication(node);
	status = wait_process(last_pid);
	return (status);
}

int	shell_operation(t_prompt_info *info)
{
	t_token_info	*token;
	t_node_info		*node;
	int				status;

	token = tokenizer(info, info->str);
	node = parser(token);
	set_redirect(node);
	status = exec(node);
	reset_redirect(node);
	return (status);
}

int	shell_loop(t_prompt_info *info)
{
	int	status;

	status = 1;
	info->str = readline("myshell:");
	if (info->str == NULL)
		return (FALSE);
	if (*(info->str))
	{
		add_history(info->str);
		status = shell_operation(info);
	}
	free(info->str);
	info->str = NULL;
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt_info	info;
	int status;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	info_init(&info, envp);
	while (1)
	{
		status = shell_loop(&info);
		if (status != 1)
			break ;
	}
	clear_history();
	return (status);
}
