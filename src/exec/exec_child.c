/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:56 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:57 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command_in_child(t_ms *ms, t_cmd *cmd, t_pipeline *pl)
{
	int	arg_count;
	int	builtin_result;

	if (is_builtin(cmd->argv[0]))
	{
		arg_count = 0;
		while (cmd->argv[arg_count])
			arg_count++;
		builtin_result = run_builtin(arg_count, cmd->argv, ms);
		ms_pipeline_free(pl);
		env_context_free(ms->envp);
		if (ms->pipe_fds)
			free(ms->pipe_fds);
		if (ms->child_pids)
			free(ms->child_pids);
		_exit(builtin_result);
	}
	exec_external_command(ms, cmd, pl);
}

static void	exec_pipe_cleanup_unused(size_t cmd_index,
	size_t cmd_count, int (*pipe_fds)[2])
{
	size_t	pipe_index;

	pipe_index = 0;
	while (pipe_index < cmd_count - 1)
	{
		if (pipe_index != cmd_index - 1)
			close(pipe_fds[pipe_index][0]);
		if (pipe_index != cmd_index)
			close(pipe_fds[pipe_index][1]);
		pipe_index++;
	}
}

/* ms_exec_pipeline_child - better name: exec_child_process_run */
void	ms_exec_pipeline_child(t_ms *ms, t_pipeline *pl, size_t cmd_index,
								int (*pipe_fds)[2])
{
	size_t	cmd_count;

	cmd_count = pl->n;
	ms_signals_child();
	if (cmd_index > 0)
		dup2(pipe_fds[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < cmd_count - 1)
		dup2(pipe_fds[cmd_index][1], STDOUT_FILENO);
	exec_pipe_cleanup_unused(cmd_index, cmd_count, pipe_fds);
	if (cmd_index > 0)
		close(pipe_fds[cmd_index - 1][0]);
	if (cmd_index < cmd_count - 1)
		close(pipe_fds[cmd_index][1]);
	if (ms_apply_redirs(&pl->cmds[cmd_index]) < 0)
	{
		ms_pipeline_free(pl);
		env_context_free(ms->envp);
		if (ms->pipe_fds)
			free(ms->pipe_fds);
		if (ms->child_pids)
			free(ms->child_pids);
		_exit(1);
	}
	exec_command_in_child(ms, &pl->cmds[cmd_index], pl);
}
