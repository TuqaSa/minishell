/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:17:31 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:11 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_process_heredoc_arg(t_ms *ms,
		t_redir *redirect_info, char *arg_raw)
{
	char	*delimiter;
	int		file_descriptor;

	delimiter = unquote_literal(arg_raw);
	if (!delimiter)
		return (-1);
	file_descriptor = -1;
	if (ms_heredoc_collect(ms, delimiter, &file_descriptor) < 0)
	{
		free(delimiter);
		ms->last_status = 130;
		return (1);
	}
	redirect_info->arg = delimiter;
	redirect_info->hdoc_fd = file_descriptor;
	return (0);
}

static int	parser_process_file_arg(t_ms *ms,
		t_redir *redirect_info, char *arg_raw)
{
	char	*expanded_filename;

	expanded_filename = expand_word(ms, arg_raw);
	if (!expanded_filename)
		return (-1);
	redirect_info->arg = expanded_filename;
	return (0);
}

/* Public redirection functions */
int	parser_set_redir_type(t_redir *redirect_info, int token_type)
{
	if (token_type == TOK_REDIR_IN)
		redirect_info->type = R_IN;
	else if (token_type == TOK_REDIR_OUT)
		redirect_info->type = R_OUT;
	else if (token_type == TOK_DGREAT)
		redirect_info->type = R_APPEND;
	else
		redirect_info->type = R_HEREDOC;
	return (0);
}

int	parser_process_redir_arg(t_ms *ms, t_redir *redirect_info, char *arg_raw)
{
	if (redirect_info->type == R_HEREDOC)
		return (parser_process_heredoc_arg(ms, redirect_info, arg_raw));
	else
		return (parser_process_file_arg(ms, redirect_info, arg_raw));
}

void	parser_cleanup_redir(t_redir *redirect_info)
{
	if (redirect_info->arg)
		free(redirect_info->arg);
	if (redirect_info->hdoc_fd >= 0)
		close(redirect_info->hdoc_fd);
}
