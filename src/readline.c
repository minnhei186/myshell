/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/13 14:01:01 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

__attribute__((destructor)) static void destructor()
{
	system("leaks -q myshell");
}




int	main(int argc, char **argv, char **environ)
{
	char	*str;

	(void)argc;
	(void)argv;
	(void)environ;

	rl_outstream = stderr;
	str = NULL;
	while (1)
	{
		str = readline("myshell:");
		if (str != NULL)
		{
			if (*str)
			{
				add_history(str);
				commnad_operation(str);
			}
			free(str);
			str = NULL;
		}
		else
			break ;
	}
	clear_history();
	return (EXIT_SUCCESS);
}
