/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:14:49 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:43 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_save_stdio(int *saved_input, int *saved_output)
{
	*saved_input = dup(STDIN_FILENO);
	*saved_output = dup(STDOUT_FILENO);
	if (*saved_input < 0 || *saved_output < 0)
	{
		if (*saved_input >= 0)
			close(*saved_input);
		if (*saved_output >= 0)
			close(*saved_output);
		return (-1);
	}
	return (0);
}

static void	builtin_restore_stdio(int saved_input, int saved_output)
{
	dup2(saved_input, STDIN_FILENO);
	dup2(saved_output, STDOUT_FILENO);
	close(saved_input);
	close(saved_output);
}

int	ms_exec_builtin_check(t_ms *ms, t_cmd *command)
{
	int	argument_count;
	int	saved_input;
	int	saved_output;
	int	builtin_result;

	if (!is_builtin(command->argv[0]))
		return (1);
	if (builtin_save_stdio(&saved_input, &saved_output) < 0)
		return (2);
	if (ms_apply_redirs(command) < 0)
	{
		ms->last_status = 1;
		builtin_restore_stdio(saved_input, saved_output);
		return (-1);
	}
	argument_count = 0;
	while (command->argv[argument_count])
		argument_count++;
	builtin_result = run_builtin(argument_count, command->argv, ms);
	builtin_restore_stdio(saved_input, saved_output);
	if (builtin_result == 2)
		return (2);
	return (0);
}

int	ms_exec_external_cmd(t_ms *ms, t_cmd *command, t_pipeline *pl)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("minishell");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (ms_apply_redirs(command) < 0)
		{
			if (pl)
				ms_pipeline_free(pl);
			env_context_free(ms->envp);
			_exit(1);
		}
		exec_external_command(ms, command, pl);
	}
	exec_wait_all_children(ms, 1, &child_pid);
	return (0);
}

int	ms_exec_cmd_with_pipeline(t_ms *ms, t_cmd *cmd, t_pipeline *pl)
{
	int	builtin_result;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		if (cmd->nreds > 0)
		{
			if (exec_empty_cmd_redirs(cmd) < 0)
			{
				ms->last_status = 1;
				return (-1);
			}
		}
		return (0);
	}
	builtin_result = ms_exec_builtin_check(ms, cmd);
	if (builtin_result == 2)
		return (2);
	if (builtin_result == 0)
		return (0);
	if (builtin_result == -1)
		return (-1);
	return (ms_exec_external_cmd(ms, cmd, pl));
}
