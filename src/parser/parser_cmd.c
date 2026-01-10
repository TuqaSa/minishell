/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:57 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:22:57 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_should_split_word(const char *raw_input,
		const char *expanded_output)
{
	if (!raw_input || !expanded_output)
		return (0);
	if (parser_is_quoted_token(raw_input))
		return (0);
	if (ft_strchr(raw_input, '"') || ft_strchr(raw_input, '\''))
		return (0);
	if (!ft_strchr(expanded_output, ' '))
		return (0);
	return (1);
}

static int	parser_handle_word_token(t_ms *ms, t_token current_token,
		char ***argv_ptr, size_t *argc_ptr)
{
	char	*expanded_word;

	expanded_word = expand_word(ms, current_token.raw);
	if (!expanded_word)
		return (-1);
	if (parser_should_split_word(current_token.raw, expanded_word))
		return (parser_handle_split_word(expanded_word, argv_ptr, argc_ptr));
	return (parser_handle_single_word(expanded_word, current_token.raw,
			argv_ptr, argc_ptr));
}

static int	parser_handle_redir_token(t_ms *ms, const t_tokvec *token_vector,
		size_t *token_index, t_cmd *output_cmd)
{
	t_token	current_token;
	char	*arg_raw;
	t_redir	redirect_info;

	current_token = token_vector->v[*token_index];
	if (parser_valid_r_s(token_vector, *token_index) != 0)
		return (1);
	arg_raw = token_vector->v[++(*token_index)].raw;
	if (parser_setup_redir(ms, &redirect_info,
			current_token.type, arg_raw) != 0)
		return (-1);
	if (push_red(&output_cmd->reds, &output_cmd->nreds, redirect_info) < 0)
	{
		parser_cleanup_redir(&redirect_info);
		return (-1);
	}
	return (0);
}

static int	parse_tokens(t_parse_ctx *parse_context)
{
	size_t	token_index;

	token_index = 0;
	while (token_index < parse_context->tv->n)
	{
		if (parse_context->tv->v[token_index].type == TOK_WORD)
		{
			if (parser_handle_word_token(parse_context->ms,
					parse_context->tv->v[token_index], parse_context->argv,
					parse_context->argc) != 0)
				return (parser_cleanup_parse_error(*(parse_context->argv),
						*(parse_context->argc),
						parse_context->out));
		}
		else
		{
			if (parser_handle_redir_token(parse_context->ms, parse_context->tv,
					&token_index, parse_context->out) != 0)
				return (parser_cleanup_parse_error(*(parse_context->argv),
						*(parse_context->argc),
						parse_context->out));
		}
		token_index++;
	}
	return (0);
}

int	parse_cmd(t_ms *ms, const t_tokvec *token_vector, t_cmd *output_cmd)
{
	size_t		argc_count;
	char		**argv_array;
	t_parse_ctx	parse_context;

	output_cmd->argv = NULL;
	output_cmd->reds = NULL;
	output_cmd->nreds = 0;
	argc_count = 0;
	argv_array = NULL;
	parse_context.ms = ms;
	parse_context.tv = token_vector;
	parse_context.argv = &argv_array;
	parse_context.argc = &argc_count;
	parse_context.out = output_cmd;
	if (parse_tokens(&parse_context) != 0)
		return (-1);
	output_cmd->argv = argv_array;
	return (0);
}
