/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:26 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:27 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_valid_r_s(const t_tokvec *token_vector,
		size_t token_index)
{
	if (token_index + 1 >= token_vector->n
		|| token_vector->v[token_index + 1].type != TOK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (1);
	}
	return (0);
}

int	parser_setup_redir(t_ms *ms, t_redir *redirect_info,
		t_toktype redir_type, char *arg_raw)
{
	redirect_info->hdoc_fd = -1;
	redirect_info->arg = NULL;
	if (parser_set_redir_type(redirect_info, redir_type) != 0)
		return (-1);
	if (parser_process_redir_arg(ms, redirect_info, arg_raw) != 0)
		return (-1);
	return (0);
}
