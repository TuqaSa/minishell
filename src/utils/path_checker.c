/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:19:48 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:17 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_is_exec_file(const char *path)
{
	struct stat	st;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	return (S_ISREG(st.st_mode));
}

char	*ms_path_build_candidate(const char *dir, const char *cmd)
{
	return (ms_path_join3(dir, "/", cmd));
}

int	ms_path_test_candidate(const char *candidate)
{
	return (path_is_exec_file(candidate));
}
