/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:09 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:22:02 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_fork_all_processes(t_ms *ms, t_pipeline *pl, pid_t *child_pids,
		int (*pipe_fds)[2])
{
	size_t	cmd_index;
	pid_t	child_pid;

	cmd_index = 0;
	while (cmd_index < pl->n)
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("minishell");
			while (cmd_index > 0)
			{
				cmd_index--;
				if (child_pids[cmd_index] > 0)
					kill(child_pids[cmd_index], SIGTERM);
			}
			return (-1);
		}
		if (child_pid == 0)
			ms_exec_pipeline_child(ms, pl, cmd_index, pipe_fds);
		child_pids[cmd_index] = child_pid;
		cmd_index++;
	}
	return (0);
}

static int	exec_pipeline_resources_setup(t_ms *ms, t_pipeline *pl,
	int (**pipe_fds)[2], pid_t **child_pids)
{
	if (pipe_array_create(pl->n, pipe_fds) < 0)
	{
		ms->last_status = 1;
		return (-1);
	}
	if (pid_array_allocate(pl->n, child_pids) < 0)
	{
		pipe_array_close_all(pl->n, *pipe_fds);
		free(*pipe_fds);
		ms->last_status = 1;
		return (-1);
	}
	return (0);
}

static void	exec_pipeline_cleanup(t_ms *ms, size_t cmd_count,
	int (*pipe_fds)[2], pid_t *child_pids)
{
	pipe_array_close_all(cmd_count, pipe_fds);
	free(pipe_fds);
	exec_wait_all_children(ms, cmd_count, child_pids);
	free(child_pids);
	ms->pipe_fds = NULL;
	ms->child_pids = NULL;
}

static int	exec_pipeline_handle_fork_error(t_ms *ms, t_pipeline *pl,
	int (*pipe_fds)[2], pid_t *child_pids)
{
	pipe_array_close_all(pl->n, pipe_fds);
	free(pipe_fds);
	free(child_pids);
	ms->pipe_fds = NULL;
	ms->child_pids = NULL;
	return (-1);
}

int	ms_exec_pipeline(t_ms *ms, t_pipeline *pl)
{
	int		(*pipe_fds)[2];
	pid_t	*child_pids;

	if (pl->n == 0)
		return (0);
	if (pl->n == 1)
	{
		if (ms_exec_cmd_with_pipeline(ms, &pl->cmds[0], pl) == 2)
			return (1);
		return (0);
	}
	if (exec_pipeline_resources_setup(ms, pl, &pipe_fds, &child_pids) < 0)
		return (-1);
	ms->pipe_fds = pipe_fds;
	ms->child_pids = child_pids;
	if (exec_fork_all_processes(ms, pl, child_pids, pipe_fds) < 0)
		return (exec_pipeline_handle_fork_error(ms, pl, pipe_fds, child_pids));
	exec_pipeline_cleanup(ms, pl->n, pipe_fds, child_pids);
	return (0);
}
