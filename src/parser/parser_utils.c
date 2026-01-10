/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:42 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:43 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(const t_tokvec *token_vector)
{
	if (token_vector->n && (token_vector->v[0].type == TOK_PIPE
			|| token_vector->v[token_vector->n - 1].type == TOK_PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

void	ms_pipeline_free(t_pipeline *pipeline)
{
	size_t	cmd_index;

	if (!pipeline || !pipeline->cmds)
		return ;
	cmd_index = 0;
	while (cmd_index < pipeline->n)
	{
		ms_cmd_free(&pipeline->cmds[cmd_index]);
		cmd_index++;
	}
	free(pipeline->cmds);
	pipeline->cmds = NULL;
	pipeline->n = 0;
}

/* Quote processing functions for literal unquoting */
char	*unquote_literal(const char *raw_input)
{
	size_t	buffer_capacity;
	size_t	buffer_length;
	char	*output_buffer;

	buffer_capacity = 0;
	buffer_length = 0;
	output_buffer = lexer_sb_new(0);
	if (!output_buffer)
		return (NULL);
	if (process_quotes(raw_input, &output_buffer,
			&buffer_length, &buffer_capacity) != 0)
	{
		free(output_buffer);
		return (NULL);
	}
	return (output_buffer);
}

int	process_quotes(const char *raw_input, char **o_buffer,
			size_t *b_length, size_t *b_capacity)
{
	size_t	char_index;
	int		in_single;
	int		in_double;
	char	current_char;

	char_index = 0;
	in_single = 0;
	in_double = 0;
	while (raw_input && raw_input[char_index])
	{
		current_char = raw_input[char_index++];
		if (!in_single && current_char == '"')
		{
			in_double = !in_double;
			continue ;
		}
		if (!in_double && current_char == '\'')
		{
			in_single = !in_single;
			continue ;
		}
		if (lexer_sb_add(o_buffer, b_length, b_capacity, current_char) < 0)
			return (-1);
	}
	return (0);
}
