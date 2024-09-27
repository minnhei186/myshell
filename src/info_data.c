/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:52:26 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/26 19:18:44 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//cmd_argvはnodeでなので必要ない
//ここで本来はmapを作成しておきたい
void	info_init(t_prompt_info *info, char **envp)
{
	info->str = NULL;
	info->envp = envp;
	info->status = 0;
	info->yourser_err=0;
}
