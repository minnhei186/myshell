/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_refunc_atol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:59:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 16:00:04 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

static int	skip_whitespace(const char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
		|| str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r')
		(*i)++;
	return (0);
}

static int	check_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	is_invalid_input(const char *str, int *error_flag, int i)
{
	if (str[i] == '\0' || (str[i] < '0' || str[i] > '9'))
	{
		*error_flag = 1;
		return (1);
	}
	return (0);
}

static int	check_overflow(long result, int digit, int sign, int *error_flag)
{
	if (sign == 1 && (result > (LONG_MAX - digit) / 10))
	{
		*error_flag = 1;
		return (1);
	}
	if (sign == -1 && (-result < (LONG_MIN + digit) / 10))
	{
		*error_flag = 1;
		return (1);
	}
	return (0);
}

long	ft_atol(const char *str, int *error_flag)
{
	long	result;
	int		sign;
	int		i;
	int		digit;

	result = 0;
	i = 0;
	*error_flag = 0;
	skip_whitespace(str, &i);
	sign = check_sign(str, &i);
	if (is_invalid_input(str, error_flag, i))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (check_overflow(result, digit, sign, error_flag))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	if (str[i] != '\0')
		*error_flag = 1;
	return (sign * result);
}
