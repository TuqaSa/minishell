/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:16 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:22:12 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_open_fd(const t_redir *redirect_info)
{
	int	file_descriptor;

	if (redirect_info->type == R_IN)
		file_descriptor = open(redirect_info->arg, O_RDONLY);
	else if (redirect_info->type == R_OUT)
		file_descriptor = open(redirect_info->arg, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (redirect_info->type == R_APPEND)
		file_descriptor = open(redirect_info->arg, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else if (redirect_info->type == R_HEREDOC)
		return (redirect_info->hdoc_fd);
	else
		return (-1);
	if (file_descriptor < 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, redirect_info->arg, ft_strlen(redirect_info->arg));
		write(STDERR_FILENO, ": ", 2);
		perror("");
		return (-1);
	}
	return (file_descriptor);
}

static int	redir_apply_single(const t_redir *redirect_info)
{
	int	file_descriptor;
	int	target_fd;

	file_descriptor = redir_open_fd(redirect_info);
	if (file_descriptor < 0)
		return (-1);
	if (redirect_info->type == R_IN || redirect_info->type == R_HEREDOC)
		target_fd = STDIN_FILENO;
	else
		target_fd = STDOUT_FILENO;
	if (dup2(file_descriptor, target_fd) < 0)
	{
		close(file_descriptor);
		return (-1);
	}
	close(file_descriptor);
	return (0);
}

int	ms_apply_redirs(const t_cmd *command)
{
	size_t	redir_index;

	redir_index = 0;
	while (redir_index < command->nreds)
	{
		if (redir_apply_single(&command->reds[redir_index]) < 0)
			return (-1);
		redir_index++;
	}
	return (0);
}

static int	exec_empty_redir_error(const char *filename)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, ": ", 2);
	perror("");
	return (-1);
}

int	exec_empty_cmd_redirs(t_cmd *cmd)
{
	size_t	redir_index;
	int		fd;

	redir_index = 0;
	while (redir_index < cmd->nreds)
	{
		if (cmd->reds[redir_index].type == R_OUT)
		{
			fd = open(cmd->reds[redir_index].arg,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (exec_empty_redir_error(cmd->reds[redir_index].arg));
			close(fd);
		}
		else if (cmd->reds[redir_index].type == R_IN)
		{
			fd = open(cmd->reds[redir_index].arg, O_RDONLY);
			if (fd < 0)
				return (exec_empty_redir_error(cmd->reds[redir_index].arg));
			close(fd);
		}
		redir_index++;
	}
	return (0);
}
