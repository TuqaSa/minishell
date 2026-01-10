/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:38 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:41 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_content_extract(const char *input_line,
		size_t *char_index, t_word_buf *word_buffer)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (input_line[*char_index])
	{
		if (lexer_should_break_word(input_line, *char_index,
				in_single, in_double))
			break ;
		if (lexer_handle_quotes(input_line, char_index, &in_single, &in_double))
		{
			if (lexer_add_char_to_word(word_buffer,
					input_line[*char_index - 1]) < 0)
				return (-1);
			continue ;
		}
		if (lexer_add_char_to_word(word_buffer, input_line[*char_index]) < 0)
			return (-1);
		(*char_index)++;
	}
	return (in_single || in_double);
}

static int	setup_word_buffer(t_word_buf *word_buffer, char **buffer,
	size_t *buffer_length, size_t *buffer_capacity)
{
	*buffer_length = 0;
	*buffer_capacity = 0;
	*buffer = lexer_sb_new(0);
	if (!*buffer)
		return (-1);
	word_buffer->buf = buffer;
	word_buffer->len = buffer_length;
	word_buffer->cap = buffer_capacity;
	return (0);
}

static int	handle_quote_error(char *buffer)
{
	ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
	free(buffer);
	return (1);
}

int	lexer_handle_word(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	char		*buffer;
	int			quote_state;
	t_word_buf	word_buffer;
	size_t		buffer_length;
	size_t		buffer_capacity;

	if (setup_word_buffer(&word_buffer, &buffer,
			&buffer_length, &buffer_capacity) < 0)
		return (-1);
	quote_state = word_content_extract(input_line, char_index, &word_buffer);
	if (quote_state < 0)
		return (quote_state);
	if (quote_state > 0)
		return (handle_quote_error(buffer));
	if (lexer_tokvec_push(output_tokens, TOK_WORD, buffer) < 0)
	{
		free(buffer);
		return (-1);
	}
	return (0);
}
