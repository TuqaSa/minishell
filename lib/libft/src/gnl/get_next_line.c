/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:08:46 by ealshari          #+#    #+#             */
/*   Updated: 2025/02/22 02:07:53 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Extracts a line up to newline from stored_data and updates the remainder
 * @param stored_data: Pointer to stored string data
 * @param newline_index: Position of newline character
 * @return: Extracted line or NULL on error
 */
static char	*get_line_from_stored_data(char **stored_data, int newline_index)
{
	char	*line;
	char	*temp;

	if (!*stored_data)
		return (NULL);
	temp = *stored_data;
	line = ft_substr_gnl(*stored_data, 0, newline_index + 1);
	if (!line)
	{
		free(*stored_data);
		*stored_data = NULL;
		return (NULL);
	}
	*stored_data = ft_substr_gnl(*stored_data, newline_index + 1,
			ft_strlen_gnl(*stored_data) - newline_index - 1);
	free(temp);
	if (!*stored_data)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/*
 * Handles the case when no newline is found in stored data
 * @return: Complete content or NULL if empty/error
 */
static char	*handle_no_newline(char **stored_data)
{
	char	*line;

	if (!*stored_data || ft_strlen_gnl(*stored_data) == 0)
	{
		free(*stored_data);
		*stored_data = NULL;
		return (NULL);
	}
	line = ft_strdup_gnl(*stored_data);
	free(*stored_data);
	*stored_data = NULL;
	return (line);
}

/*
 * Main line extraction logic
 * Determines whether to extract up to newline or handle remaining content
 */
static char	*extract_line(char **stored_data)
{
	int	newline_index;

	if (!*stored_data)
		return (NULL);
	newline_index = ft_strchr_gnl(*stored_data, '\n');
	if (newline_index == -1)
		return (handle_no_newline(stored_data));
	else
		return (get_line_from_stored_data(stored_data, newline_index));
}

/*
 * Reads from file descriptor into buffer and updates stored data
 * Handles memory management and error cases
 */
static void	read_and_store(char **read_chunk, char **stored_data, int fd,
		int *bytes_read)
{
	char	*temp;

	*read_chunk = (char *)malloc(BUFFER_SIZE + 1);
	if (!*read_chunk)
	{
		free(*stored_data);
		*stored_data = NULL;
		return ;
	}
	*bytes_read = read(fd, *read_chunk, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(*read_chunk);
		free(*stored_data);
		*stored_data = NULL;
		return ;
	}
	(*read_chunk)[*bytes_read] = '\0';
	temp = ft_strjoin_gnl(*stored_data, *read_chunk);
	free(*stored_data);
	*stored_data = temp;
	free(*read_chunk);
}

char	*get_next_line(int fd)
{
	static char	*stored_data;
	char		*read_chunk;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stored_data)
		stored_data = ft_strdup_gnl("");
	bytes_read = 1;
	read_chunk = NULL;
	while (bytes_read > 0 && ft_strchr_gnl(stored_data, '\n') == -1)
	{
		read_and_store(&read_chunk, &stored_data, fd, &bytes_read);
		if (!stored_data)
			return (NULL);
	}
	line = extract_line(&stored_data);
	if (ft_strlen_gnl(stored_data) == 0)
	{
		free(stored_data);
		stored_data = NULL;
	}
	return (line);
}
