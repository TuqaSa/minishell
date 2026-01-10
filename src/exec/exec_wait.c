/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:30 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:22:34 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_wait_handle_signal_output(int wait_status, int *signal_printed)
{
	if (!*signal_printed && WIFSIGNALED(wait_status))
	{
		if (WTERMSIG(wait_status) == SIGINT)
		{
			write(STDOUT_FILENO, "^C\n", 3);
			*signal_printed = 1;
		}
		else if (WTERMSIG(wait_status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "^\\Quit (core dumped)\n", 21);
			*signal_printed = 1;
		}
	}
}

static size_t	wait_find_child_index(size_t cmd_count,
		pid_t *child_pids, int current_pid)
{
	size_t	cmd_index;

	cmd_index = 0;
	while (cmd_index < cmd_count && child_pids[cmd_index] != current_pid)
		cmd_index++;
	return (cmd_index);
}

static void	exec_wait_process_child(t_wait_ctx *ctx,
		int *signal_printed, int *final_status)
{
	size_t	cmd_index;

	cmd_index = wait_find_child_index(ctx->cmd_count,
			ctx->child_pids, ctx->current_pid);
	if (cmd_index == ctx->cmd_count - 1)
		*final_status = ctx->wait_status;
	exec_wait_handle_signal_output(ctx->wait_status, signal_printed);
}

void	exec_wait_all_children(t_ms *ms, size_t cmd_count, pid_t *child_pids)
{
	int			final_status;
	int			signal_printed;
	size_t		children_waited;
	t_wait_ctx	ctx;

	signal_printed = 0;
	final_status = 0;
	children_waited = 0;
	ctx.cmd_count = cmd_count;
	ctx.child_pids = child_pids;
	ms_signals_ignore();
	while (children_waited < cmd_count)
	{
		ctx.current_pid = waitpid(-1, &ctx.wait_status, 0);
		if (ctx.current_pid < 0)
		{
			if (errno != ECHILD)
				perror("waitpid");
			break ;
		}
		children_waited++;
		exec_wait_process_child(&ctx, &signal_printed, &final_status);
	}
	if (final_status)
		ms_exec_handle_signals(final_status, ms);
}
