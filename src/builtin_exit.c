/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:45:14 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:24:59 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

long	ft_atol(const char *str, int *error_flag)
{
	long	result;
	int		sign;
	int		i;
	int		digit;

	result = 0;
	sign = 1;
	i = 0;
	*error_flag = 0;
	/* 空白文字をスキップ */
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	/* 符号の判定 */
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	/* 数字でない文字列のチェック */
	if (str[i] == '\0' || (str[i] < '0' || str[i] > '9'))
	{
		*error_flag = 1;
		return (0);
	}
	/* 数値の解析とオーバーフローチェック */
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && (result > (LONG_MAX - digit) / 10))
		{
			*error_flag = 1;
			return (0);
		}
		if (sign == -1 && (-result < (LONG_MIN + digit) / 10))
		{
			*error_flag = 1;
			return (0);
		}
		result = result * 10 + digit;
		i++;
	}
	/* 末尾に余分な文字がないかチェック */
	if (str[i] != '\0')
	{
		*error_flag = 1;
		return (0);
	}
	return (sign * result);
}

int	builtin_exit(t_prompt_info *info, char **argv)
{
	long	res;
	int		error_flag;

	write(STDOUT_FILENO, "exit\n", 5);
	if (argv[1] == NULL)
		exit(info->last_status);
	res = ft_atol(argv[1], &error_flag);
	if (error_flag)
	{
		write(STDERR_FILENO, "bash: exit: ", 12);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit(255);
	}
	if (argv[2])
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
		info->last_status = 1;
		return (1);
	}
	exit((int)res);
}


