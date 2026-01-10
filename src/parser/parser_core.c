/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:11 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:07 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parser_result(t_ms *ms, int parser_result)
{
	if (parser_result != 0)
	{
		if (parser_result == 1)
			ms->last_status = 2;
		return (0);
	}
	return (1);
}

static int	handle_lexer_result(t_ms *ms, int lexer_result)
{
	if (lexer_result == 1)
	{
		ms->last_status = 2;
		return (0);
	}
	if (lexer_result < 0)
		return (-1);
	return (1);
}

int	ms_run_line_simple(t_ms *ms, const char *input_line)
{
	t_tokvec	token_vector;
	t_pipeline	pipeline;
	int			lexer_result;
	int			parser_result;
	int			exec_result;

	lexer_result = lexer_tokenize(input_line, &token_vector);
	if (handle_lexer_result(ms, lexer_result) <= 0)
		return (handle_lexer_result(ms, lexer_result));
	parser_result = ms_parse_pipeline(ms, &token_vector, &pipeline);
	lexer_tokvec_free(&token_vector);
	if (handle_parser_result(ms, parser_result) == 0)
		return (0);
	exec_result = ms_exec_pipeline(ms, &pipeline);
	ms_pipeline_free(&pipeline);
	if (exec_result < 0)
		ms->last_status = 1;
	return (exec_result);
}

int	ms_parse_pipeline(t_ms *ms, const t_tokvec *token_vector,
		t_pipeline *output_pipeline)
{
	output_pipeline->cmds = NULL;
	output_pipeline->n = 0;
	if (check_pipe_syntax(token_vector) != 0)
		return (1);
	return (parser_parse_segments(ms, token_vector, output_pipeline));
}
