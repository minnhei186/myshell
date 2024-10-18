/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/18 18:51:55 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

__attribute__((destructor)) static void destructor()
{
	system("leaks  myshell");
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
//	int i;

//	i=0;
	(void)argc;
	(void)argv;
	init_signal();
	info_init(&info, envp);
//	while(envp[i])
//		printf("%s\n",envp[i++]);
	if (info.shell_finish != 1)
	{
		while (info.shell_finish != 1)
		{
			shell_loop(&info);
			info.yourser_err = 0;
		}
		clear_history();
	}
	clear_info(&info);
	return (info.last_status);
}
