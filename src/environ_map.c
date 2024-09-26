/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:56 by hosokawa          #+#    #+#             */
/*   Updated: 2024/09/25 11:22:19 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

//後に実際のchar **envpもここで扱うからかな。
//
//typedef struct s_item
//{
//	char	*name;
//	char	*value;
//}			t_item;
//
//typedef struct s_map
//{
//	t_item	*item_head;
//	char	**environ;
//}
//
//t_map *
//map_init(char **envp)
//{
//	t_map	*map;
//
//	map = malloc(sizeof(map));
//	map->environ = ft_pptdup(envp);
//	map->item_head = make_item(envp);
//}
