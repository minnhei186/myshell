/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:40:44 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/17 16:13:27 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//int	builtin_echo(t_prompt_info *info, char **argv)
//{
//	size_t	i;
//	int		new_line_flag;
//	int		first_flag;
//
//	(void)info;
//	i = 1;
//	new_line_flag = 1;
//	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
//	{
//		i++;
//		new_line_flag = 0;
//	}
//	first_flag = 1;
//	while (argv[i])
//	{
//		if (first_flag == 0)
//			write(STDOUT_FILENO, " ", 1);
//		first_flag = 0;
//		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
//		i++;
//	}
//	if (new_line_flag == 1)
//		write(STDOUT_FILENO, "\n", 1);
//	return (0);
//}


int is_option_n(const char *arg)
{
    int i;

    if (arg[0] != '-')
        return (0);
    i = 1;
    if (arg[i] != 'n')
        return (0);
    while (arg[i] == 'n')
        i++;
    if (arg[i] != '\0')
        return (0);
    return (1);
}

int	builtin_echo(t_prompt_info *info, char **argv)
{
	size_t	i;
	int		new_line_flag;
	int		first_flag;

	(void)info;
	i = 1;
	new_line_flag = 1;
	while (argv[i] && is_option_n(argv[i]))
	{
		i++;
		new_line_flag = 0;
	}
	first_flag = 1;
	while (argv[i])
	{
		if (first_flag == 0)
			write(STDOUT_FILENO, " ", 1);
		first_flag = 0;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (new_line_flag == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
