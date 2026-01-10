/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:34 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:35 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_is_operator_char(int character)
{
	if (character == '|')
		return (1);
	if (character == '<')
		return (1);
	if (character == '>')
		return (1);
	return (0);
}

int	lexer_handle_quotes(const char *input_line, size_t *char_index,
	int *in_single, int *in_double)
{
	if (!*in_single && input_line[*char_index] == '"')
	{
		*in_double = !*in_double;
		(*char_index)++;
		return (1);
	}
	if (!*in_double && input_line[*char_index] == '\'')
	{
		*in_single = !*in_single;
		(*char_index)++;
		return (1);
	}
	return (0);
}

int	lexer_should_break_word(const char *input_line, size_t char_index,
	int in_single, int in_double)
{
	char	current_char;

	current_char = input_line[char_index];
	if (in_single || in_double)
		return (0);
	if (current_char == ' ' || current_char == '\t')
		return (1);
	if (lexer_is_operator_char(current_char))
		return (1);
	return (0);
}

int	lexer_add_char_to_word(t_word_buf *word_buffer, char character)
{
	if (lexer_sb_add(word_buffer->buf, word_buffer->len,
			word_buffer->cap, character) < 0)
	{
		free(*word_buffer->buf);
		return (-1);
	}
	return (0);
}
