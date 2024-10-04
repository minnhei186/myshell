/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <hosokawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:52:26 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/04 16:53:44 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	info_null_init(t_prompt_info *info)
{
	info->str = NULL;
	info->envp = NULL;
	info->shell_finish_flag = 0;
	info->last_status = 0;
	info->yourser_err = 0;
	info->map = NULL;
}

void	info_envp2item(t_prompt_info *info, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (item_put(info->map, envp[i], 1) == 1)
		{
			info->yourser_err = 1;
			return ;
		}
		i++;
	}
}

void	info_map_init(t_prompt_info *info, char **envp)
{
	info->map = make_map();
	if (info->map == NULL)
	{
		info->shell_finish_flag = 1;
		return ;
	}
	info_envp2item(info, envp);
	if (info->yourser_err == 1)
	{
		info->shell_finish_flag =1;
		return ;
	}
}

void	info_init(t_prompt_info *info, char **envp)
{
	info_null_init(info);
	info_map_init(info, envp);
}
