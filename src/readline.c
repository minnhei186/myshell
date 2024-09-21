/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/20 19:44:42 by hosokawa         ###   ########.fr       */
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

	cmd_prompt=token2argv(node->node_token);
	cmd_path = path_get(cmd_prompt[0]);
	cmd_envp = info->envp;//環境変数をどうするかだな。
	if (cmd_path == NULL)
	{
		error_set("not_exist_command", 0, info);
		return ;
	}
	cmd_envp = info->envp;
	execve(cmd_path, cmd_prompt, cmd_envp);
	error_set("cannot_exe_command", 0, info);
}

void	parent_process(t_prompt_info *info, int pid)
{
	int	recive_status;

	if (waitpid(pid, &recive_status, 0) == -1)
	{
		error_set("waitpid_error", 0, info);
		return ;
	}
	info->status = recive_status;
}

//再起によって待機的な世界がそこにはある。
//こりゃすごいは、再起によってというかそういう世界gあある。これらはどのよに？空間がある？
//ここでひとつとなった。概念としてそこにある。そん概念をああだこうだと覆うな、その概念はそれである。というのもひとつだが、こういうのでも覆いすぎるなよ。そうでなはないのさ。みているというのは？
int	command_comunication(t_node_info *node)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		error_set("cannot_fork", 1, info);
		return (-1);
	}
	else if (pid == 0)
		child_process(node);
	if (node->next != NULL)
		return (command_comunication(node->next));
	return (pid);
}


int wait_process(int last_pid)
{

	int status;
	waitpid(last_pid,&status,0);
	return status;
}
	

int	exec(t_node_info *node)
{
	int	status;
	int	last_pid;

	last_pid = commnad_comunication(node);
	status = wait_process(last_pid);

	return status;
}

void	shell_operation(t_prompt_info *info)
{
	t_token_info	*token;
	t_node_info		*node;
	int status;

	token = tokenizer(info, info->str);
	node = parser(token);
	set_redirect(node);
	info->cmd_argv = token2argv(node->node_token);
	status=exec(node);
	reset_redirect(node);
}

int	shell_loop(t_prompt_info *info)
{
	info->str = readline("myshell:");
	if (info->str == NULL)
		return (FALSE);
	if (*(info->str))
	{
		add_history(info->str);
		shell_operation(info);
	}
	free(info->str);
	info->str = NULL;
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt_info	info;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	info_init(&info, envp);
	while (1)
	{
		if (shell_loop(&info) != 1)
			break ;
	}
	clear_history();
	return (info.status);
}
