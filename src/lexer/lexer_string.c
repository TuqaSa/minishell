/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:20 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:21 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	string_buffer_copy_content(char **buffer_ptr,
		char *new_buffer, size_t buffer_length)
{
	ft_memcpy(new_buffer, *buffer_ptr, buffer_length);
	free(*buffer_ptr);
	*buffer_ptr = new_buffer;
	return (0);
}

static int	string_buffer_expand(char **buffer_ptr,
		size_t *buffer_capacity, size_t buffer_length)
{
	size_t	new_capacity;
	char	*new_buffer;

	if (*buffer_capacity > 0)
		new_capacity = (*buffer_capacity * 2);
	else
		new_capacity = 16;
	new_buffer = (char *)ft_calloc(new_capacity, sizeof(char));
	if (!new_buffer)
		return (-1);
	string_buffer_copy_content(buffer_ptr, new_buffer, buffer_length);
	*buffer_capacity = new_capacity;
	return (0);
}

char	*lexer_sb_new(size_t initial_capacity)
{
	char	*buffer_ptr;
	size_t	alloc_size;

	if (initial_capacity > 0)
		alloc_size = initial_capacity;
	else
		alloc_size = 1;
	buffer_ptr = (char *)ft_calloc(alloc_size, sizeof(char));
	if (!buffer_ptr)
		return (NULL);
	return (buffer_ptr);
}

int	lexer_sb_add(char **buffer_ptr, size_t *buffer_length,
		size_t *buffer_capacity, char new_char)
{
	if (*buffer_length + 1 >= *buffer_capacity)
	{
		if (string_buffer_expand(buffer_ptr, buffer_capacity,
				*buffer_length) < 0)
			return (-1);
	}
	(*buffer_ptr)[(*buffer_length)++] = new_char;
	(*buffer_ptr)[*buffer_length] = '\0';
	return (0);
}
