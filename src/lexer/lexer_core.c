/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:10 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:11 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_whitespace(const char *input_line, size_t *char_index)
{
	while (input_line[*char_index] && (input_line[*char_index] == ' '
			|| input_line[*char_index] == '\t'))
		(*char_index)++;
	return (0);
}

static int	process_token(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	if (input_line[*char_index] == '|' || input_line[*char_index] == '<'
		|| input_line[*char_index] == '>')
		return (lexer_handle_operator(input_line, char_index, output_tokens));
	else
		return (lexer_handle_word(input_line, char_index, output_tokens));
}

int	lexer_tokenize(const char *input_line, t_tokvec *output_tokens)
{
	size_t	char_index;
	int		result;

	output_tokens->v = NULL;
	output_tokens->n = 0;
	output_tokens->cap = 0;
	char_index = 0;
	while (input_line && input_line[char_index])
	{
		skip_whitespace(input_line, &char_index);
		if (!input_line[char_index])
			break ;
		result = process_token(input_line, &char_index, output_tokens);
		if (result != 0)
		{
			if (result > 0)
				lexer_tokvec_free(output_tokens);
			return (result);
		}
	}
	return (0);
}
