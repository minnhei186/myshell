/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/22 13:48:10 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	expand(t_prompt_info *info, t_node_info *node)
{
	variable_expander(info, node);
	if (info->yourser_err)
		return ;
	quote_remover(info, node);
	if (info->yourser_err)
		return ;
}
