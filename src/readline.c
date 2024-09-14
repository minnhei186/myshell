/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/14 11:55:49 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q myshell");
//}

int	child_process_do(char *str)
{
	if (execve(str, &str, NULL) == -1)
		return (-1);
	return (0);
}

void extern_command(t_prompt_info *info)
{
	int	pid;
	int	status;

	status = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (status);
	else if (pid == 0)
	{
		if (child_process_do(str) == -1)
			return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	return (-1);
}

void	prompt_operation(t_prompt_info *info)
{
	extern_command(info);
}

bool	shell_loop(t_prompt_info *info)
{
	info.str = readline("myshell:");
	if (str == NULL)
		return (FALSE);
	if (*(info.str))
	{
		add_history(*(info.str));
		prompt_operation(&info);
	}
	free(info.str);
	info.str = NULL;
	return TRUE
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt_info	info;

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
