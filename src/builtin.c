/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:16 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:09:16 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

bool	is_builtin(t_node_info *node)
{
	const char		*cmd_name;
	char			*builtin_commands[BUILTIN_SIZE];
	unsigned int	i;

	s_b_c(builtin_commands);
	if (node == NULL || node->cmd == NULL | node->cmd->node_token == NULL
		|| node->cmd->node_token->word == NULL)
		return (false);
	cmd_name = node->cmd->node_token->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (ft_strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_first_builtin(t_prompt_info *info, char **cmd_argv)
{
	int	status;

	if (ft_strcmp(cmd_argv[0], "env") == 0)
	{
		status = builtin_env(info);
		info->last_status = status;
		return (1);
	}
	if (ft_strcmp(cmd_argv[0], "export") == 0)
	{
		status = builtin_export(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	if (ft_strcmp(cmd_argv[0], "unset") == 0)
	{
		status = builtin_unset(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	return (0);
}

int	exec_second_builtin(t_prompt_info *info, char **cmd_argv)
{
	int	status;

	if (ft_strcmp(cmd_argv[0], "echo") == 0)
	{
		status = builtin_echo(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	if (ft_strcmp(cmd_argv[0], "pwd") == 0)
	{
		status = builtin_pwd(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	if (ft_strcmp(cmd_argv[0], "cd") == 0)
	{
		status = builtin_cd(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	return (0);
}

int	exec_third_builtin(t_prompt_info *info, char **cmd_argv)
{
	int	status;

	if (ft_strcmp(cmd_argv[0], "exit") == 0)
	{
		status = builtin_exit(info, cmd_argv);
		info->last_status = status;
		return (1);
	}
	return (0);
}

void	exec_builtin(t_prompt_info *info, t_node_info *node)
{
	char	**cmd_argv;
	int		builtin_flag;

	builtin_flag = 0;
	do_redirect(info, node->cmd->redirects);
	if (info->yourser_err)
	{
		do_reset_redirect(node->cmd->redirects);
		info->last_status = EXIT_FAILURE;
		return ;
	}
	cmd_argv = token2argv(node->cmd->node_token);
	if (builtin_flag == 0)
		builtin_flag = exec_first_builtin(info, cmd_argv);
	if (builtin_flag == 0)
		builtin_flag = exec_second_builtin(info, cmd_argv);
	if (builtin_flag == 0)
		builtin_flag = exec_third_builtin(info, cmd_argv);
	ppt_free(cmd_argv);
	do_reset_redirect(node->cmd->redirects);
	return ;
}
