/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:24 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:22:23 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_handle_signals(int process_status, t_ms *ms)
{
	int	signal_number;

	if (WIFEXITED(process_status))
		ms->last_status = WEXITSTATUS(process_status);
	else if (WIFSIGNALED(process_status))
	{
		signal_number = WTERMSIG(process_status);
		ms->last_status = 128 + signal_number;
	}
	else if (WIFSTOPPED(process_status))
		ms->last_status = 128 + SIGSTOP;
	else if (WIFCONTINUED(process_status))
		ms->last_status = 128 + SIGCONT;
}

static void	exec_cleanup_and_exit(t_ms *ms, t_pipeline *pl, int exit_code)
{
	if (pl)
		ms_pipeline_free(pl);
	env_context_free(ms->envp);
	if (ms->pipe_fds)
		free(ms->pipe_fds);
	if (ms->child_pids)
		free(ms->child_pids);
	_exit(exit_code);
}

static void	exec_error_and_exit(const char *cmd, const char *error_msg,
							t_ms *ms, t_pipeline *pl)
{
	int	exit_code;

	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	exit_code = 127;
	if (ft_strnstr(error_msg, "directory", ft_strlen(error_msg)))
		exit_code = 126;
	if (pl)
		ms_pipeline_free(pl);
	env_context_free(ms->envp);
	if (ms->pipe_fds)
		free(ms->pipe_fds);
	if (ms->child_pids)
		free(ms->child_pids);
	_exit(exit_code);
}

static void	exec_path_command(t_ms *ms, t_cmd *cmd, t_pipeline *pl)
{
	char	*resolved_path;

	resolved_path = ms_resolve_path(ms, cmd->argv[0]);
	if (resolved_path)
	{
		execve(resolved_path, cmd->argv, ms->envp);
		free(resolved_path);
	}
	exec_error_and_exit(cmd->argv[0],
		": command not found\n", ms, pl);
}

void	exec_external_command(t_ms *ms, t_cmd *cmd, t_pipeline *pl)
{
	struct stat	path_stat;

	if (!ft_strchr(cmd->argv[0], '/'))
	{
		exec_path_command(ms, cmd, pl);
		return ;
	}
	if (stat(cmd->argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		exec_error_and_exit(cmd->argv[0], ": Is a directory\n", ms, pl);
	execve(cmd->argv[0], cmd->argv, ms->envp);
	perror("minishell");
	if (errno == ENOENT)
		exec_cleanup_and_exit(ms, pl, 127);
	else
		exec_cleanup_and_exit(ms, pl, 126);
}
