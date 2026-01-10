/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:18 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:19 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_build_cmd_segment(t_seg_ctx *segment_context,
	size_t start_index, size_t end_index)
{
	t_tokvec	segment;
	t_cmd		command;
	int			result;

	segment.v = (t_token *)&segment_context->tv->v[start_index];
	segment.n = end_index - start_index;
	segment.cap = 0;
	result = parse_cmd(segment_context->ms, &segment, &command);
	if (result != 0)
	{
		ms_pipeline_free(segment_context->out);
		return (result);
	}
	if (push_cmd(segment_context->out, &command) < 0)
	{
		ms_cmd_free(&command);
		ms_pipeline_free(segment_context->out);
		return (-1);
	}
	return (0);
}

static int	parser_process_cmd_segment(t_seg_ctx *segment_context,
		size_t start_index, size_t end_index)
{
	if (end_index == start_index)
	{
		if (segment_context->tv->n == 0)
			return (0);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		ms_pipeline_free(segment_context->out);
		return (1);
	}
	return (parser_build_cmd_segment(segment_context, start_index, end_index));
}

int	parser_parse_segments(t_ms *ms, const t_tokvec *token_vector,
		t_pipeline *output_pipeline)
{
	t_seg_ctx	segment_context;
	size_t		segment_start;
	size_t		token_index;

	segment_context.ms = ms;
	segment_context.tv = token_vector;
	segment_context.out = output_pipeline;
	segment_start = 0;
	token_index = 0;
	while (token_index <= token_vector->n)
	{
		if (token_index == token_vector->n
			|| token_vector->v[token_index].type == TOK_PIPE)
		{
			if (parser_process_cmd_segment(&segment_context,
					segment_start, token_index) != 0)
				return (1);
			segment_start = token_index + 1;
		}
		token_index++;
	}
	return (0);
}
