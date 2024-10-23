/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mlt_process_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:02:10 by hosokawa          #+#    #+#             */
/*   Updated: 2024/10/23 17:03:09 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	err_exit(const char *msg, int status)
{
	perror_prestr();
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(status);
}

void	validate_access(const char *path, const char *prompt_head)
{
	struct stat	st;

	if (path == NULL)
		err_exit("command not found", 127);
	if (ft_strcmp(prompt_head, "") == 0)
		err_exit("command not found", 127);
	if (ft_strcmp(prompt_head, "..") == 0)
		err_exit("command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit("command not found", 127);
	if (stat(path, &st) < 0)
		fatal_error_exit("fstat");
	if (S_ISDIR(st.st_mode))
		err_exit("is a directory", 126);
	if (access(path, X_OK) < 0)
		err_exit("Permission denied", 126);
}
