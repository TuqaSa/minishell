/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_array_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:41 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:42 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_array_create(size_t cmd_count, int (**out_pipe_fds)[2])
{
	size_t	pipe_index;

	*out_pipe_fds = ft_calloc(cmd_count - 1, sizeof (int) * 2);
	if (!*out_pipe_fds)
	{
		perror("minishell");
		return (-1);
	}
	pipe_index = 0;
	while (pipe_index < cmd_count - 1)
	{
		if (pipe((*out_pipe_fds)[pipe_index]) < 0)
		{
			perror("minishell");
			free(*out_pipe_fds);
			return (-1);
		}
		pipe_index++;
	}
	return (0);
}

void	pipe_array_close_all(size_t cmd_count, int (*pipe_fds)[2])
{
	size_t	pipe_index;

	pipe_index = 0;
	while (pipe_index < cmd_count - 1)
	{
		close(pipe_fds[pipe_index][0]);
		close(pipe_fds[pipe_index][1]);
		pipe_index++;
	}
}

int	pid_array_allocate(size_t cmd_count, pid_t **out_pids)
{
	*out_pids = (pid_t *)ft_calloc(cmd_count, sizeof (pid_t));
	if (!*out_pids)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}
