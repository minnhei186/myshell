/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:03:16 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/07 16:03:26 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"



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
