/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:52:26 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/09 10:36:54 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	info_null_init(t_prompt_info *info)
{
	info->str = NULL;
	info->shell_finish = 0;
	info->last_status = 0;
	info->yourser_err = 0;
	info->map = NULL;
}

void	info_envp2item(t_prompt_info *info, char **envp)
{
	int	i;

	i = 0;
	//途中までメモリが確保されている中で中断
	while (envp[i])
	{
		// item_putはinitだけではない
		item_put(info,info->map, envp[i], 0); // fatal_errではないが終了
		if (info->yourser_err == 1)
		{
			info->shell_finish =1;
			return ;
		}
		 i++;
	}
}

void	info_map_init(t_prompt_info *info, char **envp)
{
	info->map = minishell_make_map();
	info_envp2item(info, envp); //ここではまだフリーしない
								//こうすることで、同じように考えることができる。
}

void	info_init(t_prompt_info *info, char **envp)
{
	info_null_init(info);
	info_map_init(info, envp);
}
