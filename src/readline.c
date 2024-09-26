/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/25 12:23:29 by hosokawa         ###   ########.fr       */
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

	prepare_pipe_child(node);
	do_redirect(node->cmd);
	cmd_prompt = token2argv(node->cmd->node_token);
	cmd_path = path_get(cmd_prompt[0]);
	cmd_envp = environ;
	if (cmd_path == NULL)
	{
		printf("not_exist_commnad\n");
		// error_set("not_exist_command", 0, info);
		return ;
	}
	execve(cmd_path, cmd_prompt, cmd_envp);
	// error_set("cannot_exe_command", 0, info);
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
	{
		//	error_set("cannot_fork", 1, info);
		return (-1);
	}
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
	prepare_redirect(node);
	status = exec(node);
	reset_redirect(node);
	return (status);
}

void	shell_loop(t_prompt_info *info)
{
	// eofではreadlineでNULLが返るのでその時にだけ！！ループが
	info->str = readline("myshell:");
	if (info->str == NULL)
		info->status = 1;
	else
	{
		if (*(info->str)) //空文字ではないなら
		{
			add_history(info->str);
			info->status = shell_operation(info);
		}
		free(info->str); // readlineよりある文字列空間が存在するので
		info->str = NULL;
	}
}

//ステータスについて
//ああ、infoの実態は静的なんだ。うわお.ここで終われる。関数の中と終わりについて
// freeしなくていい、構造体自体をfreeしなくていい。ポインタが残ることの大切さ
int	main(int argc, char **argv, char **envp)
{
	t_prompt_info	info;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	info_init(&info, envp); //ここでmapの作成をしてもいいかもしれない。
	while (1)
	{
		shell_loop(&info);
		if (info.status == 1)
			break ;
	}
	clear_history();
	return (info.status);
}
