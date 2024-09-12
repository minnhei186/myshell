/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:01 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/12 13:59:23 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

int	main(int argc, char **argv)
{
	char	*str;

	while (str != NULL)
	{
		str = readline("myshell:");
		if(str&&*str)
			add_history(str);
		printf("%s\n", str);
		if (str != NULL)
			free(str);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
