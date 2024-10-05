/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/05 12:11:23 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

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
	reset_redirect(node);
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






//bultin!!!
//////////////////////////
//////////////////////////
//////////////////////////
//////////////////////////

bool	is_numeric(char *s)
{
	if (!isdigit(*s))
		return (false);
	while (*s)
	{
		if (!isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	builtin_exit(t_prompt_info *info,char **argv)
{
	long	res;
	char	*arg;
	char	*endptr;

	if (argv[1] == NULL)
		exit(info->last_status);
	if (argv[2])
	{
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		res = strtol(arg, &endptr, 10);
		if (errno == 0 && *endptr == '\0')
			exit((int)res);
	}
	exit(255);
}

bool	is_builtin(t_node_info *node)
{
	const char		*cmd_name;
	//char			*builtin_commands[] = {"exit", "export", "unset", "env",
	//				"cd", "echo", "pwd"};
	char			*builtin_commands[] = {"exit"};

	unsigned int	i;

	if (node == NULL || node->cmd == NULL | node->cmd->node_token== NULL
		|| node->cmd->node_token->word == NULL)
		return (false);
	cmd_name = node->cmd->node_token->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	exec_bultin(t_prompt_info *info, t_node_info *node)
{
	char	**cmd_argv;
	int		status;

	status = 0;
	do_redirect(node);
	cmd_argv = token2argv(node->cmd->node_token);
	if (ft_strncmp(cmd_argv[0], "exit", 4) == 0)
	{
		status = builtin_exit(info, cmd_argv);
		info->last_status = status;
	}
	free(cmd_argv);
	reset_redirect(node);
	return ;
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
	operation->node = parser(operation->token);
	if (info->yourser_err)
		return ;
	expand(operation->node);
	if (info->yourser_err)
		return ;
	prepare_redirect(operation->node);
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
		info->shell_finish_flag = 1;
	else
	{
		if (*(info->str))
		{
			add_history(info->str);
			shell_operation(info, &operation);
			//	free_operation(operation);
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
	rl_outstream = stderr;
	info_init(&info, envp);
	if (info.yourser_err != 1)
	{
		while (info.yourser_err != 1)
		{
			shell_loop(&info);
			info.yourser_err = 0;
		}
		clear_history();
	}
	return (info.last_status);
}
