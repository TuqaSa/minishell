/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:16:47 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:16:48 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_word(char ***argv_ptr, size_t *argc_ptr, const char *word_string)
{
	size_t	current_count;
	char	**new_vector;
	size_t	word_index;

	current_count = *argc_ptr;
	new_vector = (char **)ft_calloc(current_count + 2, sizeof(char *));
	if (!new_vector)
		return (-1);
	word_index = 0;
	while (word_index < current_count)
	{
		new_vector[word_index] = (*argv_ptr)[word_index];
		word_index++;
	}
	new_vector[current_count] = (char *)word_string;
	new_vector[current_count + 1] = NULL;
	free(*argv_ptr);
	*argv_ptr = new_vector;
	*argc_ptr = current_count + 1;
	return (0);
}

int	push_red(t_redir **redirections_ptr,
		size_t *count_ptr, t_redir new_redirect)
{
	size_t	current_count;
	t_redir	*new_redirects;
	size_t	redir_index;

	current_count = *count_ptr;
	new_redirects = (t_redir *)ft_calloc(current_count + 1, sizeof(t_redir));
	if (!new_redirects)
		return (-1);
	redir_index = 0;
	while (redir_index < current_count)
	{
		new_redirects[redir_index] = (*redirections_ptr)[redir_index];
		redir_index++;
	}
	new_redirects[current_count] = new_redirect;
	free(*redirections_ptr);
	*redirections_ptr = new_redirects;
	*count_ptr = current_count + 1;
	return (0);
}

int	push_cmd(t_pipeline *pipeline, t_cmd *command)
{
	size_t	current_count;
	t_cmd	*new_commands;
	size_t	cmd_index;

	current_count = pipeline->n;
	new_commands = (t_cmd *)ft_calloc(current_count + 1, sizeof(t_cmd));
	if (!new_commands)
		return (-1);
	cmd_index = 0;
	while (cmd_index < current_count)
	{
		new_commands[cmd_index] = pipeline->cmds[cmd_index];
		cmd_index++;
	}
	new_commands[current_count] = *command;
	free(pipeline->cmds);
	pipeline->cmds = new_commands;
	pipeline->n = current_count + 1;
	return (0);
}
