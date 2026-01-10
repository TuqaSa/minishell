/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:15:02 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:52 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_create_pipe(int *pipe_fds)
{
	if (pipe(pipe_fds) == -1)
		return (-1);
	return (0);
}

static int	heredoc_check_delimiter(const char *line, const char *delimiter)
{
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& (line[ft_strlen(delimiter)] == '\n'
			|| line[ft_strlen(delimiter)] == '\0'))
		return (1);
	return (0);
}

static int	heredoc_read_chunk(t_ms *ms, const char *delimiter,
		ssize_t nbytes, int out_fd)
{
	char	*line;
	ssize_t	actual_bytes;

	(void)ms;
	line = malloc(nbytes + 1);
	if (!line)
		return (-1);
	actual_bytes = read(STDIN_FILENO, line, nbytes);
	if (actual_bytes == -1)
	{
		free(line);
		return (-1);
	}
	line[actual_bytes] = '\0';
	if (heredoc_check_delimiter(line, delimiter))
	{
		free(line);
		return (0);
	}
	write(out_fd, line, actual_bytes);
	free(line);
	return (1);
}

static int	heredoc_input_loop(t_ms *ms, const char *delimiter, int out_fd)
{
	int		nbytes;
	int		result;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "> ", 2);
	while (1)
	{
		if (ioctl(STDIN_FILENO, FIONREAD, &nbytes) == -1)
			return (-1);
		if (g_sig == SIGINT)
			return (-1);
		if (nbytes > 0)
		{
			result = heredoc_read_chunk(ms, delimiter, nbytes, out_fd);
			if (result <= 0)
				return (result);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "> ", 2);
		}
	}
	return (0);
}

int	ms_heredoc_collect(t_ms *ms, const char *delimiter, int *output_fd)
{
	int		pipe_fds[2];
	int		result;

	if (heredoc_create_pipe(pipe_fds) == -1)
		return (-1);
	g_sig = 0;
	ms_signals_heredoc();
	result = heredoc_input_loop(ms, delimiter, pipe_fds[1]);
	close(pipe_fds[1]);
	ms_signals_interactive();
	if (result == -1)
	{
		close(pipe_fds[0]);
		return (-1);
	}
	*output_fd = pipe_fds[0];
	return (0);
}
