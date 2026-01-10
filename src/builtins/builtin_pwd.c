/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:13:37 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:13:38 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_ms *ms)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		perror("minishell");
		ms->last_status = 1;
		return (1);
	}
	builtin_putstr(current_dir);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(current_dir);
	ms->last_status = 0;
	return (0);
}
