/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:15 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:16 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pipe(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	(void)input_line;
	if (lexer_tokvec_push(output_tokens, TOK_PIPE, NULL) < 0)
		return (-1);
	(*char_index)++;
	return (0);
}

static int	handle_redirect_in(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	if (input_line[*char_index + 1] == '<')
	{
		if (lexer_tokvec_push(output_tokens, TOK_DLESS, NULL) < 0)
			return (-1);
		*char_index += 2;
	}
	else
	{
		if (lexer_tokvec_push(output_tokens, TOK_REDIR_IN, NULL) < 0)
			return (-1);
		(*char_index)++;
	}
	return (0);
}

static int	handle_redirect_out(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	if (input_line[*char_index + 1] == '>')
	{
		if (lexer_tokvec_push(output_tokens, TOK_DGREAT, NULL) < 0)
			return (-1);
		*char_index += 2;
	}
	else
	{
		if (lexer_tokvec_push(output_tokens, TOK_REDIR_OUT, NULL) < 0)
			return (-1);
		(*char_index)++;
	}
	return (0);
}

int	lexer_handle_operator(const char *input_line,
		size_t *char_index, t_tokvec *output_tokens)
{
	if (input_line[*char_index] == '|')
		return (handle_pipe(input_line, char_index, output_tokens));
	if (input_line[*char_index] == '<')
		return (handle_redirect_in(input_line, char_index, output_tokens));
	if (input_line[*char_index] == '>')
		return (handle_redirect_out(input_line, char_index, output_tokens));
	return (0);
}
