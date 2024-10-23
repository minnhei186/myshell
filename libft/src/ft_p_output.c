/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhosokaw <dhosokaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:55:43 by dhosokaw          #+#    #+#             */
/*   Updated: 2024/10/23 19:26:34 by dhosokaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_p_count(intptr_t p)
{
	int	count;

	count = 0;
	while (p)
	{
		p /= 16;
		count++;
	}
	return (count);
}

static void	ft_p_put(intptr_t p)
{
	if (p >= 16)
	{
		ft_p_put(p / 16);
		ft_p_put(p % 16);
	}
	else
	{
		if (p > 9)
			ft_pf_putchar('a' + p - 10);
		else
			ft_pf_putchar('0' + p);
	}
}

int	ft_p_output(va_list *args)
{
	intptr_t	p;
	int			count;

	p = (intptr_t)(va_arg(*args, void *));
	count = write(STDOUT_FILENO, "0x", 2);
	if (p == 0)
		count += 1;
	else
		count += ft_p_count(p);
	ft_p_put(p);
	return (count);
}
