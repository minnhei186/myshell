/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/19 14:30:06 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q myshell");
//}

void	exe_command(char *path,char **prompt,char **envp)
{
	execve(path,prompt,envp);
}

char *make_path(char *command)
{
	char *path;
	path=ft_strjoin("/bin/",command);
	return path;
}

void	child_process(t_prompt_info *info)
{
	char **cmd_prompt;
	char *cmd_path;
	char **cmd_envp;
	cmd_path=path_get(info->cmd_argv[0]);
	cmd_prompt=info->cmd_argv;
	cmd_envp=info->envp;
	if(cmd_path==NULL)
	{
		error_set("not_exist_command",0,info);
		return ;
	}
	cmd_envp=info->envp;
	exe_command(cmd_path,cmd_prompt,cmd_envp);
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

void	extern_command(t_prompt_info *info)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_set("cannot_fork", 1, info);
	else if (pid == 0)
		child_process(info);
	else
		parent_process(info, pid);
}

// redirect_zone
void redirect_open_set(t_node_info *redirect)
{
	redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY, 0644);
	redirect->targetfd=STDOUT_FILENO;
}

void init_redirect(t_node_info *node)
{
	while(node->redirects!=NULL)
	{
		redirect_open_set(node->redirects);
		node=node->redirects;
	}
}

void redirect_do_set(t_node_info *redirect)
{
	redirect->stashedfd = fcntl(redirect->targetfd, F_DUPFD, 10);
	dup2(redirect->filefd,redirect->targetfd);
}


void do_redirect(t_node_info *node)
{
	while(node->redirects!=NULL)
	{
		redirect_do_set(node->redirects);
		node=node->redirects;
	}

}

void set_redirect(t_node_info *node)
{
	init_redirect(node);
	do_redirect(node);
}

void redirect_reset_set(t_node_info *redirect)
{
	dup2(redirect->stashedfd,redirect->targetfd);
}



void reset_redirect(t_node_info *node)
{
	while(node->redirects!=NULL)
	{
		redirect_reset_set(node->redirects);
		node=node->redirects;
	}
}

void	shell_operation(t_prompt_info *info)
{
	t_token_info *token;
	t_node_info *node;

	token=tokenizer(info,info->str);
	node=parser(token);	
	set_redirect(node);
	info->cmd_argv=token2argv(node->node_token);
	extern_command(info);
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
	return TRUE;
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
