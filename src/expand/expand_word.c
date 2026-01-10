/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:05 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:06 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_sign_process(t_word_expand_ctx *ctx)
{
	(*ctx->char_index)++;
	if (ctx->raw[*ctx->char_index] == '?')
		return (status_expansion_handle(ctx->ms, ctx->char_index, ctx->output));
	if ((ft_isalpha(ctx->raw[*ctx->char_index])
			|| ctx->raw[*ctx->char_index] == '_')
		|| ft_isdigit(ctx->raw[*ctx->char_index]))
	{
		if (expand_variable_substitute(ctx->ms, ctx->raw,
				ctx->char_index, ctx->output) < 0)
		{
			free(*ctx->output);
			*ctx->output = NULL;
			return (-1);
		}
		return (0);
	}
	return (literal_dollar_append(ctx->output));
}

static int	word_character_process(t_word_expand_ctx *ctx)
{
	if (quote_toggle_check(ctx->raw, ctx->char_index,
			ctx->in_single, ctx->in_double))
		return (0);
	if (ctx->raw[*ctx->char_index] == '$' && !*ctx->in_single)
	{
		if (dollar_sign_process(ctx) < 0)
			return (-1);
	}
	else
	{
		if (char_append_to_output(ctx->raw, ctx->char_index, ctx->output) < 0)
			return (-1);
	}
	return (0);
}

char	*expand_word(t_ms *ms, const char *raw)
{
	t_word_expand_ctx	ctx;
	char				*output;
	size_t				char_index;
	int					in_single;
	int					in_double;

	if (!raw)
		return (NULL);
	output = NULL;
	char_index = 0;
	in_single = 0;
	in_double = 0;
	ctx = (t_word_expand_ctx){ms, raw, &output, &char_index,
		&in_single, &in_double};
	while (raw[char_index])
	{
		if (word_character_process(&ctx) < 0)
		{
			free(output);
			return (NULL);
		}
	}
	if (!output)
		output = ft_strdup("");
	return (output);
}
