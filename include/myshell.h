/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:33:43 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/14 11:51:45 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H 
#define MYSHELL_H



#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0;
#define TRUE 1;

typedef struct s_prompt_info
{
	char	*str;
	char	**envp;
	int		status;

}			t_prompt_info;


//prompt_info_func
void	info_init(t_prompt_info *info, char **envp);



#endif
